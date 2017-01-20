#include <object/game_object.h>
#include <physics/rigid_bodies/fracture_rigid_body.h>
#include <physics/transformations.h>
#include "physics/bullet_extensions/btFractureDynamicsWorld.h"
#include "physics/bullet_extensions/btFractureBody.h"
#include "BulletCollision/CollisionShapes/btCompoundShape.h"

#include "BulletCollision/CollisionDispatch/btUnionFind.h"

#include <game/scene_container.h>
#include <physics/rigid_body.h>
#include <iostream>
#include <math/print_math.h>

btFractureDynamicsWorld::btFractureDynamicsWorld ( btDispatcher* dispatcher,btBroadphaseInterface* pairCache,btConstraintSolver* constraintSolver,btCollisionConfiguration* collisionConfiguration)
:btDiscreteDynamicsWorld(dispatcher,pairCache,constraintSolver,collisionConfiguration),
 m_fracturingMode(true),
 scene_(nullptr),
 impact_threshold_(25.0f)
{

}


void btFractureDynamicsWorld::glueCallback()
{

	int numManifolds = getDispatcher()->getNumManifolds();

	///first build the islands based on axis aligned bounding box overlap

	btUnionFind unionFind;

	int index = 0;
	{

		int i;
		for (i=0;i<getCollisionObjectArray().size(); i++)
		{
			btCollisionObject*   collisionObject= getCollisionObjectArray()[i];
		//	btRigidBody* body = btRigidBody::upcast(collisionObject);
			//Adding filtering here
#ifdef STATIC_SIMULATION_ISLAND_OPTIMIZATION
			if (!collisionObject->isStaticOrKinematicObject())
			{
				collisionObject->setIslandTag(index++);
			} else
			{
				collisionObject->setIslandTag(-1);
			}
#else
			collisionObject->setIslandTag(i);
			index=i+1;
#endif
		}
	}

	unionFind.reset(index);

	int numElem = unionFind.getNumElements();

	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* manifold = getDispatcher()->getManifoldByIndexInternal(i);
		if (!manifold->getNumContacts())
			continue;

		btScalar minDist = 1e30f;
		for (int v=0;v<manifold->getNumContacts();v++)
		{
			minDist = btMin(minDist,manifold->getContactPoint(v).getDistance());
		}
		if (minDist>0.)
			continue;
		
		btCollisionObject* colObj0 = (btCollisionObject*)manifold->getBody0();
		btCollisionObject* colObj1 = (btCollisionObject*)manifold->getBody1();
		int tag0 = (colObj0)->getIslandTag();
		int tag1 = (colObj1)->getIslandTag();
		//btRigidBody* body0 = btRigidBody::upcast(colObj0);
		//btRigidBody* body1 = btRigidBody::upcast(colObj1);


		if (!colObj0->isStaticOrKinematicObject() && !colObj1->isStaticOrKinematicObject())
		{
			unionFind.unite(tag0, tag1);
		}
	}




	numElem = unionFind.getNumElements();



	index=0;
	for (int ai=0;ai<getCollisionObjectArray().size();ai++)
	{
		btCollisionObject* collisionObject= getCollisionObjectArray()[ai];
		if (!collisionObject->isStaticOrKinematicObject())
		{
			int tag = unionFind.find(index);

			collisionObject->setIslandTag( tag);

			//Set the correct object offset in Collision Object Array
#if STATIC_SIMULATION_ISLAND_OPTIMIZATION
			unionFind.getElement(index).m_sz = ai;
#endif //STATIC_SIMULATION_ISLAND_OPTIMIZATION

			index++;
		}
	}
	unionFind.sortIslands();



	int endIslandIndex=1;
	int startIslandIndex;

	btAlignedObjectArray<btCollisionObject*> removedObjects;

	///iterate over all islands
	for ( startIslandIndex=0;startIslandIndex<numElem;startIslandIndex = endIslandIndex)
	{
		int islandId = unionFind.getElement(startIslandIndex).m_id;
		for (endIslandIndex = startIslandIndex+1;(endIslandIndex<numElem) && (unionFind.getElement(endIslandIndex).m_id == islandId);endIslandIndex++)
		{
		}

		int fractureObjectIndex = -1;

		int numObjects=0;

		int idx;
		for (idx=startIslandIndex;idx<endIslandIndex;idx++)
		{
			int i = unionFind.getElement(idx).m_sz;
			btCollisionObject* colObj0 = getCollisionObjectArray()[i];
			if (colObj0->getInternalType()& CUSTOM_FRACTURE_TYPE)
			{
				fractureObjectIndex = i;
			}
			btRigidBody* otherObject = btRigidBody::upcast(colObj0);
			if (!otherObject || !otherObject->getInvMass())
				continue;
			numObjects++;
		}

		///Then for each island that contains at least two objects and one fracture object
		if (fractureObjectIndex>=0 && numObjects>1)
		{

			btFractureBody* fracObj = (btFractureBody*)getCollisionObjectArray()[fractureObjectIndex];

			///glueing objects means creating a new compound and removing the old objects
			///delay the removal of old objects to avoid array indexing problems
			removedObjects.push_back(fracObj);
			m_fractureBodies.remove(fracObj);

			btAlignedObjectArray<btScalar> massArray;

			btAlignedObjectArray<btVector3> oldImpulses;
			btAlignedObjectArray<btVector3> oldCenterOfMassesWS;

			oldImpulses.push_back(fracObj->getLinearVelocity()/1./fracObj->getInvMass());
			oldCenterOfMassesWS.push_back(fracObj->getCenterOfMassPosition());

			btScalar totalMass = 0.f;


			btCompoundShape* compound = new btCompoundShape();
			if (fracObj->getCollisionShape()->isCompound())
			{
				btTransform tr;
				tr.setIdentity();
				btCompoundShape* oldCompound = (btCompoundShape*)fracObj->getCollisionShape();
				for (int c=0;c<oldCompound->getNumChildShapes();c++)
				{
					compound->addChildShape(oldCompound->getChildTransform(c),oldCompound->getChildShape(c));
					massArray.push_back(fracObj->m_masses[c]);
					totalMass+=fracObj->m_masses[c];
				}

			} else
			{
				btTransform tr;
				tr.setIdentity();
				compound->addChildShape(tr,fracObj->getCollisionShape());
				massArray.push_back(fracObj->m_masses[0]);
				totalMass+=fracObj->m_masses[0];
			}

			for (idx=startIslandIndex;idx<endIslandIndex;idx++)
			{

				int i = unionFind.getElement(idx).m_sz;

				if (i==fractureObjectIndex)
					continue;

				btCollisionObject* otherCollider = getCollisionObjectArray()[i];

				btRigidBody* otherObject = btRigidBody::upcast(otherCollider);
				//don't glue/merge with static objects right now, otherwise everything gets stuck to the ground
				///todo: expose this as a callback
				if (!otherObject || !otherObject->getInvMass())
					continue;


				oldImpulses.push_back(otherObject->getLinearVelocity()*(1.f/otherObject->getInvMass()));
				oldCenterOfMassesWS.push_back(otherObject->getCenterOfMassPosition());

				removedObjects.push_back(otherObject);
				m_fractureBodies.remove((btFractureBody*)otherObject);

				btScalar curMass = 1.f/otherObject->getInvMass();


				if (otherObject->getCollisionShape()->isCompound())
				{
					btTransform tr;
					btCompoundShape* oldCompound = (btCompoundShape*)otherObject->getCollisionShape();
					for (int c=0;c<oldCompound->getNumChildShapes();c++)
					{
						tr = fracObj->getWorldTransform().inverseTimes(otherObject->getWorldTransform()*oldCompound->getChildTransform(c));
						compound->addChildShape(tr,oldCompound->getChildShape(c));
						massArray.push_back(curMass/(btScalar)oldCompound->getNumChildShapes());

					}
				} else
				{
					btTransform tr;
					tr = fracObj->getWorldTransform().inverseTimes(otherObject->getWorldTransform());
					compound->addChildShape(tr,otherObject->getCollisionShape());
					massArray.push_back(curMass);
				}
				totalMass+=curMass;
			}



			btTransform shift;
			shift.setIdentity();
			btCompoundShape* newCompound = btFractureBody::shiftTransformDistributeMass(compound,totalMass,shift);
			int numChildren = newCompound->getNumChildShapes();
			btAssert(numChildren == massArray.size());

			btVector3 localInertia;
			newCompound->calculateLocalInertia(totalMass,localInertia);
			btFractureBody* newBody = new btFractureBody(totalMass,0,newCompound,localInertia, &massArray[0], numChildren,this);
			newBody->recomputeConnectivity(this);
			newBody->setWorldTransform(fracObj->getWorldTransform()*shift);

			//now the linear/angular velocity is still zero, apply the impulses

			for (int i=0;i<oldImpulses.size();i++)
			{
				btVector3 rel_pos = oldCenterOfMassesWS[i]-newBody->getCenterOfMassPosition();
				const btVector3& imp = oldImpulses[i];
				newBody->applyImpulse(imp, rel_pos);
			}

            std::cout << "totalMass: " << totalMass << std::endl;
            // <IFX>
            auto new_game_object = std::shared_ptr<ifx::GameObject>(
                    new ifx::GameObject());
            auto new_bt_body = std::shared_ptr<btFractureBody>(newBody);
            auto new_rigid_body = std::shared_ptr<ifx::FractureRigidBody>(
                    new ifx::FractureRigidBody(new_bt_body));
            new_game_object->Add(new_rigid_body);
            auto ifx_transform = ifx::BT2IFXTransform
                    (newBody->getWorldTransform());
            new_game_object->moveTo(ifx_transform.position);
            new_game_object->rotateTo(ifx_transform.rotation);

            int size = removedObjects.size();
            for(int i = 0; i < removedObjects.size();i++){
            //for(int i = size-1; i >= 0;i--){
                auto native_body = removedObjects[i];

                auto corresponding_game_object = Find(scene_, native_body);
                if(!corresponding_game_object)
                    return;
                    //throw std::invalid_argument("GameObject not found");
                auto render_objects = corresponding_game_object->GetComponents(
                        std::move(ifx::GameComponentType::RENDER));
                for(auto& render_object : render_objects){
                    ifx::TransformData transform
                            = render_object->global_transform();
                    transform.position =
                            transform.position - new_game_object->getPosition();
                    transform.rotation =
                            transform.rotation - new_game_object->getRotation();
                    render_object->local_transform(transform);

                    new_game_object->Add(render_object);
                }

                scene_->Remove(corresponding_game_object);
            }
            scene_->Add(new_game_object);
            // </IFX>
		}


	}
/*
	//remove the objects from the world at the very end, 
	//otherwise the island tags would not match the world collision object array indices anymore
	while (removedObjects.size())
	{
		btCollisionObject* otherCollider = removedObjects[removedObjects.size()-1];
		removedObjects.pop_back();

		btRigidBody* otherObject = btRigidBody::upcast(otherCollider);
		if (!otherObject || !otherObject->getInvMass())
			continue;
		removeRigidBody(otherObject);
	}*/

}


struct	btFracturePair
{
	btFractureBody* m_fracObj;
	btAlignedObjectArray<btPersistentManifold*>	m_contactManifolds;
};



void btFractureDynamicsWorld::solveConstraints(btContactSolverInfo& solverInfo)
{
	// todo: after fracture we should run the solver again for better realism
	// for example
	//	save all velocities and if one or more objects fracture:
	//	1) revert all velocties
	//	2) apply impulses for the fracture bodies at the contact locations
	//	3)and run the constaint solver again

	btDiscreteDynamicsWorld::solveConstraints(solverInfo);

	fractureCallback();
}

btFractureBody* btFractureDynamicsWorld::addNewBody(const btTransform& oldTransform,btScalar* masses, btCompoundShape* oldCompound)
{
	int i;

	btTransform shift;
	shift.setIdentity();
	btVector3 localInertia;
	btCompoundShape* newCompound = btFractureBody::shiftTransform(oldCompound,masses,shift,localInertia);
	btScalar totalMass = 0;
	for (i=0;i<newCompound->getNumChildShapes();i++)
		totalMass += masses[i];
	//newCompound->calculateLocalInertia(totalMass,localInertia);

	btFractureBody* newBody = new btFractureBody(totalMass,0,newCompound,localInertia, masses,newCompound->getNumChildShapes(), this);
	newBody->recomputeConnectivity(this);

	newBody->setCollisionFlags(newBody->getCollisionFlags()|btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	newBody->setWorldTransform(oldTransform*shift);
	//addRigidBody(newBody);
	return newBody;
}

void btFractureDynamicsWorld::addRigidBody(btRigidBody* body)
{
	if (body->getInternalType() & CUSTOM_FRACTURE_TYPE)
	{
		btFractureBody* fbody = (btFractureBody*)body;
		m_fractureBodies.push_back(fbody);
	}
	btDiscreteDynamicsWorld::addRigidBody(body);
}

void	btFractureDynamicsWorld::removeRigidBody(btRigidBody* body)
{
	if (body->getInternalType() & CUSTOM_FRACTURE_TYPE)
	{
		btFractureBody* fbody = (btFractureBody*)body;
		btAlignedObjectArray<btTypedConstraint*> tmpConstraints;

		for (int i=0;i<fbody->getNumConstraintRefs();i++)
		{
			tmpConstraints.push_back(fbody->getConstraintRef(i));
		}

		//remove all constraints attached to this rigid body too		
		for (int i=0;i<tmpConstraints.size();i++)
			btDiscreteDynamicsWorld::removeConstraint(tmpConstraints[i]);

		m_fractureBodies.remove(fbody);
	}
	


	btDiscreteDynamicsWorld::removeRigidBody(body);
}

void	btFractureDynamicsWorld::breakDisconnectedParts( btFractureBody* fracObj)
{

	if (!fracObj->getCollisionShape()->isCompound())
		return;

	btCompoundShape* compound = (btCompoundShape*)fracObj->getCollisionShape();
	int numChildren = compound->getNumChildShapes();

	if (numChildren<=1)
		return;

    auto corresponding_game_object = Find(scene_, fracObj);

	//compute connectivity
	btUnionFind unionFind;

	btAlignedObjectArray<int> tags;
	tags.resize(numChildren);
	int i, index = 0;
	for ( i=0;i<numChildren;i++)
	{
#ifdef STATIC_SIMULATION_ISLAND_OPTIMIZATION
		tags[i] = index++;
#else
		tags[i] = i;
		index=i+1;
#endif
	}

	unionFind.reset(index);
	int numElem = unionFind.getNumElements();
	for (i=0;i<fracObj->m_connections.size();i++)
	{
		btConnection& connection = fracObj->m_connections[i];
		if (connection.m_strength > 0.)
		{
			int tag0 = tags[connection.m_childIndex0];
			int tag1 = tags[connection.m_childIndex1];
			unionFind.unite(tag0, tag1);
		}
	}
	numElem = unionFind.getNumElements();

	index=0;
	for (int ai=0;ai<numChildren;ai++)
	{
		int tag = unionFind.find(index);
		tags[ai] = tag;
		//Set the correct object offset in Collision Object Array
#if STATIC_SIMULATION_ISLAND_OPTIMIZATION
		unionFind.getElement(index).m_sz = ai;
#endif //STATIC_SIMULATION_ISLAND_OPTIMIZATION
		index++;
	}
	unionFind.sortIslands();

	int endIslandIndex=1;
	int startIslandIndex;

	btAlignedObjectArray<btCollisionObject*> removedObjects;

	int numIslands = 0;

    auto render_components
            = corresponding_game_object->GetComponents
                    (std::move(ifx::GameComponentType::RENDER));
	for ( startIslandIndex=0;startIslandIndex<numElem;startIslandIndex = endIslandIndex)
	{
		int islandId = unionFind.getElement(startIslandIndex).m_id;
		for (endIslandIndex = startIslandIndex+1;(endIslandIndex<numElem) && (unionFind.getElement(endIslandIndex).m_id == islandId);endIslandIndex++)
		{
		}

	//	int fractureObjectIndex = -1;

		int numShapes=0;


		btCompoundShape* newCompound = new btCompoundShape();
		btAlignedObjectArray<btScalar> masses;

        auto ifx_world_transform
                = ifx::BT2IFXTransform(fracObj->getWorldTransform());
        auto new_game_object =
                std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
		int idx;
		for (idx=startIslandIndex;idx<endIslandIndex;idx++)
        //for (idx=endIslandIndex-1;idx>=startIslandIndex;idx--)
		{
			int i = unionFind.getElement(idx).m_sz;
	//		btCollisionShape* shape = compound->getChildShape(i);
			newCompound->addChildShape(compound->getChildTransform(i),compound->getChildShape(i));
			masses.push_back(fracObj->m_masses[i]);
			numShapes++;
            auto& transform = compound->getChildTransform(i);
            auto compound_transform = ifx::BT2IFXTransform(transform);

            if(i >= render_components.size())
                throw std::invalid_argument("Not a proper render component id");

            ifx::TransformData local_transform
                    = render_components[i]->local_transform();

            local_transform.position = compound_transform.position;
            local_transform.rotation = compound_transform.rotation;

            render_components[i]->local_transform(local_transform);
            new_game_object->Add(render_components[i]);
		}

        // Reset local transform of render bodies
        if(numShapes == 1){
            auto render_objects = new_game_object->GetComponents
                    (ifx::GameComponentType::RENDER);
            for(auto& render_object : render_objects){
                ifx::TransformData data = render_object->local_transform();
                data.position = glm::vec3(0,0,0);
                data.rotation = glm::vec3(0,0,0);
                render_object->local_transform(data);
            }
        }
		if (numShapes)
		{
			btFractureBody* newBody = addNewBody(fracObj->getWorldTransform(),&masses[0],newCompound);
			newBody->setLinearVelocity(fracObj->getLinearVelocity());
			newBody->setAngularVelocity(fracObj->getAngularVelocity());

            auto new_body_bt = std::shared_ptr<btFractureBody>(newBody);
            auto new_body = std::shared_ptr<ifx::FractureRigidBody>(
                    new ifx::FractureRigidBody(new_body_bt));

            ifx::PrintVec3(ifx_world_transform.position);

            new_game_object->local_transform(ifx_world_transform);
            new_game_object->Add(new_body);

            scene_->Add(new_game_object);
			numIslands++;
		}

	}




    scene_->Remove(corresponding_game_object);
	//removeRigidBody(fracObj);//should it also be removed from the array?


}

#include <stdio.h>
#include <iostream>


void btFractureDynamicsWorld::fractureCallback( )
{

	btAlignedObjectArray<btFracturePair> sFracturePairs;

	if (!m_fracturingMode)
	{
		glueCallback();
		return;
	}

	int numManifolds = getDispatcher()->getNumManifolds();

	sFracturePairs.clear();


	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* manifold = getDispatcher()->getManifoldByIndexInternal(i);
		if (!manifold->getNumContacts())
			continue;

		btScalar totalImpact = 0.f;
		for (int p=0;p<manifold->getNumContacts();p++)
		{
			totalImpact += manifold->getContactPoint(p).m_appliedImpulse;
		}

		
//		printf("totalImpact=%f\n",totalImpact);

		static float maxImpact = 0;
		if (totalImpact>maxImpact)
			maxImpact = totalImpact;

		//some threshold otherwise resting contact would break objects after a while
        // TODO impact_treshold

        if(totalImpact > 15)
            std::cout << "totalImpact: " << totalImpact << std::endl;
        if (totalImpact < impact_threshold_)
			continue;

		//		printf("strong impact\n");


		//@todo: add better logic to decide what parts to fracture
		//For example use the idea from the SIGGRAPH talk about the fracture in the movie 2012:
		//
		//Breaking thresholds can be stored as connectivity information between child shapes in the fracture object
		//
		//You can calculate some "impact value" by simulating all the individual child shapes 
		//as rigid bodies, without constraints, running it in a separate simulation world 
		//(or by running the constraint solver without actually modifying the dynamics world)
		//Then measure some "impact value" using the offset and applied impulse for each child shape
		//weaken the connections based on this "impact value" and only break 
		//if this impact value exceeds the breaking threshold.
		//you can propagate the weakening and breaking of connections using the connectivity information

		int f0 = m_fractureBodies.findLinearSearch((btFractureBody*)manifold->getBody0());
		int f1 = m_fractureBodies.findLinearSearch((btFractureBody*)manifold->getBody1());

		if (f0 == f1 == m_fractureBodies.size())
			continue;


		if (f0<m_fractureBodies.size())
		{
			int j=f0;

			btCollisionObject* colOb = (btCollisionObject*)manifold->getBody1();
	//		btRigidBody* otherOb = btRigidBody::upcast(colOb);
			//	if (!otherOb->getInvMass())
			//		continue;

			int pi=-1;

			for (int p=0;p<sFracturePairs.size();p++)
			{
				if (sFracturePairs[p].m_fracObj == m_fractureBodies[j])
				{
					pi = p; break;
				}
			}

			if (pi<0)
			{
				btFracturePair p;
				p.m_fracObj = m_fractureBodies[j];
				p.m_contactManifolds.push_back(manifold);
				sFracturePairs.push_back(p);
			} else
			{
				btAssert(sFracturePairs[pi].m_contactManifolds.findLinearSearch(manifold)==sFracturePairs[pi].m_contactManifolds.size());
				sFracturePairs[pi].m_contactManifolds.push_back(manifold);
			}
		}


		if (f1 < m_fractureBodies.size())
		{
			int j=f1;
			{
				btCollisionObject* colOb = (btCollisionObject*)manifold->getBody0();
				btRigidBody* otherOb = btRigidBody::upcast(colOb);
				//	if (!otherOb->getInvMass())
				//		continue;


				int pi=-1;

				for (int p=0;p<sFracturePairs.size();p++)
				{
					if (sFracturePairs[p].m_fracObj == m_fractureBodies[j])
					{
						pi = p; break;
					}
				}
				if (pi<0)
				{
					btFracturePair p;
					p.m_fracObj = m_fractureBodies[j];
					p.m_contactManifolds.push_back( manifold);
					sFracturePairs.push_back(p);
				} else
				{
					btAssert(sFracturePairs[pi].m_contactManifolds.findLinearSearch(manifold)==sFracturePairs[pi].m_contactManifolds.size());
					sFracturePairs[pi].m_contactManifolds.push_back(manifold);
				}
			}
		}

		//
	}

	//printf("m_fractureBodies size=%d\n",m_fractureBodies.size());
	//printf("sFracturePairs size=%d\n",sFracturePairs.size());
	if (!sFracturePairs.size())
		return;


	{
		//		printf("fracturing\n");

		for (int i=0;i<sFracturePairs.size();i++)
		{
			//check impulse/displacement at impact

			//weaken/break connections (and propagate breaking)

			//compute connectivity of connected child shapes


			if (sFracturePairs[i].m_fracObj->getCollisionShape()->isCompound())
			{
				btTransform tr;
				tr.setIdentity();
				btCompoundShape* oldCompound = (btCompoundShape*)sFracturePairs[i].m_fracObj->getCollisionShape();
				if (oldCompound->getNumChildShapes()>1)
				{
					bool needsBreakingCheck = false;


					//weaken/break the connections

					//@todo: propagate along the connection graph
					for (int j=0;j<sFracturePairs[i].m_contactManifolds.size();j++)
					{
						btPersistentManifold* manifold = sFracturePairs[i].m_contactManifolds[j];
						for (int k=0;k<manifold->getNumContacts();k++)
						{
							btManifoldPoint& pt = manifold->getContactPoint(k);
							if (manifold->getBody0()==sFracturePairs[i].m_fracObj)
							{
								for (int f=0;f<sFracturePairs[i].m_fracObj->m_connections.size();f++)
								{
									btConnection& connection = sFracturePairs[i].m_fracObj->m_connections[f];
									if (	(connection.m_childIndex0 == pt.m_index0) ||
										(connection.m_childIndex1 == pt.m_index0)
										)
									{
										connection.m_strength -= pt.m_appliedImpulse;
										if (connection.m_strength<0)
										{
											//remove or set to zero
											connection.m_strength=0.f;
											needsBreakingCheck = true;
										}
									}
								}
							} else
							{
								for (int f=0;f<sFracturePairs[i].m_fracObj->m_connections.size();f++)
								{
									btConnection& connection = sFracturePairs[i].m_fracObj->m_connections[f];
									if (	(connection.m_childIndex0 == pt.m_index1) ||
										(connection.m_childIndex1 == pt.m_index1)
										)
									{
										connection.m_strength -= pt.m_appliedImpulse;
										if (connection.m_strength<0)
										{
											//remove or set to zero
											connection.m_strength=0.f;
											needsBreakingCheck = true;
										}
									}
								}
							}
						}
					}

					if (needsBreakingCheck)
					{
						breakDisconnectedParts(sFracturePairs[i].m_fracObj);
					}
				}

			}

		}
	}

	sFracturePairs.clear();

}

std::shared_ptr<ifx::GameObject> btFractureDynamicsWorld::Find(
        std::shared_ptr<ifx::SceneContainer> scene, btCollisionObject* body){
    auto& game_objects = scene->game_objects();
    for(auto& game_object : game_objects){
        auto rigid_components = game_object->GetComponents
                (std::move(ifx::GameComponentType::PHYSICS));
        if(rigid_components.size() == 1){
            std::shared_ptr<ifx::RigidBody> rigid_body
                    = std::static_pointer_cast<ifx::RigidBody>
                            (rigid_components[0]);
            if(rigid_body->rigid_body_bt().get() == body){
                return game_object;
            }
        }
    }
    return nullptr;
}
#include "factory/render_object_factory.h"

#include "graphics/rendering/shadows/shadow_mapping.h"
#include <math/math_ifx.h>
#include <factory/model_factory.h>
#include <factory/program_factory.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/instanced_render_object.h>

#include <GLFW/glfw3.h>
#include <graphics/rendering/renderer.h>
#include <graphics/factory/scene_factory.h>
#include <factory/texture_factory.h>

namespace ifx {

RenderObjectFactory::RenderObjectFactory() {}

RenderObjectFactory::~RenderObjectFactory() {}

/*
RenderObject *RenderObjectFactory::loadBicubicBezierSurfaceC0Object() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0),
                               bicubicBezierSurfaceC0Model);
    float scaleFactor = 4.0f;

    renderObject->moveTo(glm::vec3(10.0f, 0.0f, 50.0f));
    renderObject->rotateTo(glm::vec3(-90.0f, 0.0f, 0.0f));
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadBicubicBezierPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0),
                               bicubicBezierPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(10.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadBicubicBezierBowlPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0),
                               bicubicBezierBowlPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(20.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadBicubicBezierAsymmetricPatchObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0),
                               bicubicBezierAsymmetricPatchModel);
    float scaleFactor = 4.0f;

    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(30.0f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadSquareObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), squareModel);
    float scaleFactor = 4.0f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(1.5f, 0.0f, 0.0f));
    //renderObject->rotateTo(glm::vec3(0, 90.0f, 0));

    return renderObject;
}

RenderObject *RenderObjectFactory::loadCubeObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), cubeModel);

    return renderObject;
}

RenderObject *RenderObjectFactory::loadCubemapObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), cubeMapModel);
    float scaleFactor = 10.0f;
    renderObject->scale(glm::vec3(scaleFactor,
                                  scaleFactor,
                                  scaleFactor));
    return renderObject;
}

RenderObject *RenderObjectFactory::loadLampObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), lampModel);

    return renderObject;
}

RenderObject* RenderObjectFactory::loadNanosuitObject(){
    ProgramFactory program_factory;

    Program* nano_program = program_factory.loadBumpMappingProgram();
    Program* normal_vision_program = program_factory.LoadNormalVisionProgram();

    Model* nanosuitModel = ModelFactory::LoadNanoSuitModel();

    RenderObject* renderObject
            = new RenderObject(ObjectID(0), nanosuitModel);

    renderObject->addProgram(nano_program);
    renderObject->addProgram(normal_vision_program);

    float scaleFactor = 0.005f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}*/

}
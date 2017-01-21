#include "graphics/factory/render_object_factory.h"

#include "graphics/rendering/shadows/shadow_mapping.h"
#include <math/math_ifx.h>
#include <graphics/factory/model_factory.h>
#include <graphics/factory/program_factory.h>
#include <graphics/rendering/fbo_rendering/fbo_renderer.h>
#include <graphics/rendering/instanced_render_object.h>

#include <GLFW/glfw3.h>
#include <graphics/rendering/renderer.h>
#include <graphics/factory/scene_factory.h>
#include <graphics/factory/texture_factory.h>

namespace ifx{

RenderObjectFactory::RenderObjectFactory() {}

RenderObjectFactory::~RenderObjectFactory() {}

std::unique_ptr<RenderObject> RenderObjectFactory::CreateRoom(){
    std::shared_ptr<Program> program = ProgramFactory().LoadMainProgram();
    std::shared_ptr<Model> room_model = ModelFactory::LoadRoomModel();

    auto render_object
            = std::unique_ptr<RenderObject>(new RenderObject(ObjectID(0),
                                                             room_model));
    render_object->addProgram(program);
    float scaleFactor = 2.0f;
    render_object->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    render_object->SetBeforeRender([](const Program* program){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    });
    render_object->SetAfterRender([](const Program* program){
        glDisable(GL_CULL_FACE);
    });

    return render_object;
}

std::unique_ptr<RenderObject> RenderObjectFactory::CreateSpring(){
    std::shared_ptr<Program> program = ProgramFactory().LoadMainProgram();

    std::string local_path = "spring3/spring.stl";
    auto model = ModelFactory::LoadModel(
            Resources::GetInstance().GetResourcePath(local_path,
                                                     ResourceType::MODEL));

    auto render_object
            = std::unique_ptr<RenderObject>(new RenderObject(ObjectID(0),
                                                             model));
    render_object->addProgram(program);
    float scale_factor = 0.022f;
    float scale_factor_y = 0.06f;
    render_object->scale(glm::vec3(scale_factor, scale_factor_y, scale_factor));
    render_object->moveTo(glm::vec3(0.0f, 0.4f, 0.0f));

    return render_object;
}

std::unique_ptr<RenderObject> RenderObjectFactory::CreateMassSpring(){
    std::shared_ptr<Program> program = ProgramFactory().LoadMainProgram();

    std::string local_path = "weight/100t_weight.obj";
    auto model = ModelFactory::LoadModel(
            Resources::GetInstance().GetResourcePath(local_path,
                                                     ResourceType::MODEL));

    auto render_object
            = std::unique_ptr<RenderObject>(new RenderObject(ObjectID(0),
                                                             model));
    render_object->addProgram(program);
    float scale_factor = 0.025f;
    render_object->scale(glm::vec3(scale_factor, scale_factor, scale_factor));
    render_object->moveTo(glm::vec3(0.0f, 0.0f, 0.0f));
    render_object->rotateTo(glm::vec3(0.0f, 90.0f, 0.0f));

    return render_object;
}

RenderObject* RenderObjectFactory::CreateAsteroidField(){
    std::shared_ptr<Program> program = ProgramFactory().LoadInstancedProgram();

    std::shared_ptr<Model> model = ModelFactory::LoadAsteroidModel();

    InstancedData instanced_data;
    instanced_data.data_count = 10000;
    instanced_data.model_matrices.resize(instanced_data.data_count);

    srand(glfwGetTime()); // initialize random seed
    GLfloat radius = 2.5;
    GLfloat offset = 1.0f;
    for(GLuint i = 0; i < instanced_data.data_count; i++) {
        glm::mat4 model;
        // 1. Translation: displace along circle with 'radius' in range [-offset, offset]
        GLfloat angle = (GLfloat)i / (GLfloat)instanced_data.data_count * 360.0f;
        GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
        GLfloat x = sin(angle) * radius + displacement;
        displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
        GLfloat y = displacement * 0.4f; // y value has smaller displacement
        displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
        GLfloat z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));
        // 2. Scale: Scale between 0.05 and 0.25f
        GLfloat scale = (rand() % 5) / 100.0f + 0.05;
        model = glm::scale(model, glm::vec3(scale));
        // 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
        GLfloat rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
        // 4. Now add to list of matrices
        instanced_data.model_matrices[i] = model;
    }

    InstancedRenderObject* instanced_render_object
            = new InstancedRenderObject(ObjectID(0), model, instanced_data);
    instanced_render_object->addProgram(program);

    return instanced_render_object;
}

RenderObject* RenderObjectFactory::CreateAsteroid(){
    std::shared_ptr<Program> program
            = ProgramFactory().loadBumpMappingProgram();
    std::shared_ptr<Model> model = ModelFactory::LoadAsteroidModel();

    RenderObject* renderObject
            = new RenderObject(ObjectID(0), model);

    renderObject->addProgram(program);

    float scaleFactor = 0.05f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    return renderObject;
}

std::unique_ptr<RenderObject> RenderObjectFactory::CreateNanosuitObject(){
    std::shared_ptr<Program> nano_program = ProgramFactory().LoadMainProgram();
    std::shared_ptr<Program> normal_vision_program = ProgramFactory().LoadNormalVisionProgram();
    std::shared_ptr<Model> nanosuitModel = ModelFactory::LoadNanoSuitModel();

    auto renderObject
            = std::unique_ptr<RenderObject>(new RenderObject(ObjectID(0),
                                                             nanosuitModel));

    renderObject->addProgram(nano_program);
    //renderObject->addProgram(normal_vision_program);

    float scaleFactor = 0.05f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(2,0,2));

    return renderObject;
}

std::unique_ptr<RenderObject> RenderObjectFactory::CreateFloor(){
    ProgramFactory program_factory;

    std::shared_ptr<Program> nano_program = program_factory.LoadMainProgram();
    //Program* normal_vision_program = program_factory.LoadNormalVisionProgram();

    std::shared_ptr<Model> nanosuitModel = ModelFactory::LoadFloorModel();

    auto renderObject
            = std::unique_ptr<RenderObject>(new RenderObject(ObjectID(0,
                                                                      "Floor"),
                                                     nanosuitModel));

    renderObject->addProgram(nano_program);
    //renderObject->addProgram(normal_vision_program);

    float scaleFactor = 5.005f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->rotateTo(glm::vec3(90, 0, 0));

    return renderObject;
}

std::unique_ptr<RenderObject> RenderObjectFactory::CreateLampObject(){
    ProgramFactory program_factory;

    std::shared_ptr<Program> nano_program = program_factory.loadLampProgram();
    //Program* normal_vision_program = program_factory.LoadNormalVisionProgram();

    std::shared_ptr<Model> nanosuitModel = ModelFactory::LoadLampModel();

    auto renderObject
            = std::unique_ptr<RenderObject>(new RenderObject(ObjectID(0),
                                                             nanosuitModel));

    renderObject->addProgram(nano_program);

    float scaleFactor = 0.05f;
    renderObject->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    renderObject->moveTo(glm::vec3(0, 0.3, 0));

    return renderObject;
}

std::shared_ptr<RenderObject> RenderObjectFactory::CreateCube(){
    std::shared_ptr<Model> model = ModelFactory::LoadCubeModel();
    std::shared_ptr<Program> program = ProgramFactory().LoadMainProgram();

    auto renderObject = std::shared_ptr<RenderObject>(
            new RenderObject(ObjectID(0), model));
    renderObject->addProgram(program);

    return renderObject;
}

std::shared_ptr<RenderObject> RenderObjectFactory::CreateLine(
        const glm::vec3& p1, const glm::vec3& p2){
    auto material = std::shared_ptr<ifx::Material>(new ifx::Material());
    glm::vec3 color(0, 0, 255);
    material->diffuse = ifx::TextureFactory().CreateSolidColorTexture(
            color, ifx::TextureTypes::DIFFUSE);
    material->specular = ifx::TextureFactory().CreateSolidColorTexture(
            color, ifx::TextureTypes::SPECULAR);

    auto model = ifx::ModelFactory::CreateLine(p1, p2);
    model->getMesh(0)->material(material);
    auto program = ifx::ProgramFactory().LoadMainProgram();

    auto render_object
            = std::shared_ptr<ifx::RenderObject>(
                    new ifx::RenderObject(ObjectID(0),model));
    render_object->addProgram(program);

    render_object->SetBeforeRender([](const Program* program){
        glLineWidth(6);
    });
    render_object->SetAfterRender([](const Program* program){
        glLineWidth(1);
    });

    return render_object;
}

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
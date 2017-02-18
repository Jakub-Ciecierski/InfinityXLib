#include <game/game_loop.h>
#include <game/factory/game_loop_factory.h>
#include <graphics/factory/render_object_factory.h>
#include <graphics/rendering/renderer.h>
#include <game/factory/game_factory.h>
#include <game/game.h>
#include <game/scene_container.h>
#include <game/game_object.h>
#include <graphics/factory/scene_factory.h>

#include <graphics/lighting/light_source.h>
#include <graphics/lighting/types/light_directional.h>
#include <graphics/lighting/types/light_spotlight.h>

#include <graphics/rendering/camera/camera.h>
#include <engine_gui/factory/engine_gui_factory.h>
#include <graphics/rendering/renderer.h>
#include <engine_gui/engine_gui.h>
#include <example_gui.h>
#include <graphics/shaders/loaders/program_loader.h>
#include <graphics/model_loader/model_loader.h>

std::shared_ptr<ifx::LightDirectional> CreateDirectionalLight();
std::shared_ptr<ifx::LightSpotlight> CreateSpotLight();
std::shared_ptr<ifx::GameObject> CreateCyborg(
        std::shared_ptr<ifx::SceneContainer> scene);

std::shared_ptr<ifx::LightDirectional> CreateDirectionalLight(){
    ifx::LightParams light;

    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
/*
    auto light_source = std::shared_ptr<ifx::LightDirectional>(
            new ifx::LightDirectional(light));
*/
    auto light_source = std::shared_ptr<ifx::LightDirectional>(
            new ifx::LightDirectional(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));

    light_source->moveTo(glm::vec3(0.0f, 2.5f, 0.0f));
    light_source->LookAt(glm::vec3(0,0,0));

    return light_source;
}

std::shared_ptr<ifx::LightSpotlight> CreateSpotLight(){
    ifx::LightParams light;

    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
/*
    auto light_source = std::shared_ptr<ifx::LightDirectional>(
            new ifx::LightDirectional(light));
*/
    auto light_source = std::shared_ptr<ifx::LightSpotlight>(
            new ifx::LightSpotlight(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));

    light_source->moveTo(glm::vec3(0.0f, 2.5f, 0.0f));
    light_source->LookAt(glm::vec3(0,0,0));

    return light_source;
}

std::shared_ptr<ifx::GameObject> CreateCyborg(
        std::shared_ptr<ifx::SceneContainer> scene){
    ifx::Resources& resources = ifx::Resources::GetInstance();
    std::string vertex_path =
            resources.GetResourcePath("main/normal_mapping/main.vs",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("main/normal_mapping/main.fs",
                                      ifx::ResourceType::SHADER);
    auto program = ProgramLoader().CreateProgram(vertex_path,
                                                 fragment_path);
    std::string model_path = ifx::Resources::GetInstance().GetResourcePath
            ("cyborg/cyborg.obj", ifx::ResourceType::MODEL);
    auto model = ifx::ModelLoader(model_path).loadModel();

    auto render_object
            = std::shared_ptr<ifx::RenderObject>(
                    new ifx::RenderObject(ObjectID(0), model));

    render_object->addProgram(program);

    float scaleFactor = 0.5f;
    render_object->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    auto game_object = scene->CreateAndAddEmptyGameObject();
    game_object->Add(render_object);

    return game_object;
}

int main() {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();
    auto scene = game->scene();
    auto game_object1 = scene->CreateAndAddEmptyGameObject();
    auto game_object2 = scene->CreateAndAddEmptyGameObject();
    auto game_object3 = scene->CreateAndAddEmptyGameObject();
    auto game_object4 = scene->CreateAndAddEmptyGameObject();

    auto lamp = ifx::RenderObjectFactory().CreateLampObject();
    lamp->moveTo(glm::vec3(0.0f, 2.7f, 0.0f));

    game_object1->Add(ifx::RenderObjectFactory().CreateFloor());

    game_object2->Add(std::move(lamp));
    game_object2->Add(CreateSpotLight());
    game_object2->Add(CreateDirectionalLight());

    game_object3->Add(ifx::RenderObjectFactory().CreateNanosuitObject());
    game_object4->Add(
            ifx::SceneFactory().CreateCamera(game->game_loop()->renderer()->window()));

    CreateCyborg(game->scene());

    auto gui = std::shared_ptr<ExampleGUI>(
            new ExampleGUI(
                    game->game_loop()->renderer()->window()->getHandle(),
                    game->scene(),
                    game->game_loop()->physics_simulation()));
    game->game_loop()->renderer()->SetGUI(gui);
    game->game_loop()->renderer()->SetRenderingType
            (ifx::RenderingType::FBO_TEXTURE);
    game->Start();
}

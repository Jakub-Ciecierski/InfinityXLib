#include <game/game_loop.h>
#include <game/factory/game_loop_factory.h>
#include <graphics/factory/render_object_factory.h>
#include <graphics/rendering/renderer.h>
#include <game/factory/game_factory.h>
#include <game/game.h>
#include <game/scene_container.h>
#include <object/game_object.h>
#include <graphics/factory/scene_factory.h>
#include <graphics/lighting/light_source.h>
#include <graphics/lighting/types/light_directional.h>
#include <graphics/lighting/types/light_spotlight.h>

#include <graphics/rendering/camera/camera.h>
#include <engine_gui/factory/engine_gui_factory.h>
#include <graphics/rendering/renderer.h>
#include <engine_gui/engine_gui.h>
#include <example_gui.h>

std::shared_ptr<ifx::LightDirectional> CreateDirectionalLight();

std::shared_ptr<ifx::LightDirectional> CreateDirectionalLight(){
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

int main() {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto game_object1 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto game_object2 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto game_object3 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto game_object4 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());

    auto lamp = ifx::RenderObjectFactory().CreateLampObject();
    lamp->moveTo(glm::vec3(0.0f, 2.7f, 0.0f));

    game_object1->Add(ifx::RenderObjectFactory().CreateFloor());

    game_object2->Add(std::move(lamp));
    game_object2->Add(CreateDirectionalLight());

    game_object3->Add(ifx::RenderObjectFactory().CreateNanosuitObject());
    game_object4->Add(
            ifx::SceneFactory().CreateCamera(game->game_loop()->renderer()->window()));

    game->scene()->Add(game_object1);
    game->scene()->Add(game_object2);
    game->scene()->Add(game_object3);
    game->scene()->Add(game_object4);

    auto gui = std::shared_ptr<ExampleGUI>(
            new ExampleGUI(
                    game->game_loop()->renderer()->window()->getHandle(),
                    game->scene()));
    game->game_loop()->renderer()->SetGUI(gui);

    game->Start();
}

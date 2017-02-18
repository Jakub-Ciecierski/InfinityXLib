#include "gtest/gtest.h"

#include <game/factory/game_factory.h>
#include <game/game.h>
#include <game/game_loop.h>
#include <game/scene_container.h>

#include <object/render_object.h>
#include <game/game_object.h>

#include <graphics/lighting/types/light_point.h>
#include <graphics/lighting/light_group.h>
#include <graphics/rendering/camera/camera.h>
#include <graphics/rendering/renderer.h>
#include <graphics/rendering/scene_renderer.h>

#include <memory>

TEST(Game, GameFactory_Default) {

    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();
}

TEST(Game,
     GameObjectWithTwoComponents_SceneRendererHasRenderObjectProperCount) {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game1 = game_factory->Create();

    auto render_object = std::shared_ptr<ifx::RenderObject>(
            new ifx::RenderObject(ObjectID(2), nullptr));
    auto light = std::shared_ptr<ifx::LightPoint>(
            new ifx::LightPoint(ifx::LightParams{}));
    auto game_object = game1->scene()->CreateAndAddEmptyGameObject();

    game_object->Add(render_object);
    game_object->Add(light);


    auto scene_renderer = game1->game_loop()->renderer()->scene_renderer();

    unsigned int expected_value = 1;

    EXPECT_EQ(expected_value, scene_renderer->render_objects().size());
}

TEST(Game,
     GameObjectWithTwoComponents_SceneRendererHasLightProperCount) {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto render_object = std::shared_ptr<ifx::RenderObject>(
            new ifx::RenderObject(ObjectID(2), nullptr));
    const auto light = std::shared_ptr<ifx::LightPoint>(
            new ifx::LightPoint(ifx::LightParams{}));

    auto game_object = game->scene()->CreateAndAddEmptyGameObject();

    game_object->Add(render_object);
    game_object->Add(light);

    auto scene_renderer = game->game_loop()->renderer()->scene_renderer();

    unsigned int expected_value = 1;

    EXPECT_EQ(expected_value,
              scene_renderer->light_group()->lights().size());
}

TEST(Game,
     GameObjecstWithTwoComponents_SceneRendererHasRenderObjectProperCount) {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto render_object1 = std::shared_ptr<ifx::RenderObject>(
            new ifx::RenderObject(ObjectID(2), nullptr));
    auto render_object2 = std::shared_ptr<ifx::RenderObject>(
            new ifx::RenderObject(ObjectID(2), nullptr));
    auto game_object1 = game->scene()->CreateAndAddEmptyGameObject();
    auto game_object2 = game->scene()->CreateAndAddEmptyGameObject();

    game_object1->Add(render_object1);
    game_object2->Add(render_object2);

    auto scene_renderer = game->game_loop()->renderer()->scene_renderer();

    unsigned int expected_value = 2;

    EXPECT_EQ(expected_value, scene_renderer->render_objects().size());
}

TEST(Game,
     GameObjecstWithTwoComponents_RemoveOne_ProperCount) {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto render_object1 = std::shared_ptr<ifx::RenderObject>(
            new ifx::RenderObject(ObjectID(2), nullptr));
    auto render_object2 = std::shared_ptr<ifx::RenderObject>(
            new ifx::RenderObject(ObjectID(2), nullptr));

    auto game_object1 = game->scene()->CreateAndAddEmptyGameObject();
    auto game_object2 = game->scene()->CreateAndAddEmptyGameObject();

    game_object1->Add(render_object1);
    game_object2->Add(render_object2);

    auto scene = game->scene();
    scene->Add(game_object1);
    scene->Add(game_object2);

    scene->Remove(game_object1);

    auto scene_renderer = game->game_loop()->renderer()->scene_renderer();

    unsigned int expected_value = 1;

    EXPECT_EQ(expected_value, scene_renderer->render_objects().size());
}
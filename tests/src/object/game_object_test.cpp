#include "gtest/gtest.h"

#include <game/game_object.h>
#include <object/game_component.h>
#include <game/factory/game_factory.h>
#include <game/game.h>
#include <game/scene_container.h>

TEST(GameObject, GameObject_RemoveExistingComponent_ReturnedTrue) {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto game_component = std::shared_ptr<ifx::GameComponent>(
            new ifx::GameComponent(ifx::GameComponentType::RENDER));
    auto game_object = game->scene()->CreateAndAddEmptyGameObject();

    game_object->Add(game_component);

    const bool expected_value = true;
    bool actual_value = game_object->Remove(game_component);

    EXPECT_EQ(expected_value, actual_value);
}

TEST(GameObject, GameObject_RemoveNonExistingComponent_ReturnedFalse) {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto game_component = std::shared_ptr<ifx::GameComponent>(
            new ifx::GameComponent(ifx::GameComponentType::RENDER));

    auto game_object = game->scene()->CreateAndAddEmptyGameObject();

    const bool expected_value = false;
    bool actual_value = game_object->Remove(game_component);

    EXPECT_EQ(expected_value, actual_value);
}

TEST(GameObject, GameObject_GetComponentsByType_CorrectCount) {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto game_component1 = std::shared_ptr<ifx::GameComponent>(
            new ifx::GameComponent(ifx::GameComponentType::RENDER));
    auto game_component2 = std::shared_ptr<ifx::GameComponent>(
            new ifx::GameComponent(ifx::GameComponentType::RENDER));

    auto game_object = game->scene()->CreateAndAddEmptyGameObject();

    game_object->Add(game_component1);
    game_object->Add(game_component2);

    auto game_components_render
            = game_object->GetComponents(ifx::GameComponentType::RENDER);

    const unsigned int expected_value = 2;

    EXPECT_EQ(expected_value, game_components_render.size());
}
#include "gtest/gtest.h"

#include <memory>

#include <game/scene_container.h>
#include <game/factory/scene_container_factory.h>
#include <game/game_object.h>
#include <game/game.h>
#include <game/factory/game_factory.h>

TEST(Game, SceneContainer_RemoveExistingObject_ReturnedTrue) {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto game_object = game->scene()->CreateAndAddEmptyGameObject();

    const bool expected_value = true;
    bool actual_value = game->scene()->Remove(game_object);

    EXPECT_EQ(expected_value, actual_value);
}

TEST(Game, SceneContainer_RemoveNonExistingObject_ReturnedFalse) {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto game_object = game->scene()->CreateGameObject();

    const bool expected_value = false;
    bool actual_value = game->scene()->Remove(game_object);

    EXPECT_EQ(expected_value, actual_value);
}
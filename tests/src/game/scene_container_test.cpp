#include "gtest/gtest.h"

#include <memory>

#include <game/scene_container.h>
#include <game/factory/scene_container_factory.h>
#include <object/game_object.h>

TEST(Game, SceneContainer_RemoveExistingObject_ReturnedTrue) {
    auto scene_container = ifx::SceneContainerFactory().Create(nullptr,
                                                               nullptr);

    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    scene_container->Add(game_object);

    const bool expected_value = true;
    bool actual_value = scene_container->Remove(game_object);

    EXPECT_EQ(expected_value, actual_value);
}

TEST(Game, SceneContainer_RemoveNonExistingObject_ReturnedFalse) {
    auto scene_container = ifx::SceneContainerFactory().Create(nullptr,
                                                               nullptr);

    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());

    const bool expected_value = false;
    bool actual_value = scene_container->Remove(game_object);

    EXPECT_EQ(expected_value, actual_value);
}
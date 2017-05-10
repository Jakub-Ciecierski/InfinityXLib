#include "gtest/gtest.h"

#include <memory>

#include <controls_tests/control_context_impl.h>
#include <controls_tests/controlable_object.h>

#include <controls/controller/controller_container.h>
#include <controls/controls.h>
#include <controls/controller/factory/controller_container_factory.h>
#include <controls/factory/controls_factory.h>
#include <controls/command/command.h>
#include <controls/command/commands/keyboard_command.h>
#include <controls/command/commands/mouse_command.h>
#include <controls/command/factory/command_factory.h>
#include <controls/controller/controllers/keyboard_controller.h>
#include <controls/controller/controllers/mouse_controller.h>
#include <controls/controller/events/keyboard_controller_event.h>
#include <controls/controller/events/mouse_controller_event.h>
#include <controls/controller/events/mouse_scroll_controller_event.h>

class ControlsTest : public testing::Test{
protected:

    virtual void SetUp(){
        auto control_context = std::make_shared<ifx::ControlContextImpl>();
        controls_ = ifx::ControlsFactory().Create(control_context);
    }

    std::shared_ptr<ifx::Command> CreateKeyboardCommand(
            std::shared_ptr<ifx::ControlableObject> object){
        ifx::CommandFunction function
                = [](std::shared_ptr<ifx::Controller>,
                     std::shared_ptr<ifx::Controlable> obj){
                    std::static_pointer_cast<ifx::ControlableObject>(obj)->value(true);
                };
        auto command = ifx::CommandFactory(controls_).CreateKeyboardCommand(
                object,
                function,
                ifx::KeyboardControllerEventType {
                        ifx::KeyboardControllerKeyType::A,
                        ifx::KeyboardControllerCallbackType::PRESSED
                }
        );
        return command;
    }

    std::shared_ptr<ifx::Command> CreateMouseCommand(
            std::shared_ptr<ifx::ControlableObject> object){
        ifx::CommandFunction function
                = [](std::shared_ptr<ifx::Controller>,
                     std::shared_ptr<ifx::Controlable> obj){
                    std::static_pointer_cast<ifx::ControlableObject>(obj)->value(true);
                };
        auto command = ifx::CommandFactory(controls_).CreateMouseCommand(
                object,
                function,
                ifx::MouseControllerEventType {
                        ifx::MouseControllerKeyType::MOUSE_LEFT,
                        ifx::MouseControllerCallbackType::PRESSED
                }
        );
        return command;
    }

    std::shared_ptr<ifx::Command> CreateMouseScrollCommand(
            std::shared_ptr<ifx::ControlableObject> object){
        ifx::CommandFunction function
                = [](std::shared_ptr<ifx::Controller>,
                     std::shared_ptr<ifx::Controlable> obj){
                    std::static_pointer_cast<ifx::ControlableObject>(obj)->value(true);
                };
        auto command = ifx::CommandFactory(controls_).CreateMouseCommand(
                object,
                function,
                ifx::MouseControllerEventType {
                        ifx::MouseControllerKeyType::MOUSE_SCROLL,
                        ifx::MouseControllerCallbackType::SCROLL_ACTIVE
                }
        );
        return command;
    }

    std::shared_ptr<ifx::Controls> controls_;
};

TEST_F(ControlsTest, ControlsFactory_Create_SuccesfullyCreatesObject){
    ASSERT_TRUE(controls_ != nullptr);
}

TEST_F(ControlsTest, ControllerContainer_Created_KeyboardNotNull){
    auto input_container = ifx::ControllerContainerFactory().Create();

    ASSERT_TRUE(input_container->keyboard_controller() != nullptr);
}

TEST_F(ControlsTest, ControllerContainer_Created_MouseNotNull){
    auto input_container = ifx::ControllerContainerFactory().Create();

    ASSERT_TRUE(input_container->mouse_controller() != nullptr);
}

TEST_F(ControlsTest, Command_CommandExecuted_ObjectValueChanged){
    auto object = std::make_shared<ifx::ControlableObject>();
    auto command = CreateKeyboardCommand(object);

    EXPECT_EQ(false, object->value());
    command->Execute();
    EXPECT_EQ(true, object->value());
}

TEST_F(ControlsTest,
       Command_ControlsUpdatedWithoutSatisfyingCondition_ValueNotChanged){
    auto object = std::make_shared<ifx::ControlableObject>();
    auto command = CreateKeyboardCommand(object);

    controls_->AddCommand(command);

    EXPECT_EQ(false, object->value());
    controls_->Update();
    EXPECT_EQ(false, object->value());
}

TEST_F(ControlsTest,
       Command_ControlsUpdatedWithSatisfyingCondition_ValueChanged){
    auto object = std::make_shared<ifx::ControlableObject>();
    auto command = CreateKeyboardCommand(object);

    controls_->AddCommand(command);

    auto event = controls_->controller_container()->keyboard_controller()
            ->GetEvent(ifx::KeyboardControllerKeyType::A);

    event->OnPressed();

    EXPECT_EQ(false, object->value());
    controls_->Update();
    EXPECT_EQ(true, object->value());
}

TEST_F(ControlsTest,
       Command_ControlsUpdatedAfterRemovingCommand_ValueNotChanged){
    auto object = std::make_shared<ifx::ControlableObject>();
    auto command = CreateKeyboardCommand(object);

    controls_->AddCommand(command);

    auto event = controls_->controller_container()->keyboard_controller()
            ->GetEvent(ifx::KeyboardControllerKeyType::A);
    event->OnPressed();

    controls_->RemoveCommand(command);

    EXPECT_EQ(false, object->value());
    controls_->Update();
    EXPECT_EQ(false, object->value());
}

TEST_F(ControlsTest,
       Command_MouseCommand_ValueChanged){
    auto object = std::make_shared<ifx::ControlableObject>();
    auto command = CreateMouseCommand(object);

    controls_->AddCommand(command);

    auto event = controls_->controller_container()->mouse_controller()
            ->GetEvent(ifx::MouseControllerKeyType::MOUSE_LEFT);

    event->OnPressed();

    EXPECT_EQ(false, object->value());
    controls_->Update();
    EXPECT_EQ(true, object->value());
}

TEST_F(ControlsTest,
       Command_MouseCommand_ValueNotChanged){
    auto object = std::make_shared<ifx::ControlableObject>();
    auto command = CreateMouseCommand(object);

    controls_->AddCommand(command);

    auto event = controls_->controller_container()->mouse_controller()
            ->GetEvent(ifx::MouseControllerKeyType::MOUSE_LEFT);

    EXPECT_EQ(false, object->value());
    controls_->Update();
    EXPECT_EQ(false, object->value());
}

TEST_F(ControlsTest,
       Command_MouseScrollCommandActivated_ValueChanged){
    auto object = std::make_shared<ifx::ControlableObject>();
    auto command = CreateMouseScrollCommand(object);

    controls_->AddCommand(command);

    auto event = controls_->controller_container()->mouse_controller()
            ->GetEvent(ifx::MouseControllerKeyType::MOUSE_SCROLL);

    std::static_pointer_cast<ifx::MouseScrollControllerEvent>(event)
            ->SetActivated(true);

    EXPECT_EQ(false, object->value());
    controls_->Update();
    EXPECT_EQ(true, object->value());
}
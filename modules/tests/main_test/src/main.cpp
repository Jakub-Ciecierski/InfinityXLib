#include <game_loop/game_loop.h>
#include <factory/render_object_factory.h>
#include <rendering/renderer.h>



int main() {
    ifx::GameLoop game_loop(
            std::move(ifx::RenderObjectFactory().CreateRenderer()));

    game_loop.renderer()->scene()->AddRenderObject(
            ifx::RenderObjectFactory().CreateFloor()
    );
    game_loop.renderer()->scene()->AddRenderObject(
            ifx::RenderObjectFactory().CreateNanosuitObject()
    );
    auto lamp = ifx::RenderObjectFactory().CreateLampObject();
    lamp->moveTo(glm::vec3(2.5f, 2.7f, 0.0f));
    game_loop.renderer()->scene()->AddRenderObject(
            std::move(lamp)
    );

    game_loop.Start();
}


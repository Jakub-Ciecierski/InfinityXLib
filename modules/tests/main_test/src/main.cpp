#include <game_loop/game_loop.h>
#include <factory/render_object_factory.h>
#include <rendering/renderer.h>

int main() {
    ifx::GameLoop game_loop(
            std::move(ifx::RenderObjectFactory().CreateRenderer()));

    game_loop.Start();
}


#ifndef PROJECT_FBO_RENDERER_H
#define PROJECT_FBO_RENDERER_H

#include <memory>

namespace ifx {

class Mesh;
class Window;
class FBO;
class Program;

/**
 * The viewport does not need to be changed since the window's dimensions
 * are used.
 * Creates FBO with Color and Depth buffers.
 * Allows for post-processing effects.
 */
class FBORenderer {
public:

    FBORenderer(Window* window);

    ~FBORenderer();

    Program* program(){return program_.get();}

    void SetProgram(std::shared_ptr<Program> program);

    void Bind();

    void Render();
    void Render(Program* program);

private:
    void initFBO(Window* window);
    void initScreenMesh();

    std::unique_ptr<FBO> fbo_;

    /**
     * The quad mesh which will render the screen.
     */
    std::unique_ptr<Mesh> screenMesh_;

    std::shared_ptr<Program> program_;
};
}

#endif //PROJECT_FBO_RENDERER_H

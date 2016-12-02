#ifndef PROJECT_RENDER_OBJECT_FACTORY_H
#define PROJECT_RENDER_OBJECT_FACTORY_H

#include <object/render_object.h>
#include <memory>

namespace ifx {

class Renderer;
class FBORenderer;
class Window;
class ShadowMapping;

class RenderObjectFactory {
public:

    RenderObjectFactory();
    ~RenderObjectFactory();

    std::unique_ptr<Renderer> CreateRenderer();
    std::unique_ptr<FBORenderer> CreateFBORenderer(Window* window);
    ShadowMapping* CreateShadowMapping();

    std::shared_ptr<RenderObject> CreateQuad(int x = 50, int y = 50);
    std::shared_ptr<RenderObject> CreateAxis();

    std::unique_ptr<RenderObject> CreateRoom();
    std::unique_ptr<RenderObject> CreateSpring();
    std::unique_ptr<RenderObject> CreateMassSpring();

    std::unique_ptr<RenderObject> CreateNanosuitObject();
    std::unique_ptr<RenderObject> CreateFloor();
    std::unique_ptr<RenderObject> CreateLampObject();

    RenderObject* CreateAsteroidField();
    RenderObject* CreateAsteroid();

    /*
    RenderObject* loadBicubicBezierSurfaceC0Object();
    RenderObject* loadBicubicBezierPatchObject();
    RenderObject* loadBicubicBezierBowlPatchObject();
    RenderObject* loadBicubicBezierAsymmetricPatchObject();

    RenderObject* loadSquareObject();
    RenderObject* loadCubeObject();
    RenderObject* loadCubemapObject();
    RenderObject* loadLampObject();
    */
};
}

#endif //PROJECT_RENDER_OBJECT_FACTORY_H

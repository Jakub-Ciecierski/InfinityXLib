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

    std::unique_ptr<RenderObject> CreateRoom();
    std::unique_ptr<RenderObject> CreateSpring();
    std::unique_ptr<RenderObject> CreateMassSpring();

    RenderObject* CreateAsteroidField();
    RenderObject* CreateAsteroid();
    std::unique_ptr<RenderObject> CreateNanosuitObject();

    std::unique_ptr<RenderObject> CreateFloor();

    std::unique_ptr<RenderObject> CreateLampObject();

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
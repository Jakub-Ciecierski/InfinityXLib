#ifndef PROJECT_RENDER_OBJECT_FACTORY_H
#define PROJECT_RENDER_OBJECT_FACTORY_H

#include <graphics/rendering/render_object.h>
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

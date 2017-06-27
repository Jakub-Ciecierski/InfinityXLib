#ifndef PROJECT_GUI_CONTEXT_H
#define PROJECT_GUI_CONTEXT_H

namespace ifx {

class GUIContext {
public:

    GUIContext();

    virtual ~GUIContext();

    virtual bool Init(void* native_window) = 0;
    virtual bool Terminate() = 0;

    virtual void NewFrame() = 0;
    virtual void Render() = 0;

private:
};
}


#endif //PROJECT_GUI_CONTEXT_H

#ifndef PROJECT_GUI_SUBSYSTEM_H
#define PROJECT_GUI_SUBSYSTEM_H

namespace ifx {

class GUIPart {
public:

    GUIPart();

    virtual ~GUIPart();

    virtual void Render() = 0;

private:
};
}


#endif //PROJECT_GUI_SUBSYSTEM_H

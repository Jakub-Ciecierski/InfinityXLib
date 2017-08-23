#ifndef PROJECT_GUI_TMP_H
#define PROJECT_GUI_TMP_H

#include <common/updatable.h>

#include <memory>
#include <vector>

namespace ifx {

class GUIContext;
class GUIPart;
class ControlContext;

class GUI : public Updatable {
public:

    GUI(std::shared_ptr<GUIContext> context);

    virtual ~GUI() = default;

    virtual void Update(float time_delta = 0) override;

    bool Terminate();

    void AddGUIPart(std::shared_ptr<GUIPart> gui_part);
private:
    std::vector<std::shared_ptr<GUIPart>> gui_parts_;
    std::shared_ptr<GUIContext> context_;

    bool is_init_;
};
}


#endif //PROJECT_GUI_TMP_H

#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

#include <string>

namespace ifx {

class View {
public:
    View(std::string name);
    virtual ~View() = default;

    bool is_window_focused() { return is_window_focused_; }
    void is_window_focused(bool value) { is_window_focused_ = value; }

    virtual bool Terminate();

    const std::string &name() { return name_; }

    virtual void Render() = 0;

    virtual void OnViewEnter();
    virtual void OnViewLeave();

private:
    std::string name_;

    bool is_window_focused_;
};

}

#endif //PROJECT_VIEW_H

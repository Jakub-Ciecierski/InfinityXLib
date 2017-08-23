#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

#include <string>

namespace ifx {

class View {
public:
    View(std::string name);
    virtual ~View() = default;

    virtual bool Terminate();

    const std::string& name(){return name_;}

    virtual void Render() = 0;
private:
    std::string name_;
};

}

#endif //PROJECT_VIEW_H

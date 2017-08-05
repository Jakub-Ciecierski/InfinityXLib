#ifndef PROJECT_WINDOW_VIEW_H
#define PROJECT_WINDOW_VIEW_H

#include <string>
#include <memory>
#include <vector>

typedef int ImGuiWindowFlags;

namespace ifx{

class View;

class WindowView {
public:
    WindowView(std::string name = "Debug");

    WindowView(std::vector<std::shared_ptr<View>> view,
               std::string name = "Debug");
    WindowView(std::shared_ptr<View> view,
               std::string name = "Debug");

    virtual ~WindowView();

    void show(bool val){show_ = val;}
    bool* show(){return &show_;}

    float width(){
        if(!show_)
            return 0;
        return width_;
    }
    float height(){
        if(!show_)
            return 0;
        return height_;
    }

    const std::string& name(){return name_;}

    virtual void Render();

    void SetFlags(ImGuiWindowFlags flags);

protected:
    //virtual void RenderContent() = 0;
    virtual void RenderContent();

    virtual void FetchSize();

    bool show_;

    float width_;
    float height_;

    std::string name_;

    ImGuiWindowFlags flags_;
private:
    std::vector<std::shared_ptr<View>> views_;
};

}

#endif // PROJECT_WINDOW_VIEW_H
#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

#include <string>

typedef int ImGuiWindowFlags;

namespace ifx{

class View {
public:
    View(std::string name = "Debug");
    virtual ~View();

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
    virtual void RenderContent() = 0;

    virtual void FetchSize();

    bool show_;

    float width_;
    float height_;

    std::string name_;

    ImGuiWindowFlags flags_;
};

}

#endif //PROJECT_VIEW_H

#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

namespace ifx{

class View {
public:
    View();
    virtual ~View();

    void show(bool val){show_ = val;}
    bool* show(){return &show_;}

    virtual void Render() = 0;
protected:
    bool show_;

};

}

#endif //PROJECT_VIEW_H

#ifndef PROJECT_BOTTOM_VIEW_H
#define PROJECT_BOTTOM_VIEW_H

#include <editor/view.h>

namespace ifx {

class BottomView : public View{
public:

    BottomView();

    ~BottomView();

protected:
    virtual void RenderContent() override;

private:
};
}


#endif //PROJECT_BOTTOM_VIEW_H

#ifndef PROJECT_SOFT_BODY_SOLVER_VIEW_H
#define PROJECT_SOFT_BODY_SOLVER_VIEW_H

namespace ifx {

struct SoftBodyEditorObjects;

class SoftBodySolverView {
public:
    SoftBodySolverView() = default;
    ~SoftBodySolverView() = default;

    void Render(SoftBodyEditorObjects& soft_body_objects);

private:
};

}

#endif //PROJECT_SOFT_BODY_SOLVER_VIEW_H

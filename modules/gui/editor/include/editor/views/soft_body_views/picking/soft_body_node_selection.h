#ifndef PROJECT_SOFT_BODY_NODE_SELECTION_H
#define PROJECT_SOFT_BODY_NODE_SELECTION_H

#include <vector>

namespace ifx {

class SoftBodyNodeSelection {
public:
    SoftBodyNodeSelection() = default;
    ~SoftBodyNodeSelection() = default;

    const std::vector<unsigned int>& selected_vertices(){
        return selected_vertices_;
    }

    void Reset();

    void NotifyIntersection(unsigned int index);

    bool IsSelected(unsigned int index);

    void AddSelection(unsigned int selected);

    bool RemoveSelection(unsigned int selected);

private:
    std::vector<unsigned int> selected_vertices_;

};

}

#endif //PROJECT_SOFT_BODY_NODE_SELECTION_H

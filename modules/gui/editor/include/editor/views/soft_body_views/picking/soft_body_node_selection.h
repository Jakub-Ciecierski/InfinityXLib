#ifndef PROJECT_SOFT_BODY_NODE_SELECTION_H
#define PROJECT_SOFT_BODY_NODE_SELECTION_H

#include <vector>

namespace ifx {

enum class SelectionType{
    Ray, Box
};

class SoftBodyNodeSelection {
public:
    SoftBodyNodeSelection() = default;
    ~SoftBodyNodeSelection() = default;

    const std::vector<unsigned int>& selected_vertices() const {
        return selected_vertices_;
    }

    void Reset();

    void NotifyIntersection(unsigned int index, SelectionType type);

    bool IsSelected(unsigned int index);

    void AddSelection(unsigned int selected);

    bool RemoveSelection(unsigned int selected);

    bool IsInputBeginBoxCasting();
    bool IsInputUpdateBoxCasting();
    bool IsInputEndBoxCasting();
    bool IsInputRayCasting();
    bool IsInputShiftModifier();
private:

    std::vector<unsigned int> selected_vertices_;

};

}

#endif //PROJECT_SOFT_BODY_NODE_SELECTION_H

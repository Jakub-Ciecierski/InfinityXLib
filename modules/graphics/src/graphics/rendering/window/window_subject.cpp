#include "graphics/rendering/window/window_subject.h"

#include "graphics/rendering/window/window_observer.h"

namespace ifx {

void WindowSubject::NotifyResize(int width, int height) {
    for (auto &observer : observers_) {
        observer->OnResize(width, height);
    }
}

void WindowSubject::AddObserver(WindowObserver *observer) {
    observers_.push_back(observer);
}

bool WindowSubject::RemoveObserver(WindowObserver *observer) {
    for (unsigned int i = 0; i < observers_.size(); i++) {
        if (observers_[i] == observer) {
            observers_.erase(observers_.begin() + i);
            return true;
        }
    }
    return false;
}

}

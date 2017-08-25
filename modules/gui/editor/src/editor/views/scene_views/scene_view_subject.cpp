#include "editor/views/scene_views/scene_view_subject.h"

#include "editor/views/scene_views/scene_view_observer.h"

namespace ifx{

void SceneViewSubject::AddObserver(
        std::shared_ptr<SceneViewObserver> observer){
    observers_.push_back(observer);
}

bool SceneViewSubject::RemoveObserver(
        std::shared_ptr<SceneViewObserver> observer){
    for(unsigned int i = 0; i < observers_.size(); i++){
        auto shared_observer = observers_[i].lock();
        if(shared_observer && shared_observer == observer){
            observers_.erase(observers_.begin() + i);
            return true;
        }
    }
    return false;
}

void SceneViewSubject::NotifySetSelectedGameObject(
        std::shared_ptr<GameObject> selected_game_object){
    std::vector<std::weak_ptr<SceneViewObserver>> remaining_observers;

    for(auto& observer : observers_){
        auto observer_shared = observer.lock();
        if(observer_shared){
            observer_shared->OnSetSelectedGameObject(selected_game_object);
            remaining_observers.push_back(observer);
        }
    }
    observers_ = remaining_observers;
}

}

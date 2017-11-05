#ifndef PROJECT_UPDATABLE_H
#define PROJECT_UPDATABLE_H

namespace ifx {

struct UpdateTimeDelta{
    float time_delta = 1.0f / 60.0f;
};

struct UpdateTimer{
    float last_time = 0;
    float current_time = 0;
    float total_time = 0;
    float time_since_last_update = 0;
};

class Updatable {
public:
    Updatable() = default;
    Updatable(const UpdateTimeDelta& update_time_delta_);

    virtual ~Updatable() = default;

    float fixed_time_delta(){return update_time_delta_.time_delta;}
    void fixed_time_delta(float fixed_time_delta){
        update_time_delta_.time_delta = fixed_time_delta;}

    virtual void Update(float time_delta);
    bool UpdateFixed();

protected:
    virtual void UpdateFixedContent();

    UpdateTimeDelta update_time_delta_;
private:
    void UpdateTimers();
    bool IsUpdateReady();

    UpdateTimer update_timer_;

};
}

#endif //PROJECT_UPDATABLE_H

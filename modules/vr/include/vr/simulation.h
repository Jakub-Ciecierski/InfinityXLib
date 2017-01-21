#ifndef PROJECT_SIMULATION_H
#define PROJECT_SIMULATION_H

namespace ifx {

struct SimulationTimeData{
    float simulation_length = -1;

    float last_time = 0;
    float current_time = 0;

    float total_time = 0;

    float time_since_last_update = 0;
    const float time_delta = 1.0f / 60.0f;
};

/**
 * Abstract class representing a simple VR Simulation.
 */
class Simulation {
public:

    Simulation();
    virtual ~Simulation();

    SimulationTimeData& time_data(){return time_data_;}

    virtual void Update() = 0;

    bool IsRunning();
    void SetRunning(bool value);

    void Play();
    void Pause();

    virtual void Reset();
protected:
    bool UpdateTime();

    bool running_;

    SimulationTimeData time_data_;
};
}

#endif //PROJECT_SIMULATION_H

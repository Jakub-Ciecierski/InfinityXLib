#ifndef PROJECT_PROFILER_VIEW_H
#define PROJECT_PROFILER_VIEW_H

#include <editor/view.h>
#include <memory>

namespace ifx {

class GameLoop;
class GameUpdater;
class UpdateTimer;

class ProfilerView : public View{
public:

    ProfilerView(std::shared_ptr<GameLoop> game_loop);
    ~ProfilerView() = default;

    virtual void Render() override;
private:
    void RenderProfiler(const GameUpdater& game_updater);

    void RenderSingleProfiler(const std::string &name,
                              const UpdateTimer &timer,
                              double total_time);

    std::shared_ptr<GameLoop> game_loop_;
};
}


#endif //PROJECT_PROFILER_VIEW_H

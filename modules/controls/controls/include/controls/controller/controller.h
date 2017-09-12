#ifndef PROJECT_INPUT_H
#define PROJECT_INPUT_H

#include <vector>
#include <memory>

#include <common/updatable.h>

namespace ifx {

class ControllerEvent;

using ControllerEvents = std::vector<std::shared_ptr<ControllerEvent>>;

class Controller : public Updatable {
public:

    virtual ~Controller();

    const ControllerEvents &events() { return events_; }

    virtual void Update(float time_delta = 0) override;

protected:
    Controller();

    ControllerEvents events_;

};
}

#endif //PROJECT_INPUT_H

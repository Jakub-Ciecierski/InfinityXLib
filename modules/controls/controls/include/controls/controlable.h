#ifndef PROJECT_CONTROLABLE_H
#define PROJECT_CONTROLABLE_H

namespace ifx {

/**
 * Classes that wish to part of a Command system, must be inherited from
 * Controlable interface.
 */
class Controlable {
public:
    virtual ~Controlable(){}

protected:
    Controlable(){}
};
}


#endif //PROJECT_CONTROLABLE_H

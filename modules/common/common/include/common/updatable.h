#ifndef PROJECT_UPDATABLE_H
#define PROJECT_UPDATABLE_H

namespace ifx {

class Updatable {
public:

    Updatable();

    virtual ~Updatable();

    virtual void Update(float time_delta) = 0;
private:
};
}

#endif //PROJECT_UPDATABLE_H

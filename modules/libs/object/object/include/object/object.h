//
// Created by jakub on 5/23/16.
//

#ifndef DUCK_OBJECT_H
#define DUCK_OBJECT_H

#include "object/object_id.h"

#include <string>

class Object {
protected:

    ObjectID id_;

public:

    Object(ObjectID id);
    ObjectID& id() {return id_;}
    void id(ObjectID id){id_ = id;}

    virtual ~Object();

    virtual void update() = 0;

};


#endif //DUCK_OBJECT_H

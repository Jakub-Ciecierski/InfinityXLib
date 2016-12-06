#ifndef DUCK_OBJECT_ID_H
#define DUCK_OBJECT_ID_H

#include <string>

class ObjectID {
public:

    ObjectID(int key);
    ObjectID(int key, std::string name);

    ~ObjectID();

    std::string name(){return name_;}

    bool operator==(const ObjectID& id) const;
    bool operator!=(const ObjectID &id) const;
private:
    int key;
    std::string name_;
};


#endif //DUCK_OBJECT_ID_H

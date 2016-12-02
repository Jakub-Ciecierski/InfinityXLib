//
// Created by jakub on 5/24/16.
//

#include "object/object_id.h"

ObjectID::ObjectID(int key) : key_(key){

}

ObjectID::ObjectID(int key, std::string name) :
    key_(key), name_(name){

}

ObjectID::~ObjectID() {

}

bool ObjectID::operator==(const ObjectID &id) const {
    return id.key_ == this->key_;
}

bool ObjectID::operator!=(const ObjectID &id) const {
    return id.key_ != this->key_;
}
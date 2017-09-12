#include "physics/transformations.h"

namespace ifx {

btTransform IFX2BTTransform(const TransformData &ifx_transform) {
    btTransform bt_transform;

    glm::quat glm_quat(glm::radians(ifx_transform.rotation));
    btQuaternion bt_quat(glm_quat.x, glm_quat.y, glm_quat.z, glm_quat.w);

    bt_transform.setOrigin(
        btVector3(ifx_transform.position.x,
                  ifx_transform.position.y,
                  ifx_transform.position.z));
    bt_transform.setRotation(bt_quat);

    return bt_transform;
}

TransformData BT2IFXTransform(const btTransform &bt_transform) {
    TransformData ifx_transform;

    auto &origin = bt_transform.getOrigin();
    auto rotation_quat = bt_transform.getRotation();
    glm::quat glm_quat = glm::quat(rotation_quat.w(), rotation_quat.x(),
                                   rotation_quat.y(), rotation_quat.z());
    ifx_transform.position = glm::vec3(origin.x(), origin.y(), origin.z());
    ifx_transform.rotation = glm::degrees(glm::eulerAngles(glm_quat));

    return ifx_transform;
}

}

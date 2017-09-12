#ifndef PROJECT_TRANSFORMATIONS_H
#define PROJECT_TRANSFORMATIONS_H

/**
 * Transformation of data between Bullet and InfinityX
 */

#include <LinearMath/btTransform.h>
#include <math/transform.h>

namespace ifx {

btTransform IFX2BTTransform(const TransformData &);
TransformData BT2IFXTransform(const btTransform &);

}

#endif //PROJECT_TRANSFORMATIONS_H

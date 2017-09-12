#ifndef PROJECT_PRINT_MATH_H
#define PROJECT_PRINT_MATH_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ifx {
void PrintVec3(const glm::vec3 &vec);
void PrintMat3(const glm::mat3 &mat);
void PrintMat4(const glm::mat4 &mat);
void PrintQuat(const glm::quat &q);
}

#endif //PROJECT_PRINT_MATH_H

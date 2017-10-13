#include "math/print_math.h"

#include <iostream>

namespace ifx {

void PrintVec3(const glm::vec3 &vec) {
    std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}

void PrintVec4(const glm::vec4 &vec) {
    std::cout << vec.x << ", " << vec.y
              << ", " << vec.z
              << ", " << vec.w
              << std::endl;
}

void PrintMat3(const glm::mat3 &mat) {
    std::cout << mat[0].x << ", " << mat[1].x << ", " << mat[2].x << std::endl;
    std::cout << mat[0].y << ", " << mat[1].y << ", " << mat[2].y << std::endl;
    std::cout << mat[0].z << ", " << mat[1].z << ", " << mat[2].z << std::endl;
}

void PrintMat4(const glm::mat4 &mat) {
    std::cout << mat[0].x << ", " << mat[1].x << ", "
              << mat[2].x << ", " << mat[3].x << std::endl;

    std::cout << mat[0].y << ", " << mat[1].y << ", "
              << mat[2].y << ", " << mat[3].y << std::endl;

    std::cout << mat[0].z << ", " << mat[1].z << ", "
              << mat[2].z << ", " << mat[3].z << std::endl;

    std::cout << mat[0].w << ", " << mat[1].w << ", "
              << mat[2].w << ", " << mat[3].w << std::endl;

    std::cout << std::endl;
}

void PrintQuat(const glm::quat &q) {
    std::cout << q.x << ", " << q.y << ", " << q.z << ", " << q.w << std::endl;
}

}
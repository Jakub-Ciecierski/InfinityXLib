#include "math/print_math.h"

#include <iostream>

namespace ifx {

void PrintVec3(const glm::vec3 &vec){
    std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}

void PrintMat3(const glm::mat3 &mat){
    std::cout << mat[0].x << ", " << mat[1].x << ", " << mat[2].x << std::endl;
    std::cout << mat[0].y << ", " << mat[1].y << ", " << mat[2].y << std::endl;
    std::cout << mat[0].z << ", " << mat[1].z << ", " << mat[2].z << std::endl;
}

}
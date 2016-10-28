#include <math/math_ifx.h>

namespace ifx{

LineSphereIntersection Intersection(const LineIntersection& line,
                                    const SphereIntersection& sphere){
    LineSphereIntersection intersection;
    float a = ifx::dot(line.direction, line.origin - sphere.center);
    float a_sqr = a*a;
    glm::vec3 co = line.origin - sphere.center;
    float b = ifx::dot(co, co);

    float under_sqrt = a_sqr - b + (sphere.radius * sphere.radius);
    if(under_sqrt < 0)
        return intersection;

    under_sqrt = sqrt(under_sqrt);
    intersection.d1 = -a + under_sqrt;
    intersection.d2 = -a - under_sqrt;

    return intersection;
}

float Magnitude(const glm::vec3& v1){
    float x_d = v1.x * v1.x;
    float y_d = v1.y * v1.y;
    float z_d = v1.z * v1.z;

    return sqrt(x_d + y_d + z_d);
}

float EuclideanDistance(const glm::vec3& v1, const glm::vec3& v2){
    float x_d = v1.x - v2.x;
    x_d = x_d * x_d;
    float y_d = v1.y - v2.y;
    y_d = y_d * y_d;
    float z_d = v1.z - v2.z;
    z_d = z_d * z_d;

    return sqrt(x_d + y_d + z_d);
}

float dot(const glm::vec3& v1, const glm::vec3& v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

std::vector<std::string> SplitString(std::string s,
                                     std::string delimiter) {
    std::vector<std::string> tokens;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}


}
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 binormal;

out vec3 Normal;
out vec3 Tangent;
out vec3 Binormal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

#define CONTROL_POINTS_COUNT 64
uniform vec3 ControlPoints[CONTROL_POINTS_COUNT];

float bernstein3(float x, float i);
float factorial(float x);
float binomial(float n, float k);
vec4 computeBezierBasis(float u);

vec3 transform_bezier_cube(vec3 position);

void main()
{
    vec3 transform_position = transform_bezier_cube(position);
    //transform_position = position;

    vec4 pos4 = vec4(transform_position, 1.0f);
    mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    gl_Position = MVP * pos4;

    // Fragment position is used to
    // calculate the Ray between Fragment and Light position for each fragment
    FragPos = vec3(ModelMatrix * pos4);

    // Multiply by the "Normal Matrix"
    // TODO This should be calculatd on CPU and send as uniform mat4
    Normal = mat3(transpose(inverse(ModelMatrix))) * normal;
    Tangent = mat3(transpose(inverse(ModelMatrix))) * tangent;
    Binormal = mat3(transpose(inverse(ModelMatrix))) * binormal;

    TexCoords = texCoords;
}

vec3 transform_bezier_cube(vec3 position_){
    vec3 output = vec3(0,0,0);
    position_ = (position_ + 1.0) / 2.0;
/*
    vec4 bezier_x = computeBezierBasis(position_.x);
    vec4 bezier_y = computeBezierBasis(position_.y);
    vec4 bezier_z = computeBezierBasis(position_.z);
*/
    int id = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                float bi = bernstein3(position_.x, i);
                float bj = bernstein3(position_.y, j);
                float bk = bernstein3(position_.y, k);
                //id = 16 * i + 4 * j + k;
                output += ControlPoints[id] * bi * bj * bk;

                float x = ControlPoints[id].x * bi;
                float y = ControlPoints[id].y * bj;
                float z = ControlPoints[id].z * bk;

                //output += vec3(x,y,z);
                id++;
            }
        }
    }
    //output = (output - 1.0) * 2.0;
    return output;
}

float bernstein3(float x, float i){
    float n = 3;
    return binomial(n,i)*pow(x,i)*pow((1-x), n-i);
}

float binomial(float n, float k){
    return factorial(n) / (factorial(k) * factorial(n-k));
}

float factorial(float x){
    float Temp = x;
    float Result;
    for(Result = 1; Temp > 1; --Temp)
        Result *= Temp;
    return Result;
}

vec4 computeBezierBasis(float u){
    // TODO unwind the calculations
    vec4 bezierBasis = vec4(pow(1-u, 3),
                            3*u* pow(1-u, 2),
                            3*pow(u, 2)*(1-u),
                            pow(u, 3));

    return bezierBasis;
}

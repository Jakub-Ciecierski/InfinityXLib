#include <graphics/lighting/types/light_point.h>
#include <graphics/lighting/builders/pointlight_shader_builder.h>

#include <GL/glew.h>

namespace ifx {

LightPoint::LightPoint(const LightParams& light_params) :
        LightSource(light_params, LightType::POINT) {}

LightPoint::~LightPoint() {}

void LightPoint::bind(const Program &program, int id) {
    ifx::PointlightShaderBuilder builder(id);
    builder.build();

    // Light Position
    GLint lightPosLoc = glGetUniformLocation(program.getID(),
                                             builder.POSITION.c_str());

    GLint lightAmbientLoc = glGetUniformLocation(program.getID(),
                                                 builder.AMBIENT.c_str());
    GLint lightDiffuseLoc = glGetUniformLocation(program.getID(),
                                                 builder.DIFFUSE.c_str());
    GLint lightSpecularLoc = glGetUniformLocation(program.getID(),
                                                  builder.SPECULAR.c_str());

    GLint attenConstLoc = glGetUniformLocation(program.getID(),
                                               builder.ATTEN_CONSTANT.c_str());
    GLint attenLineLoc = glGetUniformLocation(program.getID(),
                                              builder.ATTEN_LINEAR.c_str());
    GLint attenQuadLoc = glGetUniformLocation(program.getID(),
                                              builder.ATTEN_QUAD.c_str());
    auto position = getPosition();
    glUniform3f(lightPosLoc, position.x, position.y, position.z);

    glUniform3f(lightAmbientLoc,
                light_params_.ambient.x,
                light_params_.ambient.y,
                light_params_.ambient.z);
    glUniform3f(lightDiffuseLoc,
                light_params_.diffuse.x,
                light_params_.diffuse.y,
                light_params_.diffuse.z);
    glUniform3f(lightSpecularLoc,
                light_params_.specular.x,
                light_params_.specular.y,
                light_params_.specular.z);

    glUniform1f(attenConstLoc, light_params_.constant);
    glUniform1f(attenLineLoc, light_params_.linear);
    glUniform1f(attenQuadLoc, light_params_.quadratic);
}
}
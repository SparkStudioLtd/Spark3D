#include "Core/Graphics/Graphics.h"

void GPUShader::bind() {
    glUseProgram(std::any_cast<int>(this->unbaseVars["programID"]));
}

void GPUShader::shaderInputDataMat4(std::string name, glm::mat4 val)
{
    glUniformMatrix4fv(glGetUniformLocation(std::any_cast<int>(this->unbaseVars["programID"]), name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void GPUShader::shaderInputDataFloat(std::string name, float val)
{
    glUniform1f(glGetUniformLocation(std::any_cast<int>(this->unbaseVars["programID"]), name.c_str()), val);
}

void GPUShader::shaderInputDataInt(std::string name, int val)
{
    glUniform1i(glGetUniformLocation(std::any_cast<int>(this->unbaseVars["programID"]), name.c_str()), val);
}

void GPUShader::shaderInputDataVec3(std::string name, glm::vec3 val)
{
    glUniform3f(glGetUniformLocation(std::any_cast<int>(this->unbaseVars["programID"]), name.c_str()), val.x, val.y, val.z);
}

void GPUShader::unbind() {
    glUseProgram(0);
}
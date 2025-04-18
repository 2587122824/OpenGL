#include "Shader.h"
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

Shader::Shader(const std::string& filepath)
{
    //顶点着色器源码
    std::string vertexShaderCode = std::get<0>(parseShader(filepath));
    //片段着色器源码
    std::string fragmentShaderCode = std::get<1>(parseShader(filepath));
    id = CreateShader(vertexShaderCode, fragmentShaderCode);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void Shader::use()
{
    glUseProgram(id);
}
void Shader::setUniform1i(const char* varible, GLuint value)
{
    GLint location = glGetUniformLocation(id, varible);//获取uniform变量位置
    glUniform1i(location, value); // 设置uniform变量的值需要先使用program，因为它是在当前激活的着色器程序中设置unform的
}

void Shader::setUniformMatrix4fv(const char* varible, glm::mat4 value)
{
    GLint location = glGetUniformLocation(id, varible);//获取uniform变量位置
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));//设置uniform变量的值需要先使用program，因为它是在当前激活的着色器程序中设置unform的
}
void Shader::setUniform4f(const char* varible, glm::vec4 value)
{
    GLint location = glGetUniformLocation(id, varible);//获取uniform变量位置
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

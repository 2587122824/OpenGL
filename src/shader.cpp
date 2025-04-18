#include "Shader.h"
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

Shader::Shader(const std::string& filepath)
{
    //������ɫ��Դ��
    std::string vertexShaderCode = std::get<0>(parseShader(filepath));
    //Ƭ����ɫ��Դ��
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
    GLint location = glGetUniformLocation(id, varible);//��ȡuniform����λ��
    glUniform1i(location, value); // ����uniform������ֵ��Ҫ��ʹ��program����Ϊ�����ڵ�ǰ�������ɫ������������unform��
}

void Shader::setUniformMatrix4fv(const char* varible, glm::mat4 value)
{
    GLint location = glGetUniformLocation(id, varible);//��ȡuniform����λ��
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));//����uniform������ֵ��Ҫ��ʹ��program����Ϊ�����ڵ�ǰ�������ɫ������������unform��
}
void Shader::setUniform4f(const char* varible, glm::vec4 value)
{
    GLint location = glGetUniformLocation(id, varible);//��ȡuniform����λ��
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <string>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();
	void use();
    void setUniform1i(const char* varible, GLuint value);
	void setUniformMatrix4fv(const char* varible, glm::mat4 value);
    void setUniform4f(const char* varible, glm::vec4 value);
	GLuint id;
private:
    std::tuple<std::string, std::string> parseShader(const std::string& filepath) {
        enum class ShaderType
        {
            NONE = 01, VERTEX = 0, FRAGMENT = 1
        };
        std::fstream stream(filepath);
        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    //��������Ϊ������ɫ��
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos) {
                    //��������ΪƬ����ɫ��
                    type = ShaderType::FRAGMENT;
                }
            }
            //���˱�ʶ��������ɫ����Դ����
            else {
                ss[int(type)] << line << "\n";
            }
        }
        std::string vertexShaderCode = ss[0].str();
        std::string fragmentShaderCode = ss[1].str();
        std::tuple<std::string, std::string> tuple(vertexShaderCode, fragmentShaderCode);
        return tuple;
    }
    GLuint CompileShader(unsigned int type, const std::string& ShaderCode) {
        GLuint id = glCreateShader(type);
        const char* sourceCode = ShaderCode.c_str();
        glShaderSource(id, 1, &sourceCode, NULL);
        glCompileShader(id);
        //��鶥����ɫ���Ƿ����ɹ�
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        return id;
    }
    GLuint CreateShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) {
        GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
        GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
        //��������ɫ������Ϊһ����ɫ���������
        id = glCreateProgram();
        glAttachShader(id, vertexShader);//��֮ǰ����Ķ�����ɫ�����ӵ����������
        glAttachShader(id, fragmentShader); //��֮ǰ�����Ƭ����ɫ�����ӵ����������
        glLinkProgram(id);
        //��������Ƿ�ɹ�
        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
        }
        else {
            //������Ϳ���ɾ����ɫ������
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }
        return id;
    }
};

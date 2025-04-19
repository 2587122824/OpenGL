#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4
//����
struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;
    VertexArray VAO;

    // ���캯��
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        // ��ʼ��VBO,VAO,��������ָ��
        setupMesh();
    }

    // ��Ⱦ����
    void Draw(Shader& shader)
    {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            string number;
            string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to string
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to string
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to string

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.id, (name + number).c_str()), i);
            // and finally bind the texture 
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        // ����
        VAO.bind();
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        VAO.unbind();

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

private:
    VertexBuffer VBO;
    IndexBuffer IBO;

    // ��ʼ��VBO,VAO,��������ָ��
    void setupMesh()
    {
        //vertexBufferObject ���㻺�����
        VBO = VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));//���ýṹ���ڴ������ԣ������һ������ĳ�ʼλ�ú�ȫ��������ڴ泤��

        //indexBufferObject �����������
        IBO = IndexBuffer(&indices[0], indices.size() * sizeof(Vertex));

        //VBO����
        VertexBufferLayout VBL;
        //���붥�����ԵĴ�С
        VBL.addAttribute(3);//����λ��
        VBL.addAttribute(3);//���㷨��
        VBL.addAttribute(2);//��������
        VBL.addAttribute(3);//��������
        VBL.addAttribute(3);//���㸱����
        VBL.addAttribute(4);//�������id
        VBL.addAttribute(4);//Ȩ��
        //����������ָ�����VAO
        VAO.addBuffer(VBO, VBL);
    }
};
#endif
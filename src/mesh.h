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
//顶点
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

    // 构造函数
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        // 初始化VBO,VAO,顶点属性指针
        setupMesh();
    }

    // 渲染函数
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

        // 绘制
        VAO.bind();
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        VAO.unbind();

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

private:
    VertexBuffer VBO;
    IndexBuffer IBO;

    // 初始化VBO,VAO,顶点属性指针
    void setupMesh()
    {
        //vertexBufferObject 顶点缓存对象
        VBO = VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));//利用结构体内存连续性，传入第一个顶点的初始位置和全部顶点的内存长度

        //indexBufferObject 索引缓存对象
        IBO = IndexBuffer(&indices[0], indices.size() * sizeof(Vertex));

        //VBO布局
        VertexBufferLayout VBL;
        //传入顶点属性的大小
        VBL.addAttribute(3);//顶点位置
        VBL.addAttribute(3);//顶点法线
        VBL.addAttribute(2);//纹理坐标
        VBL.addAttribute(3);//顶点切线
        VBL.addAttribute(3);//顶点副切线
        VBL.addAttribute(4);//顶点骨骼id
        VBL.addAttribute(4);//权重
        //将顶点属性指针放入VAO
        VAO.addBuffer(VBO, VBL);
    }
};
#endif
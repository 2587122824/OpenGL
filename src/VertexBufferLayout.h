#pragma once
#include <GL/glew.h>
#include <vector>
class VertexBufferLayout
{
public:
	int vertexAttribuCount = -1;//记录第几个属性
	int position = -1;
	int dimension = 0;//维度
	GLfloat type = GL_FLOAT;
	int stride = 0;//步长
	int offset = 0;//偏移量
	std::vector<VertexBufferLayout> vector;
	VertexBufferLayout();
	~VertexBufferLayout();
	int getStride();
	void addAttribute(int dimension);
};

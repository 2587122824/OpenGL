#pragma once
#include <GL/glew.h>
#include <vector>
class VertexBufferLayout
{
public:
	int vertexAttribuCount = -1;//��¼�ڼ�������
	int position = -1;
	int dimension = 0;//ά��
	GLfloat type = GL_FLOAT;
	int stride = 0;//����
	int offset = 0;//ƫ����
	std::vector<VertexBufferLayout> vector;
	VertexBufferLayout();
	~VertexBufferLayout();
	int getStride();
	void addAttribute(int dimension);
};

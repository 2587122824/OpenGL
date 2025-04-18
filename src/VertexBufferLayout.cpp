#include "VertexBufferLayout.h"
#include <GL/glew.h>
#include <iostream>
VertexBufferLayout::VertexBufferLayout()
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}
int VertexBufferLayout::getStride() {
	return stride * sizeof(type);
}
//�������ʱ���¼�������ŵ�vector������
void VertexBufferLayout::addAttribute(int dimension) {
	this->dimension = dimension;
	position++;//λ��+1
	//���㲽��
	stride += dimension;
	//����ƫ����
	offset = stride - dimension;
	vector.push_back(*this);
}

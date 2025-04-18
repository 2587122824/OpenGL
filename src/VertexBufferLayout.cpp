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
//添加属性时候记录下来并放到vector容器中
void VertexBufferLayout::addAttribute(int dimension) {
	this->dimension = dimension;
	position++;//位置+1
	//计算步长
	stride += dimension;
	//计算偏移量
	offset = stride - dimension;
	vector.push_back(*this);
}

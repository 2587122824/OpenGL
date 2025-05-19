#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include <iostream>
#include <GL/glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}
void VertexArray::addBuffer(VertexBuffer &VBO, VertexBufferLayout &VBL) {//必须引用传参！！！！
	this->bind();
	VBO.bind();
	for (int i = 0; i < VBL.vector.size(); i++) {
		/*std::cout << VBL.vector[i].position << std::endl;
		std::cout << VBL.vector[i].dimension << std::endl;
		std::cout << VBL.vector[i].stride << std::endl;
		std::cout << VBL.vector[i].offset << std::endl;*/

	//	//VBO布局 储存在VAO中
	//	//第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。
	//	//第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
	//	//第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec * 都是由浮点数值组成的)。
	//	//下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是 - 1）到1之间。我们把它设置为GL_FALSE。
	//	//第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。
	//	//最后一个参数的类型是GLvoid * ，需要进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。
		glVertexAttribPointer(VBL.vector[i].position, VBL.vector[i].dimension, VBL.vector[i].type, GL_FALSE, VBL.vector[VBL.vector.size()-1].getStride(), (GLvoid*)(VBL.vector[i].offset * sizeof(VBL.vector[i].type)));
		glEnableVertexAttribArray(VBL.vector[i].position);
	}
}
void VertexArray::bind()
{
	glBindVertexArray(id);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

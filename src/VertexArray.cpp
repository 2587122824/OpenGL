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
void VertexArray::addBuffer(VertexBuffer &VBO, VertexBufferLayout &VBL) {//�������ô��Σ�������
	this->bind();
	VBO.bind();
	for (int i = 0; i < VBL.vector.size(); i++) {
		/*std::cout << VBL.vector[i].position << std::endl;
		std::cout << VBL.vector[i].dimension << std::endl;
		std::cout << VBL.vector[i].stride << std::endl;
		std::cout << VBL.vector[i].offset << std::endl;*/

	//	//VBO���� ������VAO��
	//	//��һ������ָ������Ҫ���õĶ������ԡ����ǵ������ڶ�����ɫ����ʹ��layout(location = 0)������position�������Ե�λ��ֵ(Location)�������԰Ѷ������Ե�λ��ֵ����Ϊ0��
	//	//�ڶ�������ָ���������ԵĴ�С������������һ��vec3������3��ֵ��ɣ����Դ�С��3��
	//	//����������ָ�����ݵ����ͣ�������GL_FLOAT(GLSL��vec * �����ɸ�����ֵ��ɵ�)��
	//	//�¸��������������Ƿ�ϣ�����ݱ���׼��(Normalize)�������������ΪGL_TRUE���������ݶ��ᱻӳ�䵽0�������з�����signed������ - 1����1֮�䡣���ǰ�������ΪGL_FALSE��
	//	//�����������������(Stride)�������������������Ķ���������֮��ļ����Ҫע�������������֪����������ǽ������еģ���������������֮��û�п�϶������Ҳ��������Ϊ0����OpenGL�������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã���
	//	//���һ��������������GLvoid * ����Ҫ���������ֵ�ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)��
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

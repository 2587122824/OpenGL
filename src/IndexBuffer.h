#pragma once
#include <GL/glew.h>
class IndexBuffer {

private:
	GLuint id;
public:
	IndexBuffer();
	IndexBuffer(const void* verteices, unsigned int size);
	~IndexBuffer();

	void bind();
	void unbind();

};
#pragma once
#include <GL/glew.h>
class VertexBuffer {

private:
	GLuint id;
public:
	VertexBuffer(const void* verteices, unsigned int size);
	~VertexBuffer();

	void bind();
	void unbind();

};
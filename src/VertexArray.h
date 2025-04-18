#pragma once
#include <GL/glew.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class VertexArray {
private: 
	GLuint id;
public: 
	VertexArray();
	~VertexArray();
	void bind();
	void unbind();
	void addBuffer(VertexBuffer& VBO, VertexBufferLayout& VBL);
};
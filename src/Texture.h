#pragma once
#include <GL/glew.h>
#include <string>
class Texture {
private:
	GLuint id;
	int width, height, nrChannels;
public:
	Texture(const std::string filepath, int slot = 0);
	~Texture();
	void bind();
	void unbind();
	unsigned char* image_load(const std::string filepath);
};
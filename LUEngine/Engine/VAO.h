#pragma once

#include "src/glad/include/glad/glad.h"

class VAO
{
public:
	unsigned int ID{};
	VAO();
	~VAO();
	void Bind();
	void Unbind();
	void LinkAttrib(int layout, GLuint components, GLsizei stride, void* offset);
};


#pragma once

#include "src/glad/include/glad/glad.h"

class VBO
{
public:
	unsigned int ID{};
	VBO();
	~VBO();
	void Bind();
	void Unbind();
	void Setup(const GLfloat* vertices, GLsizeiptr size);
};


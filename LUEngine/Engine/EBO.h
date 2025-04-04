#pragma once

#include "src/glad/include/glad/glad.h"

class EBO
{
public:
	unsigned int ID{};
	EBO();
	~EBO();
	void Bind();
	void Unbind();
	void Setup(const unsigned int* indices, GLsizeiptr size);
};


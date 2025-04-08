#pragma once

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

class Obj
{
public:
	Obj(float vertices, int indices);
	~Obj();
private:
	VBO vbo{};
	VAO vao{};
};


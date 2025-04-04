#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::LinkAttrib(int layout, GLuint components, GLsizei stride, void* offset)
{
	glVertexAttribPointer(layout, components, GL_FLOAT, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
}

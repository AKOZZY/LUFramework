#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    unsigned int ID;

    void Activate();

private:
    void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif
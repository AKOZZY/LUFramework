#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "src/glm/glm.hpp"
#include "src/glm/gtc/matrix_transform.hpp"
#include "src/glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);

    void Activate();

    void SetUniformMatrix4(const char* name, glm::mat4 matrix);

private:
    void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif
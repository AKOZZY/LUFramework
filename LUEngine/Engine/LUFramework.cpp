#include "LUFramework.h"

LUFramework::LUFramework()
{
    glfwInit();
}

void LUFramework::InitWindow(const char* windowText, int screenWidth, int screenHeight)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, windowText, NULL, NULL);
    glfwMakeContextCurrent(window);
}

GLFWwindow* LUFramework::GetWindow()
{
    return window;
}

void LUFramework::ClearBackground(Colour colour)
{
    glClearColor(colour.r, colour.g, colour.b, colour.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void LUFramework::DrawSquare(VAO vao, VBO vbo, Vector2 positon)
{
    vao.Bind();
    vbo.Bind();
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    vao.Unbind();
    vbo.Unbind();
}

bool LUFramework::GetKeyDown(int input)
{
    if (glfwGetKey(window, input) == GLFW_PRESS) return true;
}

Texture LUFramework::LoadTexture(const char* filePath)
{
    // Create Texture
    Texture texture{};
    // Texture stuff
    glGenTextures(1, &texture.ID);
    glBindTexture(GL_TEXTURE_2D, texture.ID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath, &texture.width, &texture.height, &texture.channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}



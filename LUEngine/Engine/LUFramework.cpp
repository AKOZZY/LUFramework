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

void LUFramework::DrawSquare()
{

}

bool LUFramework::GetKeyDown(int input)
{
    if (glfwGetKey(window, input) == GLFW_PRESS) return true;
}



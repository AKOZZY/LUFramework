#include "src/glad/include/glad/glad.h"
#include "src/GLFW/include/glfw3.h"
#include "src/glm/glm.hpp"
#include "src/glm/gtc/matrix_transform.hpp"
#include "src/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <cmath>

#include "LUFramework.h"
#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // Init LU and GLFW
    // test
    LUFramework lu{};

    // Init Window and check if window has failed to init
    lu.InitWindow("LU Engine", SCR_WIDTH, SCR_HEIGHT);
    if (lu.GetWindow() == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(lu.GetWindow(), framebuffer_size_callback);
    
    // Init Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // >> START << //
    Shader shader{"defaultVertShader.vert", "defaultFragShader.frag"};

    float vertices[] = 
    {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int indices[] =
    {
         0, 1, 3,
         1, 2, 3
    };

    // Generate VBO, VAO objects
    VBO vbo{};
    VAO vao{};
    EBO ebo{};

    // Bind the objects and setup objects
    vao.Bind();

    vbo.Bind();
    vbo.Setup(vertices, sizeof(vertices));

    ebo.Bind();
    ebo.Setup(indices, sizeof(indices));

    // Link vertex attributes
    vao.LinkAttrib(0, 3, 3 * sizeof(float), (void*)0); // Position

    // Init object matrix
    Vector2 positon{};
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(0.1, 0.1, 0.1));

    // Unbind
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    while (!glfwWindowShouldClose(lu.GetWindow()))
    {
        // >> UPDATE << //
        if (lu.GetKeyDown(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(lu.GetWindow(), true);

        //trans = glm::translate(trans, glm::vec3(positon.x, positon.y, 0));

        if (lu.GetKeyDown(GLFW_KEY_W)) trans = glm::translate(trans, glm::vec3(0, positon.y + 0.1, 0));
        if (lu.GetKeyDown(GLFW_KEY_S)) trans = glm::translate(trans, glm::vec3(0, positon.y - 0.1, 0));
        if (lu.GetKeyDown(GLFW_KEY_A)) trans = glm::translate(trans, glm::vec3(positon.x - 0.1, 0, 0));
        if (lu.GetKeyDown(GLFW_KEY_D)) trans = glm::translate(trans, glm::vec3(positon.x + 0.1, 0, 0));

        // >> RENDER << //
        lu.ClearBackground(Colour{COLOUR_OPENGL_DEFAULT});

        shader.Activate();

        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.Unbind();

        glfwSwapBuffers(lu.GetWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
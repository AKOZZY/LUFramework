// GLAD AND GLFW
#include "src/glad/include/glad/glad.h"
#include "src/GLFW/include/glfw3.h"
// GLM
#include "src/glm/glm.hpp"
#include "src/glm/gtc/matrix_transform.hpp"
#include "src/glm/gtc/type_ptr.hpp"
// Stb Image
#include "stb_image.h"
// STL
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
        // Positions         // TexCoord
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
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
    vao.LinkAttrib(0, 3, 5 * sizeof(float), (void*)0); // Position
    vao.LinkAttrib(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Texture

    // Init object matrix
    Vector2 positon{};
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(0.1, 0.1, 0.1));

    // Unbind
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture stuff
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("src/Textures/epicface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // OpenGL rendering settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(lu.GetWindow()))
    {
        // >> UPDATE << //
        if (lu.GetKeyDown(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(lu.GetWindow(), true);

        if (lu.GetKeyDown(GLFW_KEY_W)) trans = glm::translate(trans, glm::vec3(0, positon.y + 0.1, 0));
        if (lu.GetKeyDown(GLFW_KEY_S)) trans = glm::translate(trans, glm::vec3(0, positon.y - 0.1, 0));
        if (lu.GetKeyDown(GLFW_KEY_A)) trans = glm::translate(trans, glm::vec3(positon.x - 0.1, 0, 0));
        if (lu.GetKeyDown(GLFW_KEY_D)) trans = glm::translate(trans, glm::vec3(positon.x + 0.1, 0, 0));

        // >> RENDER << //
        lu.ClearBackground(Colour{COLOUR_OPENGL_DEFAULT});

        shader.Activate();
        
        
        shader.SetUniformMatrix4("transform", trans);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        vao.Unbind();

        glfwSwapBuffers(lu.GetWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
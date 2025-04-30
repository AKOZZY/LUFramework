#include "GameObject.h"

GameObject::GameObject()
{
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
}

GameObject::~GameObject()
{

}

void GameObject::Render()
{
    shader.Activate();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GameObject::Update()
{
    // Matrix Multiplication
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.1, 0.1, 0.1));
    transform = glm::translate(transform, glm::vec3(position.x, position.y, 0));
    // Send Matrix To Shader
    shader.SetUniformMatrix4("transform", transform);
}

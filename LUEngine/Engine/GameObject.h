#pragma once

// GLAD AND GLFW
#include "src/glad/include/glad/glad.h"
#include "src/GLFW/include/glfw3.h"

// GLM
#include "src/glm/glm.hpp"
#include "src/glm/gtc/matrix_transform.hpp"
#include "src/glm/gtc/type_ptr.hpp"

// Stb Image
#include "stb_image.h"

#include "LUFramework.h"
#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Render();
	void Update();

	Vector2 position{};
	Vector2 scale{};

	Texture texture{};
private:
	VBO vbo{};
	VAO vao{};
	EBO ebo{};

	Shader shader{"defaultVertShader.vert", "defaultFragShader.frag"};

	//glm::mat4 translate{1.0f};
	//glm::mat4 scale{1.0f};
};


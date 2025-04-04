#pragma once

#include <iostream>

#include "src/glad/include/glad/glad.h"
#include "src/GLFW/include/glfw3.h"

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

// Colors
#define COLOUR_OPENGL_DEFAULT 0.184, 0.310, 0.310, 1.0
#define COLOUR_RED 1.0, 0.0, 0.0, 1.0
#define COLOUR_PINK 0.780, 0.082, 0.522, 1.0
#define COLOUR_GREY 0.412, 0.412, 0.412, 1.0

// Structs
struct Vector2
{
	float x{};
	float y{};
};

struct Colour
{
	float r{}; // Red
	float g{}; // Green
	float b{}; // Blue
	float a{}; // Alpha
};

class LUFramework
{
public:
	LUFramework();
	
	// Window Functions
	void InitWindow(const char* windowText, int screenWidth, int screenHeight);
	GLFWwindow* GetWindow();

	// Render
	void ClearBackground(Colour colour);
	void DrawSquare();

	// Inputs
	bool GetKeyDown(int input);

private:
	const unsigned int SCR_WIDTH{ 800 };
	const unsigned int SCR_HEIGHT{ 600 };
	GLFWwindow* window{};
};

// Template Functions
template <typename T> void DebugLog(T input)
{
	std::cout << input << "\n";
}



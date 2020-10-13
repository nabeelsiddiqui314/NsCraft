#pragma once
#include <array>
#include <GL/glew.h>

struct Quad {
	std::array<GLfloat, 12> vertices;
	GLfloat lightingMultiplier;
};
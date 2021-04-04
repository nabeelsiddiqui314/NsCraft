#pragma once
#include <array>
#include <GL/glew.h>

struct BlockFace {
	std::array<GLfloat, 12> vertices;
	GLfloat faceLight;
};

namespace BlockFaces {
	constexpr BlockFace Front = {{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1 }, 0.8f };

	constexpr BlockFace Back = {{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0 }, 0.8f };

	constexpr BlockFace Left = {{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0 }, 0.6f };

	constexpr BlockFace Right = {{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1 }, 0.6f };

	constexpr BlockFace Top = {{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0 }, 1.0f };

	constexpr BlockFace Bottom = {{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1 }, 0.4f };

	constexpr BlockFace CrossA = { {
		0, 0, 1,
		1, 0, 0,
		1, 1, 0,
		0, 1, 1 }, 0.8f };

	constexpr BlockFace CrossB = { {
		1, 0, 1,
		0, 0, 0,
		0, 1, 0,
		1, 1, 1 }, 0.8f };

	constexpr std::array<GLuint, 6> indicesOrder = { 0, 1, 2, 0, 2, 3 };
}
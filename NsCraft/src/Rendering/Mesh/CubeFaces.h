#pragma once
#include "Quad.h"

// indices -> 0, 1, 2, 0, 2, 3

namespace CubeFaces {
	const Quad Front = {
		0, 0, 0,
		1, 0, 0,
		1, 1, 0,
		0, 1, 0 };

	const Quad Back = { 
		1, 0, -1,
		0, 0, -1,
		0, 1, -1,
		1, 1, -1 };

	const Quad Left = { 
		0, 0, -1,
		0, 0,  0,
		0, 1,  0,
		0, 1, -1 };

	const Quad Right = { 
		1, 0,  0,
		1, 0, -1,
		1, 1, -1,
		1, 1,  0 };

	const Quad Top = { 
		0, 1,  0,
		1, 1,  0,
		1, 1, -1,
		0, 1, -1 };

	const Quad Bottom = { 
		0, 0, -1,
		1, 0, -1,
		1, 0,  0,
		0, 0,  0 };
}
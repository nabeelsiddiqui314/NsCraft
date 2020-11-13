#pragma once
#include "Quad.h"

// indices -> 0, 1, 2, 0, 2, 3

namespace CubeFaces {
	const Quad Front = {{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1 }, 0.8f };

	const Quad Back = {{ 
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0 }, 0.8f };

	const Quad Left = {{ 
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0 }, 0.6f };

	const Quad Right = {{ 
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1 }, 0.6f };

	const Quad Top = {{ 
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0 }, 1.0f };

	const Quad Bottom = {{ 
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1 }, 0.4f };
}
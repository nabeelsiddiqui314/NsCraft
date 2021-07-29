#pragma once
#include "Vector3.h"
#include <array>

namespace Directions {
	const Vector3 Up    (  0,  1,  0 );
	const Vector3 Down  (  0, -1,  0 );
	const Vector3 Right (  1,  0,  0 );
	const Vector3 Left  ( -1,  0,  0 );
	const Vector3 Front (  0,  0,  1 );
	const Vector3 Back  (  0,  0, -1 );

	const std::array<Vector3, 6> List = { Up, Down, Right, Left, Front, Back };
}
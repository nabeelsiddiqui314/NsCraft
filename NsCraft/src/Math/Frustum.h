#pragma once
#include <array>
#include "Plane.h"

struct AABB;
class Camera;

class Frustum {
private:
	enum {
		NEARP = 0,
		FARP,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};
public:
	Frustum(const Camera& camera);
	~Frustum() = default;
public:
	bool isAABBinFrustum(const AABB& aabb) const;
private:
	std::array<Plane, 6> m_planes;
};
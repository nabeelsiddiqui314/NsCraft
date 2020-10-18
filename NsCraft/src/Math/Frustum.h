#pragma once
#include <array>
#include <glm/glm.hpp>
#include "Plane.h"

struct AABB;

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
	Frustum() = default;
	~Frustum() = default;
public:
	void update(const glm::mat4& view, const glm::mat4& projection);

	bool isAABBinFrustum(const AABB& aabb) const;
private:
	std::array<Plane, 6> m_planes;
};
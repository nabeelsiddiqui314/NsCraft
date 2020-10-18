#pragma once
#include <glm/glm.hpp>

struct Plane {
public:
	glm::vec3 normal;
	float d;
public:
	float distance(const glm::vec3& p) const;
};
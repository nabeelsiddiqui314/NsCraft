#pragma once
#include <glm/glm.hpp>

struct AABB {
public:
	glm::vec3 position;
	glm::vec3 size;
public:
	glm::vec3 getVN(const glm::vec3& normal) const;
	glm::vec3 getVP(const glm::vec3& normal) const;
};
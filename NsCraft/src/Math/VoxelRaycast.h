#pragma once
#include <glm/vec3.hpp>
#include "Vector3.h"

class VoxelRaycast {
public:
	VoxelRaycast(const glm::vec3& origin, const glm::vec3& direction);
	~VoxelRaycast() = default;
public:
	Vector3 increment();
private:
	float sign(float value);
	float intBound(float s, float ds);
private:
	glm::vec3 m_currentPos;
	glm::vec3 m_step;
	glm::vec3 m_tMax;
	glm::vec3 m_tDelta;
};
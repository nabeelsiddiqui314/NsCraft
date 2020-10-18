#include "AABB.h"

glm::vec3 AABB::getVN(const glm::vec3& normal) const {
	glm::vec3 res = position;

	if (normal.x < 0) {
		res.x += size.x;
	}

	if (normal.y < 0) {
		res.y += size.y;
	}

	if (normal.z < 0) {
		res.z += size.z;
	}

	return res;
}

glm::vec3 AABB::getVP(const glm::vec3& normal) const {
	glm::vec3 res = position;

	if (normal.x > 0) {
		res.x += size.x;
	}

	if (normal.y > 0) {
		res.y += size.y;
	}

	if (normal.z > 0) {
		res.z += size.z;
	}

	return res;
}

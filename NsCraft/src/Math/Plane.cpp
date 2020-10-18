#include "Plane.h"

float Plane::distance(const glm::vec3& p) const {
	return d + glm::dot(p, normal);
}

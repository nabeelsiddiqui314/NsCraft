#include "Frustum.h"
#include "AABB.h"
#include "Plane.h"
#include "../Rendering/Camera/Camera.h"
#include <glm/glm.hpp>

Frustum::Frustum(const Camera& camera) {
	glm::mat4 mat = camera.getProjection() * camera.getView();

	m_planes[LEFT].normal.x = mat[0][3] + mat[0][0];
	m_planes[LEFT].normal.y = mat[1][3] + mat[1][0];
	m_planes[LEFT].normal.z = mat[2][3] + mat[2][0];
	m_planes[LEFT].d = mat[3][3] + mat[3][0];

	m_planes[RIGHT].normal.x = mat[0][3] - mat[0][0];
	m_planes[RIGHT].normal.y = mat[1][3] - mat[1][0];
	m_planes[RIGHT].normal.z = mat[2][3] - mat[2][0];
	m_planes[RIGHT].d = mat[3][3] - mat[3][0];

	m_planes[BOTTOM].normal.x = mat[0][3] + mat[0][1];
	m_planes[BOTTOM].normal.y = mat[1][3] + mat[1][1];
	m_planes[BOTTOM].normal.z = mat[2][3] + mat[2][1];
	m_planes[BOTTOM].d = mat[3][3] + mat[3][1];

	m_planes[TOP].normal.x = mat[0][3] - mat[0][1];
	m_planes[TOP].normal.y = mat[1][3] - mat[1][1];
	m_planes[TOP].normal.z = mat[2][3] - mat[2][1];
	m_planes[TOP].d = mat[3][3] - mat[3][1];

	m_planes[NEARP].normal.x = mat[0][3] + mat[0][2];
	m_planes[NEARP].normal.y = mat[1][3] + mat[1][2];
	m_planes[NEARP].normal.z = mat[2][3] + mat[2][2];
	m_planes[NEARP].d = mat[3][3] + mat[3][2];

	m_planes[FARP].normal.x = mat[0][3] - mat[0][2];
	m_planes[FARP].normal.y = mat[1][3] - mat[1][2];
	m_planes[FARP].normal.z = mat[2][3] - mat[2][2];
	m_planes[FARP].d = mat[3][3] - mat[3][2];

	for (auto& plane : m_planes) {
		float length = glm::length(plane.normal);
		plane.normal /= length;
		plane.d /= length;
	}
}

bool Frustum::isAABBinFrustum(const AABB& aabb) const {
	bool result = true;
	for (auto& plane : m_planes) {
		if (plane.distance(aabb.getVP(plane.normal)) < 0) {
			return false;
		}
		else if (plane.distance(aabb.getVN(plane.normal)) < 0) {
			result = true;
		}
	}
	return result;
}
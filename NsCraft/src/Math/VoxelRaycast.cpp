#include "VoxelRaycast.h"
#include "Vector3.h"

VoxelRaycast::VoxelRaycast(const glm::vec3& origin, const glm::vec3& direction) {
	m_currentPos.x = floor(origin.x);
	m_currentPos.y = floor(origin.y);
	m_currentPos.z = floor(origin.z);

	m_step.x = sign(direction.x);
	m_step.y = sign(direction.y);
	m_step.z = sign(direction.z);

	m_tMax.x = intBound(m_currentPos.x, direction.x);
	m_tMax.y = intBound(m_currentPos.y, direction.y);
	m_tMax.z = intBound(m_currentPos.z, direction.z);

	m_tDelta = m_step / glm::vec3(direction.x, direction.y, direction.z);
}

Vector3 VoxelRaycast::increment() {
	if (m_tMax.x < m_tMax.y) {
		if (m_tMax.x < m_tMax.z) {
			m_currentPos.x += m_step.x;
			m_tMax.x += m_tDelta.x;
		}
		else {
			m_currentPos.z += m_step.z;
			m_tMax.z += m_tDelta.z;
		}
	}
	else {
		if (m_tMax.y < m_tMax.z) {
			m_currentPos.y += m_step.y;
			m_tMax.y += m_tDelta.y;
		}
		else {
			m_currentPos.z += m_step.z;
			m_tMax.z += m_tDelta.z;
		}
	}

	return Vector3(m_currentPos.x, m_currentPos.y, m_currentPos.z);
}

float VoxelRaycast::sign(float value) {
	if (value > 0) {
		return 1.0f;
	}
	else if (value < 0) {
		return -1.0f;
	}

	return 0.0f;
}

float VoxelRaycast::intBound(float s, float ds){
	if (ds > 0) {
		return (ceil(s) - s) / abs(ds);
	}
	else {
		return (s - floor(s)) / abs(ds);
	}
}

#pragma once
#include <glm/glm.hpp>
#include "../../Math/Frustum.h"

class Camera {
public:
	Camera(float aspectRatio, float fov);
	~Camera() = default;
public:
	glm::mat4 getView() const;
	glm::mat4 getProjection() const;

	void setAspectRatio(float aspectRatio);
	void setFOV(float fov);

	void setPosition(const glm::vec3& position);
	void move(const glm::vec3& moveVector);
	void rotate(float yaw, float pitch);

	glm::vec3 getFront() const;
	glm::vec3 getRight() const;

	glm::vec3 getPosition() const;

	const Frustum& getFrustum() const;
private:
	void updateView();
	void updateProjection();
private:
	glm::vec3 m_position;
	glm::vec3 m_worldUp;
	glm::vec3 m_up;
	glm::vec3 m_front;
	glm::vec3 m_right;

	float m_yaw;
	float m_pitch;
	float m_aspectRatio;
	float m_fov;

	glm::mat4 m_view;
	glm::mat4 m_projection;

	Frustum m_frustum;
};
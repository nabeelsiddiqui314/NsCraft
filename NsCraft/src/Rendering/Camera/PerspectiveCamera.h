#pragma once
#include "ICamera.h"
#include "../../Math/Frustum.h"

class PerspectiveCamera : public ICamera {
public:
	PerspectiveCamera(float aspectRatio, float fov);
	~PerspectiveCamera() = default;
public:
	glm::mat4 getView() const override;
	glm::mat4 getProjection() const override;

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
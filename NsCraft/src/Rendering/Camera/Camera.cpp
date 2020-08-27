#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float aspectRatio, float fov)
	: m_position(0.0f, 0.0f, 0.0f),
      m_worldUp(0.0f, 1.0f, 0.0f),
      m_up(0.0f, 1.0f, 0.0f),
	  m_front(0.0f, 0.0f, 1.0f),
      m_right(0.0f, 0.0f, 0.0f),
      m_yaw(-9.0f),
      m_pitch(0.0f),
      m_aspectRatio(aspectRatio),
      m_fov(fov) {}

glm::mat4 Camera::getView() const {
	return glm::lookAt(m_position, m_position + m_front, m_worldUp);
}

glm::mat4 Camera::getProjection() const {
	return glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 1000.0f);
}

void Camera::setAspectRatio(float aspectRatio) {
	m_aspectRatio = aspectRatio;
}

void Camera::setFOV(float fov) {
	m_fov = fov;
}

void Camera::setPosition(const glm::vec3& position) {
	m_position = position;
	updateCameraVectors();
}

void Camera::move(const glm::vec3& moveVector) {
	setPosition(m_position + moveVector);
}

void Camera::rotate(float yaw, float pitch) {
	m_yaw += yaw;
	m_pitch += pitch;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	updateCameraVectors();
}

glm::vec3 Camera::getFront() const {
	return m_front;
}

glm::vec3 Camera::getRight() const {
	return m_right;
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
	front.y = sinf(glm::radians(m_pitch));
	front.z = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
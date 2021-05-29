#pragma once
#include "ICamera.h"
#include <glm/glm.hpp>

struct Projection {
	float left, right, bottom, top;
};

class OrthographicCamera : public ICamera {
public:
	OrthographicCamera(const Projection& projection);
	~OrthographicCamera() = default;
public:
	glm::mat4 getView() const override;
	glm::mat4 getProjection() const override;

	void setProjection(const Projection& projection);

	void setPosition(const glm::vec2& position);
	glm::vec2 getPosition() const;

	void setRotation(float rotation);
	float getRotation() const;
	
	void move(const glm::vec2& deltaPosition);
	void rotate(float deltaRotation);
private:
	void updateView();
private:
	glm::vec2 m_position;
	float m_rotation;

	glm::mat4 m_view;
	glm::mat4 m_projection;
};
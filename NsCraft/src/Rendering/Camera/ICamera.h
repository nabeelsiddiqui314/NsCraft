#pragma once
#include <glm/glm.hpp>

class ICamera {
public:
	ICamera() = default;
	virtual ~ICamera() = default;
public:
	virtual glm::mat4 getView() const = 0;
	virtual glm::mat4 getProjection() const = 0;
};
#include "OrthographpicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(const Projection& projection) 
    : m_position(0.0f), m_rotation(0.0f) {
    setProjection(projection);
    updateView();
}

glm::mat4 OrthographicCamera::getView() const {
    return m_view;
}

glm::mat4 OrthographicCamera::getProjection() const {
    return m_projection;
}

void OrthographicCamera::setProjection(const Projection& projection) {
    m_projection = glm::ortho(projection.left, projection.right, projection.bottom, projection.top, -1.0f, 1.0f);
}

void OrthographicCamera::setPosition(const glm::vec2& position) {
    m_position = position;
    updateView();
}

glm::vec2 OrthographicCamera::getPosition() const {
    return m_position;
}

void OrthographicCamera::setRotation(float rotation) {
    m_rotation = rotation;
    updateView();
}

float OrthographicCamera::getRotation() const {
    return m_rotation;
}

void OrthographicCamera::move(const glm::vec2& deltaPosition) {
    setPosition(m_position + deltaPosition);
}

void OrthographicCamera::rotate(float deltaRotation) {
    setRotation(m_rotation + deltaRotation);
}

void OrthographicCamera::updateView() {
    auto translation = glm::translate(glm::mat4(1.0f), glm::vec3(m_position, 0.0f));
    auto rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

    auto transformation = translation * rotation;

    m_view = glm::inverse(transformation);
}
#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float faceLight;
layout (location = 3) in float skyLight;
layout (location = 4) in float naturalLight;

out vec2 v_texCoords;
out vec3 v_lighting;

uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
	gl_Position = u_projection * u_view * vec4(position, 1.0);
	v_texCoords = texCoords;

	float skyLightIntensity = 1 * faceLight;
	float lighting = max((naturalLight + skyLight * skyLightIntensity) / 2, 0.2);
	v_lighting = vec3(lighting);
}
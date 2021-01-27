#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float textureIndex;
layout (location = 3) in float faceLight;
layout (location = 4) in float skyLight;
layout (location = 5) in float naturalLight;

out vec3 v_textureArrayCoords;
out vec3 v_lighting;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
	gl_Position = u_projection * u_view * u_model * vec4(position, 1.0);
	v_textureArrayCoords = vec3(texCoords, textureIndex);

	float lighting = max((naturalLight + skyLight) / 2, 0.2) * faceLight;
	v_lighting = vec3(lighting);
}
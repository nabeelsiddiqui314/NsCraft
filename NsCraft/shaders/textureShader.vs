#version 430 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_texCoords;

void main() {
	gl_Position = u_projection * u_view * u_model * vec4(vec3(position, 0.0), 1.0);
	v_texCoords = texCoords;
}
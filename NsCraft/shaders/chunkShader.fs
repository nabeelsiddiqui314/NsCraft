#version 460 core

out vec4 color;
in vec2 v_texCoords;
in vec3 v_lighting;

uniform sampler2D u_texture;

void main() {
	color = texture(u_texture, v_texCoords) * vec4(v_lighting, 1.0);
}
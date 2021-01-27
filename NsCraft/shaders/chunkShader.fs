#version 430 core

out vec4 color;
in vec3 v_textureArrayCoords;
in vec3 v_lighting;

uniform sampler2DArray u_blocksTexture;

void main() {
	color = texture(u_blocksTexture, v_textureArrayCoords) * vec4(v_lighting, 1.0);
}
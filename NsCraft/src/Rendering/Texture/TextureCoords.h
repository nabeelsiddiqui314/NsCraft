#pragma once

struct TextureCoords {
	float bottomLeftU, bottomLeftV, topRightU, topRightV;
public:
	TextureCoords() = default;
	TextureCoords(float _bottomLeftU, float _bottomLeftV, float _topRightU, float _topRightV);
};
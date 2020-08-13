#pragma once

struct FloatRect {
	float x, y, w, h;
public:
	FloatRect() = default;
	FloatRect(float _x, float _y, float _w, float _h);
};
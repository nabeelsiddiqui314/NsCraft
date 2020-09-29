#include "Vector2.h"

Vector2::Vector2(int _x, int _y)
	: x(_x), y(_y) {}

const Vector2 Vector2::operator+(const Vector2& other) const {
	return { x + other.x, y + other.y };
}

const Vector2 Vector2::operator-(const Vector2& other) const {
	return { x - other.x, y - other.y };
}

const Vector2 Vector2::operator*(const Vector2& other) const {
	return { x * other.x, y * other.y };
}

const Vector2 Vector2::operator/(const Vector2& other) const {
	return { x / other.x, y / other.y };
}

const Vector2 Vector2::operator%(const Vector2& other) const {
	return { x % other.x, y % other.y };
}

const Vector2 Vector2::operator+(int other) const {
	return { x + other, y + other };
}

const Vector2 Vector2::operator-(int other) const {
	return { x - other, y - other };
}

const Vector2 Vector2::operator*(int other) const {
	return { x * other, y * other };
}

const Vector2 Vector2::operator/(int other) const {
	return { x / other, y / other };
}

const Vector2 Vector2::operator%(int other) const {
	return { x % other, y % other };
}

void Vector2::operator+=(const Vector2& other) {
	x += other.x;
	y += other.y;
}

void Vector2::operator-=(const Vector2& other) {
	x -= other.x;
	y -= other.y;
}

void Vector2::operator*=(const Vector2& other) {
	x *= other.x;
	y *= other.y;
}

void Vector2::operator/=(const Vector2& other) {
	x /= other.x;
	y /= other.y;
}

void Vector2::operator%=(const Vector2& other) {
	x %= other.x;
	y %= other.y;
}

bool Vector2::operator==(const Vector2& other) const {
	return x == other.x &&
		y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const {
	return x != other.x ||
		y != other.y;
}
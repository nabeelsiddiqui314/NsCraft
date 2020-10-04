#include "Vector3.h"

Vector3::Vector3(int _x, int _y, int _z) 
	: x(_x), y(_y), z(_z) {}

const Vector3 Vector3::operator+(const Vector3& other) const {
	return { x + other.x, y + other.y, z + other.z };
}

const Vector3 Vector3::operator-(const Vector3& other) const {
	return { x - other.x, y - other.y, z - other.z };
}

const Vector3 Vector3::operator*(const Vector3& other) const {
	return { x * other.x, y * other.y, z * other.z };
}

const Vector3 Vector3::operator/(const Vector3& other) const {
	return { x / other.x, y / other.y, z / other.z };
}

const Vector3 Vector3::operator%(const Vector3& other) const {
	return {x % other.x, y % other.y, z % other.z };
}

const Vector3 Vector3::operator+(int other) const {
	return {x + other, y + other, z + other};
}

const Vector3 Vector3::operator-(int other) const {
	return { x - other, y - other, z - other };
}

const Vector3 Vector3::operator*(int other) const {
	return { x * other, y * other, z * other };
}

const Vector3 Vector3::operator/(int other) const {
	return { x / other, y / other, z / other };
}

const Vector3 Vector3::operator%(int other) const {
	return { x % other, y % other, z % other };
}

void Vector3::operator+=(const Vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vector3::operator-=(const Vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void Vector3::operator*=(const Vector3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

void Vector3::operator/=(const Vector3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
}

void Vector3::operator%=(const Vector3& other) {
	x %= other.x;
	y %= other.y;
	z %= other.z;
}

bool Vector3::operator==(const Vector3& other) const {
	return x == other.x &&
		   y == other.y &&
		   z == other.z;
}

bool Vector3::operator!=(const Vector3& other) const {
	return x != other.x ||
		   y != other.y ||
		   z != other.z;
}

bool Vector3::operator<(const Vector3 & other) const {
	if (x < other.x) return true;
	if (x > other.x) return false;

	if (y < other.y) return true;
	if (y > other.y) return false;

	if (z < other.z) return true;
	return false;
}

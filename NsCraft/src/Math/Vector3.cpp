#include "Vector3.h"

Vector3::Vector3(int _x, int _y, int _z) 
	: x(_x), y(_y), z(_z) {}

const Vector3 Vector3::operator+(const Vector3& other) const {
	return { x + other.x, y + other.y, z + other.z };
}

const Vector3 Vector3::operator-(const Vector3& other) const {
	return { x - other.x, y - other.y, z - other.z };
}

const Vector3 Vector3::operator%(const Vector3& other) const {
	return {x % other.x, y % other.y, z % other.z };
}

void Vector3::operator+=(const Vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vector3::operator-=(const Vector3 & other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
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

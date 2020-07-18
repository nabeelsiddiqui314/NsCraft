#include "Vector3.h"

const Vector3 Vector3::operator+(const Vector3& other) const {
	return { x + other.x, y + other.y, z + other.z };
}

const Vector3 Vector3::operator-(const Vector3& other) const {
	return { x - other.x, y - other.y, z - other.z };
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

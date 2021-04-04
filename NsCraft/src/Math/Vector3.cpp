#include "Vector3.h"

Vector3::Vector3(int _x, int _y, int _z) 
	: x(_x), y(_y), z(_z) {}

Vector3::operator glm::vec3() const {
	return glm::vec3(x, y, z);
}

const Vector3 Vector3::operator+(const Vector3& other) const {
	return { x + other.x, y + other.y, z + other.z };
}

const Vector3 Vector3::operator-(const Vector3& other) const {
	return { x - other.x, y - other.y, z - other.z };
}

int Vector3::dot(const Vector3& other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3& other) const {
	return { y * other.z - other.y * z,
	         other.x * z - x * other.z,
	         x * other.y - other.x * y };
}

const Vector3 Vector3::operator*(int scalar) const {
	return { x * scalar, y * scalar, z * scalar };
}

const Vector3 Vector3::operator/(int scalar) const {
	return { x / scalar, y / scalar, z / scalar };
}

const Vector3 Vector3::operator%(int scalar) const {
	return { x % scalar, y % scalar, z % scalar };
}

void Vector3::operator*=(int scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

void Vector3::operator/=(int scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
}

void Vector3::operator%=(int scalar) {
	x %= scalar;
	y %= scalar;
	z %= scalar;
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

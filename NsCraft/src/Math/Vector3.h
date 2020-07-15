#pragma once

struct Vector3 {
	int x, y, z;
public:
	const Vector3 operator+(const Vector3& other) const;
	const Vector3 operator-(const Vector3& other) const;

	void operator+=(const Vector3& other);
	void operator-=(const Vector3& other);
};
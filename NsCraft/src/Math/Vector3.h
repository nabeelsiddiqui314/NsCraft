#pragma once
#include <functional>

struct Vector3 {
	int x, y, z;
public:
	Vector3() = default;
	Vector3(int _x, int _y, int _z);
public:
	const Vector3 operator+(const Vector3& other) const;
	const Vector3 operator-(const Vector3& other) const;
	const Vector3 operator*(const Vector3& other) const;
	const Vector3 operator/(const Vector3& other) const;
	const Vector3 operator%(const Vector3& other) const;

	const Vector3 operator+(int other) const;
	const Vector3 operator-(int other) const;
	const Vector3 operator*(int other) const;
	const Vector3 operator/(int other) const;
	const Vector3 operator%(int other) const;

	void operator+=(const Vector3& other);
	void operator-=(const Vector3& other);
	void operator*=(const Vector3& other);
	void operator/=(const Vector3& other);
	void operator%=(const Vector3& other);

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	bool operator<(const Vector3& other) const;
};

namespace std {
	template<>
	struct std::hash<Vector3> {
		size_t operator()(const Vector3& vec) const {
			size_t h1 = std::hash<int>()(vec.x);
			size_t h2 = std::hash<int>()(vec.y);
			size_t h3 = std::hash<int>()(vec.z);
			return (h1 ^ (h2 << 1)) ^ h3;
		}
	};
}
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

	void operator+=(const Vector3& other);
	void operator-=(const Vector3& other);
	void operator*=(const Vector3& other);
	void operator/=(const Vector3& other);
	void operator%=(const Vector3& other);

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
};

namespace std {
	template<>
	struct std::hash<Vector3> {
		size_t operator()(const Vector3& vec) const {
			std::hash<int> hasher;
			auto hashx = hasher(vec.x);
			auto hashy = hasher(vec.y);
			auto hashz = hasher(vec.z);

			return std::hash<int>{}((hashx ^ (hashy << hashz) ^ hashz));
		}
	};
}
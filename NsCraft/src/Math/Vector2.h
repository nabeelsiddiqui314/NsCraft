#pragma once
#include <functional>

struct Vector2 {
	int x, y;
public:
	Vector2() = default;
	Vector2(int _x, int _y);
public:
	const Vector2 operator+(const Vector2& other) const;
	const Vector2 operator-(const Vector2& other) const;
	const Vector2 operator*(const Vector2& other) const;
	const Vector2 operator/(const Vector2& other) const;
	const Vector2 operator%(const Vector2& other) const;

	const Vector2 operator+(int other) const;
	const Vector2 operator-(int other) const;
	const Vector2 operator*(int other) const;
	const Vector2 operator/(int other) const;
	const Vector2 operator%(int other) const;

	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);
	void operator*=(const Vector2& other);
	void operator/=(const Vector2& other);
	void operator%=(const Vector2& other);

	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;
};

namespace std {
	template<>
	struct std::hash<Vector2> {
		size_t operator()(const Vector2& vec) const {
			std::hash<int> hasher;
			auto hashx = hasher(vec.x);
			auto hashy = hasher(vec.y);

			return std::hash<std::size_t>{}((hashx ^ hashy) >> 2);
		}
	};
}
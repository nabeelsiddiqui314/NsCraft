#pragma once
#include <array>
#include "../Math/Vector2.h"

template <typename T, std::size_t width, std::size_t height>
class Flat2DArray {
public:
	Flat2DArray() = default;
	~Flat2DArray() = default;
public:
	T& operator[](const Vector2& position) {
		return m_flat2DArray[position.x + position.y * width];
	}

	void fill(const T& value) {
		m_flat2DArray.fill(value);
	}
private:
	std::array<T, width * height> m_flat2DArray;
};
#pragma once
#include <memory>

class ChunkShape;
struct Vector3;

typedef std::shared_ptr<ChunkShape> ChunkShapePtr;

class IShapeGenerator {
public:
	IShapeGenerator() = default;
	virtual ~IShapeGenerator() = default;
public:
	virtual ChunkShapePtr generateShape(const Vector3& position) = 0;
};
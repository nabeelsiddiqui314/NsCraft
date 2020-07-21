#pragma once
#include <memory>

struct Vector3;
class Chunk;

class IWorldObserver {
public:
	IWorldObserver() = default;
	virtual ~IWorldObserver() = default;
public:
	virtual void onChunkLoad(const Vector3& position, const std::shared_ptr<Chunk>& chunk) = 0;
	virtual void onChunkUnload(const Vector3& position, const std::shared_ptr<Chunk>& chunk) = 0;
};
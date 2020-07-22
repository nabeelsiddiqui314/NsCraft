#pragma once

struct Vector3;

class IWorldObserver {
public:
	IWorldObserver() = default;
	virtual ~IWorldObserver() = default;
public:
	virtual void onChunkLoad(const Vector3& position) = 0;
	virtual void onChunkUnload(const Vector3& position) = 0;
};
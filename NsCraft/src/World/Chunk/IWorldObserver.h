#pragma once

struct Vector3;
struct ChunkLoadEvent;
struct ChunkUnloadEvent;

class IWorldObserver {
public:
	IWorldObserver() = default;
	virtual ~IWorldObserver() = default;
public:
	virtual void onWorldEvent(const ChunkLoadEvent& event) {}
	virtual void onWorldEvent(const ChunkUnloadEvent& event) {}
};
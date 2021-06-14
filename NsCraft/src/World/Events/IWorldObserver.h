#pragma once

struct ChunkLoadEvent;
struct ChunkUnloadEvent;
struct ChunkModifyEvent;
struct BlockModifyEvent;

class IWorldObserver {
public:
	IWorldObserver() = default;
	virtual ~IWorldObserver() = default;
public:
	virtual void onEvent(ChunkLoadEvent& event) {}
	virtual void onEvent(ChunkUnloadEvent& event) {}
	virtual void onEvent(ChunkModifyEvent& event) {}
	virtual void onEvent(BlockModifyEvent& event) {}
};
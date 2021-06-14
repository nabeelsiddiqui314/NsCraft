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
	virtual void onEvent(const ChunkLoadEvent& event) {}
	virtual void onEvent(const ChunkUnloadEvent& event) {}
	virtual void onEvent(const ChunkModifyEvent& event) {}
	virtual void onEvent(const BlockModifyEvent& event) {}
};
#pragma once
#include "IWorldEvent.h"
#include "../Chunk/IWorldObserver.h"
#include "../../Math/Vector3.h"

struct ChunkUnloadEvent : IWorldEvent {
public:
	Vector3 chunkPosition;
public:
	void handleEvent(IWorldObserver& eventHandler) const override {
		eventHandler.onWorldEvent(*this);
	}
};
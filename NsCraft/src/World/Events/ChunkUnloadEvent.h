#pragma once
#include "../../EventSystem/Event.h"
#include "../../Math/Vector3.h"

struct ChunkUnloadEvent : Event<ChunkUnloadEvent> {
	Vector3 chunkPosition;
};
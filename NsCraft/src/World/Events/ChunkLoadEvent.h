#pragma once
#include "../../EventSystem/Event.h"
#include "../../Math/Vector3.h"


struct ChunkLoadEvent : Event<ChunkLoadEvent> {
	Vector3 chunkPosition;
};
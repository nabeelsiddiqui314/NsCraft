#pragma once
#include "../../EventSystem/Event.h"
#include "../../Math/Vector3.h"

struct ChunkModifyEvent : Event<ChunkModifyEvent> {
	Vector3 chunkPosition;
	Vector3 blockPosition;
};
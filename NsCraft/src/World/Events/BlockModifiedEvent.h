#pragma once
#include "../../EventSystem/Event.h"
#include "../../Math/Vector3.h"
#include "../Blocks/BlockDefs.h"

struct BlockModifiedEvent : Event<BlockModifiedEvent> {
	Vector3 chunkPosition;
	Vector3 blockPosition;

	Block_ID previousBlock;
	Block_ID newBlock;
};
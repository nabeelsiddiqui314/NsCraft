#pragma once
#include "WorldEvent.h"
#include "../../Math/Vector3.h"
#include "../Blocks/BlockDefs.h"

struct ChunkLoadEvent : WorldEvent<ChunkLoadEvent> {
	Vector3 chunkPosition;
};

struct ChunkUnloadEvent : WorldEvent<ChunkUnloadEvent> {
	Vector3 chunkPosition;
};

struct ChunkModifyEvent : WorldEvent<ChunkModifyEvent> {
	Vector3 chunkPosition;
	Vector3 blockPosition;
};

struct BlockModifyEvent : WorldEvent<BlockModifyEvent> {
	Vector3 chunkPosition;
	Vector3 blockPosition;

	Block_ID previousBlock;
	Block_ID newBlock;
};
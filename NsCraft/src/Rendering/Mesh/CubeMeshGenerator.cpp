#include "CubeMeshGenerator.h"
#include "ChunkMesh.h"
#include "../../World/Chunk/World.h"
#include "../../Math/Vector3.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "CubeFaces.h"
#include "../../Math/Directions.h"
#include "../../Math/FloatRect.h"

CubeMeshGenerator::CubeMeshGenerator(const std::shared_ptr<BlockRegistry>& blockRegistry) 
	: m_blockRegistry(blockRegistry) {}

void CubeMeshGenerator::generateMesh(ChunkMesh& mesh, const World& world, const Vector3& blockPosition) {
	auto tryAddFace = [&](const Vector3& neighborPos, const Quad& face) {
		auto neighborBlockID = world.getBlockIDAt(blockPosition + neighborPos);
		auto neighborBlock = m_blockRegistry->getBlockFromID(neighborBlockID);

		if (!neighborBlock->isOpaque()) {
			mesh.addQuad(blockPosition, { 0.0f, 0.0f, 1.0f, 1.0f }, face); // the texture coords are temporary, it will be replaced when a texture atlas is added.
		}
	};

	tryAddFace(Directions::Up,    CubeFaces::Top);
	tryAddFace(Directions::Down,  CubeFaces::Bottom);
	tryAddFace(Directions::Right, CubeFaces::Right);
	tryAddFace(Directions::Left,  CubeFaces::Left);
	tryAddFace(Directions::Front, CubeFaces::Front);
	tryAddFace(Directions::Back,  CubeFaces::Back);
}
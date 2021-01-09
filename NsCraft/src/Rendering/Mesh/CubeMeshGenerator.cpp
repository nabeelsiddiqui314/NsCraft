#include "CubeMeshGenerator.h"
#include "ChunkMesh.h"
#include "../../World/Chunk/World.h"
#include "../../Math/Vector3.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "CubeFaces.h"
#include "../../Math/Directions.h"
#include "../../World/Chunk/Chunk.h"

CubeMeshGenerator::CubeMeshGenerator(const std::string& topTexture, const std::string& sideTexture, const std::string& bottomTexture)
	: m_topTexture(topTexture),
      m_sideTexture(sideTexture),
      m_bottomTexture(bottomTexture) {}

void CubeMeshGenerator::generateMesh(ChunkMesh& mesh, const World& world, const Vector3& chunkPosition, const Vector3& blockPosition) {
	Vector3 blockPositionWorld = chunkPosition * Chunk::WIDTH + blockPosition;

	auto tryAddFace = [&](const Vector3& neighborOffset, const std::string& texture, const Quad& face) {
		auto neighborPos = blockPositionWorld + neighborOffset;
		auto neighborBlockID = world.getBlockIDAt(neighborPos);
		
		auto& blockRegistry = BlockRegistry::getInstance();
		const auto& neighborBlock = blockRegistry.getBlockFromID(neighborBlockID);

		if (!neighborBlock.isCompletelyOpaque()) {
			mesh.addQuad(blockPosition, texture, face, world.getSkyLightAt(neighborPos), world.getNaturalLightAt(neighborPos));
		}
	};

	tryAddFace(Directions::Up,    m_topTexture,     CubeFaces::Top);
	tryAddFace(Directions::Down,  m_bottomTexture,  CubeFaces::Bottom);
	tryAddFace(Directions::Right, m_sideTexture,     CubeFaces::Right);
	tryAddFace(Directions::Left,  m_sideTexture,     CubeFaces::Left);
	tryAddFace(Directions::Front, m_sideTexture,     CubeFaces::Front);
	tryAddFace(Directions::Back,  m_sideTexture,     CubeFaces::Back);
}
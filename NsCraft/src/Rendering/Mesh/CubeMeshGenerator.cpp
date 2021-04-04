#include "CubeMeshGenerator.h"
#include "ChunkMesh.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "../../Geometry/BlockFaces.h"
#include "../../Math/Directions.h"
#include "../../World/Chunk/PaddedChunk.h"

CubeMeshGenerator::CubeMeshGenerator(GLuint topTexture, GLuint sideTexture, GLuint bottomTexture)
	: m_topTexture(topTexture),
      m_sideTexture(sideTexture),
      m_bottomTexture(bottomTexture) {}

void CubeMeshGenerator::generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) {
	auto tryAddFace = [&](const Vector3& neighborOffset, GLuint texture, const BlockFace& face) {
		auto& blockRegistry = BlockRegistry::getInstance();

		ChunkNode neighborNode = chunk.getNode(position + neighborOffset);

		const auto& neighborBlock = blockRegistry.getBlockFromID(neighborNode.getBlockID());

		if (!neighborBlock.isCompletelyOpaque()) {
			mesh.addQuad(texture, face, neighborNode.getSkyLight(), neighborNode.getNaturalLight());
		}
	};

	tryAddFace(Directions::Up,   m_topTexture, BlockFaces::Top);
	tryAddFace(Directions::Down, m_bottomTexture, BlockFaces::Bottom);
	tryAddFace(Directions::Right, m_sideTexture, BlockFaces::Right);
	tryAddFace(Directions::Left, m_sideTexture, BlockFaces::Left);
	tryAddFace(Directions::Front, m_sideTexture, BlockFaces::Front);
	tryAddFace(Directions::Back, m_sideTexture,   BlockFaces::Back);
}
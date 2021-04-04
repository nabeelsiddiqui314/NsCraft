#include "LiquidMeshGenerator.h"
#include "ChunkMesh.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "../../Geometry/BlockFaces.h"
#include "../../Math/Directions.h"
#include "../../World/Chunk/PaddedChunk.h"

LiquidMeshGenerator::LiquidMeshGenerator(GLuint texture) 
	: m_texture(texture) {}

void LiquidMeshGenerator::generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) {
	auto tryAddFace = [&](const Vector3& neighborOffset, const BlockFace& face) {
		auto& blockRegistry = BlockRegistry::getInstance();

		ChunkNode node = chunk.getNode(position);
		ChunkNode neighborNode = chunk.getNode(position + neighborOffset);

		const auto& neighborBlock = blockRegistry.getBlockFromID(neighborNode.getBlockID());

		if (!neighborBlock.isCompletelyOpaque() && node.getBlockID() != neighborNode.getBlockID()) {
			mesh.addQuad(m_texture, face, neighborNode.getSkyLight(), neighborNode.getNaturalLight());
		}
	};

	tryAddFace(Directions::Up, BlockFaces::Top);
	tryAddFace(Directions::Down, BlockFaces::Bottom);
	tryAddFace(Directions::Right, BlockFaces::Right);
	tryAddFace(Directions::Left, BlockFaces::Left);
	tryAddFace(Directions::Front, BlockFaces::Front);
	tryAddFace(Directions::Back, BlockFaces::Back);
}
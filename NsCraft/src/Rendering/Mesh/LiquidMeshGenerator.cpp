#include "LiquidMeshGenerator.h"
#include "ChunkMesh.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "../../Geometry/BlockFaces.h"

LiquidMeshGenerator::LiquidMeshGenerator(GLuint texture) 
	: m_texture(texture) {}

void LiquidMeshGenerator::generateMesh(ChunkMesh& mesh, const Neighborhood& neighborhood) {
	auto tryAddFace = [&](ChunkNode neighborNode, const BlockFace& face) {
		auto& blockRegistry = BlockRegistry::getInstance();
		const auto& neighborBlock = blockRegistry.getBlockFromID(neighborNode.getBlockID());

		if (!neighborBlock.isCompletelyOpaque() && neighborhood.centre.getBlockID() != neighborNode.getBlockID()) {
			mesh.addQuad(m_texture, face, neighborNode.getSkyLight(), neighborNode.getNaturalLight());
		}
	};

	tryAddFace(neighborhood.top, BlockFaces::Top);
	tryAddFace(neighborhood.bottom, BlockFaces::Bottom);
	tryAddFace(neighborhood.right, BlockFaces::Right);
	tryAddFace(neighborhood.left, BlockFaces::Left);
	tryAddFace(neighborhood.front, BlockFaces::Front);
	tryAddFace(neighborhood.back, BlockFaces::Back);
}
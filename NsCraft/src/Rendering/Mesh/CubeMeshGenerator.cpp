#include "CubeMeshGenerator.h"
#include "ChunkMesh.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "../../Geometry/BlockFaces.h"

CubeMeshGenerator::CubeMeshGenerator(const std::string& topTexture, const std::string& sideTexture, const std::string& bottomTexture)
	: m_topTexture(topTexture),
      m_sideTexture(sideTexture),
      m_bottomTexture(bottomTexture) {}

void CubeMeshGenerator::generateMesh(ChunkMesh& mesh, const Neighborhood& neighborhood) {
	auto tryAddFace = [&](ChunkNode node, const std::string& texture, const BlockFace& face) {
		auto& blockRegistry = BlockRegistry::getInstance();
		const auto& neighborBlock = blockRegistry.getBlockFromID(node.getBlockID());

		if (!neighborBlock.isCompletelyOpaque()) {
			mesh.addQuad(texture, face, node.getSkyLight(), node.getNaturalLight());
		}
	};

	tryAddFace(neighborhood.top,    m_topTexture,    BlockFaces::Top);
	tryAddFace(neighborhood.bottom, m_bottomTexture, BlockFaces::Bottom);
	tryAddFace(neighborhood.right,  m_sideTexture,   BlockFaces::Right);
	tryAddFace(neighborhood.left,   m_sideTexture,   BlockFaces::Left);
	tryAddFace(neighborhood.front,  m_sideTexture,   BlockFaces::Front);
	tryAddFace(neighborhood.back,   m_sideTexture,   BlockFaces::Back);
}
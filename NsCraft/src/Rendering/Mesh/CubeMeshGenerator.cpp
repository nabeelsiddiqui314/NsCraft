#include "CubeMeshGenerator.h"
#include "ChunkMesh.h"
#include "../../World/Blocks/BlockRegistry.h"
#include "../../World/Blocks/Block.h"
#include "../../Geometry/BlockFaces.h"
#include "../../Math/Directions.h"
#include "../../World/Chunk/PaddedChunk.h"
#include "../../Math/Vector2.h"

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
			std::array<GLfloat, 4> ambientLight;

			for (int y = 0; y <= 1; y++) {
				for (int x = 0; x <= 1; x++) {
					std::size_t index = x + y * 2;
			
					Vector2 vert = { x, y };
			
					if (vert == Vector2(0, 1)) {
						vert = {1, 1};
					}
					else if (vert == Vector2(1, 1)) {
						vert = { 0, 1 };
					}
			
					Vector3 side1, side2, corner;
			
					if (neighborOffset == Directions::Up || 
						neighborOffset == Directions::Down) {
						side1 = {-1, 0, 0};
						side2 = neighborOffset.cross(Directions::Left);
					}
					else {
						side1 = neighborOffset.cross(Directions::Up);
						side2 = {0, -1, 0};
					}
			
					if (vert.x == 1)
						side1 *= -1;
					if (vert.y == 1)
						side2 *= -1;
			
					corner = side1 + side2 + neighborOffset;
					side1 += neighborOffset;
					side2 += neighborOffset;
			
					const auto& side1Block = blockRegistry.getBlockFromID(chunk.getNode(position + side1).getBlockID());
					const auto& side2Block = blockRegistry.getBlockFromID(chunk.getNode(position + side2).getBlockID());
					const auto& cornerBlock = blockRegistry.getBlockFromID(chunk.getNode(position + corner).getBlockID());
			
					ambientLight[index] = getAmbientOcclusion(side1Block.isCompletelyOpaque(), 
						                                           side2Block.isCompletelyOpaque(), 
						                                           cornerBlock.isCompletelyOpaque());
				}
			}

			mesh.addQuad(texture, face, neighborNode.getSkyLight(), neighborNode.getNaturalLight(), ambientLight);
		}
	};

	tryAddFace(Directions::Up,   m_topTexture, BlockFaces::Top);
	tryAddFace(Directions::Down, m_bottomTexture, BlockFaces::Bottom);
	tryAddFace(Directions::Right, m_sideTexture, BlockFaces::Right);
	tryAddFace(Directions::Left, m_sideTexture, BlockFaces::Left);
	tryAddFace(Directions::Front, m_sideTexture, BlockFaces::Front);
	tryAddFace(Directions::Back, m_sideTexture,   BlockFaces::Back);
}

float CubeMeshGenerator::getAmbientOcclusion(bool side1, bool side2, bool corner) {
	if (side1 && side2) {
		return 0.0f;
	}
	
	return (float)(3.0f - (side1 + side2 + corner)) / 3.0f;
}

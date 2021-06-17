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
	auto tryAddFace = [&](const Vector3& faceDirection, GLuint texture, const BlockFace& face) {
		auto& blockRegistry = BlockRegistry::getInstance();

		ChunkNode neighborNode = chunk.getNode(position + faceDirection);

		const auto& neighborBlock = blockRegistry.getBlockFromID(neighborNode.blockID);

		if (!neighborBlock.isCompletelyOpaque()) {
			auto ambientLighting = getFaceAmbientLighting(chunk, position, faceDirection);
			mesh.addQuad(texture, face, neighborNode.skyLight, neighborNode.naturalLight, ambientLighting);
		}
	};

	tryAddFace(Directions::Up,   m_topTexture, BlockFaces::Top);
	tryAddFace(Directions::Down, m_bottomTexture, BlockFaces::Bottom);
	tryAddFace(Directions::Right, m_sideTexture, BlockFaces::Right);
	tryAddFace(Directions::Left, m_sideTexture, BlockFaces::Left);
	tryAddFace(Directions::Front, m_sideTexture, BlockFaces::Front);
	tryAddFace(Directions::Back, m_sideTexture,   BlockFaces::Back);
}

std::array<GLfloat, 4> CubeMeshGenerator::getFaceAmbientLighting(const PaddedChunk& chunk, const Vector3& blockPosition, const Vector3& faceDirection) const {
	std::array<GLfloat, 4> ambientLight;

	auto& blockRegistry = BlockRegistry::getInstance();

	for (int y = 0; y <= 1; y++) {
		for (int x = 0; x <= 1; x++) {
			std::size_t index = x + y * 2;

			Vector2 vert = { x, y };

			if (vert == Vector2(0, 1)) {
				vert = { 1, 1 };
			}
			else if (vert == Vector2(1, 1)) {
				vert = { 0, 1 };
			}

			auto [side1, side2, corner] = computeVertexNeighbors(faceDirection, vert);

			const auto& side1Block = blockRegistry.getBlockFromID(chunk.getNode(blockPosition + side1).blockID);
			const auto& side2Block = blockRegistry.getBlockFromID(chunk.getNode(blockPosition + side2).blockID);
			const auto& cornerBlock = blockRegistry.getBlockFromID(chunk.getNode(blockPosition + corner).blockID);

			ambientLight[index] = getAmbientOcclusion(side1Block.isCompletelyOpaque(),
				side2Block.isCompletelyOpaque(),
				cornerBlock.isCompletelyOpaque());
		}
	}

	return ambientLight;
}

std::tuple<Vector3, Vector3, Vector3> CubeMeshGenerator::computeVertexNeighbors(const Vector3& faceDirection, const Vector2& vertex) const {
	Vector3 side1, side2, corner;

	if (faceDirection == Directions::Up || faceDirection == Directions::Down) {
		side1 = { -1, 0, 0 };
		side2 = faceDirection.cross(Directions::Left);
	}
	else {
		side1 = faceDirection.cross(Directions::Up);
		side2 = { 0, -1, 0 };
	}

	if (vertex.x == 1) {
		side1 *= -1;
	}
	if (vertex.y == 1) {
		side2 *= -1;
	}

	corner = side1 + side2 + faceDirection;
	side1 += faceDirection;
	side2 += faceDirection;

	return { side1, side2, corner };
}

float CubeMeshGenerator::getAmbientOcclusion(bool side1, bool side2, bool corner) const {
	if (side1 && side2) {
		return 0.0f;
	}
	
	return (float)(3.0f - (side1 + side2 + corner)) / 3.0f;
}
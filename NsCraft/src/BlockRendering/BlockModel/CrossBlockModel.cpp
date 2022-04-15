#include "CrossBlockModel.h"
#include "../../Rendering/Mesh/ChunkMesh.h"
#include "../../Geometry/BlockFaces.h"
#include "../../World/Chunk/PaddedChunk.h"

CrossBlockModel::CrossBlockModel(GLuint texture)
	: m_texture(texture) {}

void CrossBlockModel::generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) {
	std::uint8_t skyLight = chunk.getNode(position).skyLight;
	std::uint8_t naturalLight = chunk.getNode(position).naturalLight;

	mesh.addQuad(m_texture, BlockFaces::CrossA, skyLight, naturalLight);
	mesh.addQuad(m_texture, BlockFaces::CrossB, skyLight, naturalLight);
}
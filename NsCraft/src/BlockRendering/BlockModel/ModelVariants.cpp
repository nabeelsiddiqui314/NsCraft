#include "ModelVariants.h"
#include <numeric>
#include "../../World/Chunk/PaddedChunk.h"
#include "../../Math/CoordinateConversion.h"
#include "../../World/Chunk/Chunk.h"

ModelVariants::ModelVariants(const VariantList& variants)
	: m_variants(variants) {
	m_weightSum = std::accumulate(m_variants.list.begin(), m_variants.list.end(), 0, [](int sum, const auto& variant) {
		return sum += variant.weight;
	});
}

void ModelVariants::generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) {
	static std::hash<Vector3> hasher;

	Vector3 blockWorldPosition = CoordinateConversion::chunkToWorld(chunk.getPosition(), position, Chunk::WIDTH);

	int randomNumber = hasher(blockWorldPosition) % m_weightSum;

	for (auto& variant : m_variants.list) {
		if (randomNumber < variant.weight) {
			variant.model->generateMesh(position, mesh, chunk);
			break;
		}
		randomNumber -= variant.weight;
	}
}

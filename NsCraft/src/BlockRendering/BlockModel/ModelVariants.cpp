#include "ModelVariants.h"
#include "../../World/Chunk/PaddedChunk.h"
#include <numeric>

ModelVariants::ModelVariants(const VariantList& variants)
	: m_variants(variants) {
	m_weightSum = std::accumulate(m_variants.list.begin(), m_variants.list.end(), 0, [](int sum, const auto& variant) {
		return sum += variant.weight;
	});
}

void ModelVariants::generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) {
	static std::hash<Vector3> hasher;
	srand(hasher(position));
	int randomNumber = rand() % m_weightSum;

	for (auto& variant : m_variants.list) {
		if (randomNumber < variant.weight) {
			variant.model->generateMesh(position, mesh, chunk);
			break;
		}
		randomNumber -= variant.weight;
	}
}

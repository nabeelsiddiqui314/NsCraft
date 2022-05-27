#pragma once
#include "IBlockModel.h"
#include <memory>
#include <vector>

struct Variant {
	std::shared_ptr<IBlockModel> model;
	int weight;

	Variant(const std::shared_ptr<IBlockModel>& _model) 
		: model(_model), weight(1) {}
	Variant(const std::shared_ptr<IBlockModel>& _model, int weight)
		: model(_model), weight(weight) {}
};

struct VariantList {
	std::vector<Variant> list;

	VariantList(const std::initializer_list<Variant>& _list)
	: list(_list) {}
};

class ModelVariants : public IBlockModel {
public:
	ModelVariants(const VariantList& variants);
	~ModelVariants() = default;
public:
	void generateMesh(const Vector3& position, ChunkMesh& mesh, const PaddedChunk& chunk) override;
private:
	VariantList m_variants;
	int m_weightSum;
};
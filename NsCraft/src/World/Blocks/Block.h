#pragma once
#include <memory>

class IMeshGenerator;

class Block {
private:
	typedef std::shared_ptr<IMeshGenerator> MeshGeneratorPtr;
public:
	Block(const MeshGeneratorPtr& meshGenerator, bool isOpaque);
	~Block() = default;
public:
	MeshGeneratorPtr getMeshGenerator() const;
	bool isOpaque() const;
private:
	MeshGeneratorPtr m_meshGenerator;
	bool m_isOpaque;
};
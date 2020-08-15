#pragma once
#include <memory>

class IMeshGenerator;

class Block {
private:
	typedef std::shared_ptr<IMeshGenerator> MeshGeneratorPtr;
public:
	Block(const MeshGeneratorPtr& meshGenerator);
	~Block() = default;
public:
	MeshGeneratorPtr getMeshGenerator() const;
private:
	MeshGeneratorPtr m_meshGenerator;
};
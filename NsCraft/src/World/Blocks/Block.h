#pragma once
#include <memory>

class IMeshGenerator;

class Block {
private:
	typedef std::shared_ptr<IMeshGenerator> MeshGeneratorPtr;
public:
	Block();
	~Block() = default;
public:
	void setMeshGenerator(const MeshGeneratorPtr& meshGenerator);
	MeshGeneratorPtr getMeshGenerator() const;

	void setOpaqueness(bool opaqueness);
	bool isOpaque() const;

	void setLuminocity(std::uint8_t luminocity);
	std::uint8_t getLuminocity() const;
private:
	MeshGeneratorPtr m_meshGenerator;
	bool m_isOpaque;
	std::uint8_t m_luminocity;
};
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

	void setOpacity(std::uint8_t opacity);
	std::uint8_t getOpacity() const;

	bool isCompletelyOpaque() const;

	void setLuminocity(std::uint8_t luminocity);
	std::uint8_t getLuminocity() const;
private:
	MeshGeneratorPtr m_meshGenerator;
	std::uint8_t m_opacity;
	std::uint8_t m_luminocity;
};
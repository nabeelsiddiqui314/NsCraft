#pragma once
#include <memory>

class IMeshGenerator;
class Material;

class Block {
private:
	typedef std::shared_ptr<IMeshGenerator> MeshGeneratorPtr;
	typedef std::shared_ptr<Material> MaterialPtr;
public:
	Block();
	~Block() = default;
public:
	void setMeshGenerator(const MeshGeneratorPtr& meshGenerator);
	MeshGeneratorPtr getMeshGenerator() const;

	void setMaterial(const MaterialPtr& material);
	MaterialPtr getMaterial() const; 

	void setOpacity(std::uint8_t opacity);
	std::uint8_t getOpacity() const;

	bool isInvisible() const;
	bool isCompletelyOpaque() const;

	void setLuminocity(std::uint8_t luminocity);
	std::uint8_t getLuminocity() const;
private:
	std::uint8_t m_opacity;
	std::uint8_t m_luminocity;
	MeshGeneratorPtr m_meshGenerator;
	MaterialPtr m_material;
};
#pragma once
#include <memory>

class DensityMap;
struct Vector3;

class IDensityGenerator {
private:
	typedef std::shared_ptr<DensityMap> DensityMapPtr;
public:
	IDensityGenerator() = default;
	virtual ~IDensityGenerator() = default;
public:
	virtual DensityMapPtr generateDensity(const Vector3& position) = 0;
};
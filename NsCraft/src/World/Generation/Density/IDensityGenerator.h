#pragma once
#include <memory>

class DensityMap;
struct Vector3;

typedef std::shared_ptr<DensityMap> DensityMapPtr;

class IDensityGenerator {
public:
	IDensityGenerator() = default;
	virtual ~IDensityGenerator() = default;
public:
	virtual DensityMapPtr generateDensityMap(const Vector3& position) = 0;
};
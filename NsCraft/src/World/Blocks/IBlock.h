#pragma once
#include <memory>

class IMeshGenerator;

class IBlock {
public:
	IBlock() = default;
	virtual ~IBlock() = default;
public:
	virtual const std::unique_ptr<IMeshGenerator>& getMeshGenerator() const = 0;
private:
};
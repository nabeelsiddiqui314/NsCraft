#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

typedef std::uint8_t Registation_ID;

template <typename T>
class Registry {
private:
	typedef std::unique_ptr<T> ItemPtr;
public:
	Registry() = default;
	~Registry() = default;
public:
	template <typename... Args>
	const ItemPtr& registerItem(const std::string& name, Args&&... args) {
		Registation_ID id = m_items.size();
		m_items.emplace_back(std::make_unique<T>(args...));
		m_nameToIDMap.emplace(std::make_pair(name, id));
		return m_items.back();
	}

	const ItemPtr& getItemFromID(Registation_ID id) const {
		return m_items[id];
	}

	const ItemPtr& getItemFromName(const std::string& name) const {
		return m_items[m_nameToIDMap.at(name)];
	}
private:
	std::unordered_map<std::string, Registation_ID> m_nameToIDMap;
	std::vector<ItemPtr> m_items;
};
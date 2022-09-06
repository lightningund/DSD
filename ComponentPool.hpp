#pragma once
#include "Lib.hpp"

struct ComponentPool {
	// Just data
	char* data{nullptr};

	// How big each element is
	size_t element_size{};

	ComponentPool(const size_t element_size);
	~ComponentPool();

	// Get a pointer to the location in memory corresponding to the specified ID
	void* get(const EntityID index) const;
};

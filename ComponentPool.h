#pragma once
#include "Lib.h"

struct ComponentPool {
	// Just data
	char* data{nullptr};

	// How big each element is
	size_t element_size{};

	ComponentPool(size_t element_size);
	~ComponentPool();

	// Get a pointer to the location in memory corresponding to the specified ID
	void* get(EntityID index);
};

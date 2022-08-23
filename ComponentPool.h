#pragma once
#include "Lib.h"

struct ComponentPool {
	char* data{nullptr};
	size_t element_size{};

	ComponentPool(size_t element_size);
	~ComponentPool();

	void* get(EntityID index);
};

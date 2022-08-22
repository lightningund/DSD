#pragma once
#include "Lib.h"

struct ComponentPool {
	ComponentPool(size_t element_size);
	~ComponentPool();

	char* get(EntityID index);

	char* data{nullptr};
	size_t element_size{};
};


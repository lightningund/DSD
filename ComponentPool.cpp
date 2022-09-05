#include "ComponentPool.h"

ComponentPool::ComponentPool(const size_t element_size) {
	this->element_size = element_size;
	data = new char[element_size * MAX_ENTITIES];
}

ComponentPool::~ComponentPool() {
	delete data;
}

void* ComponentPool::get(const EntityID index) const {
	return data + (index * element_size);
}

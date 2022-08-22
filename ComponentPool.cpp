#include "ComponentPool.h"

ComponentPool::ComponentPool(size_t element_size) {
	this->element_size = element_size;
	data = new char[element_size * MAX_ENTITIES];
}

ComponentPool::~ComponentPool() {
	delete data;
}

char* ComponentPool::get(EntityID index) {
	return data + (index * element_size);
}

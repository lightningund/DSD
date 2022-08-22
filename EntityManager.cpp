#include "EntityManager.h"

EntityID EntityManager::create_entity() {
	// Create and add a new entity with an empty mask and an ID of the current number of entities
	entities.push_back(EntityManager::EntityDesc{entities.size(), ComponentMask{}});
	
	// Return the ID of the newly created entity
	return entities.back().id;
}

template <typename T>
T* EntityManager::assign_component(EntityID entity) {
	ComponentID component_id = get_component_id<T>();

	// If we don't have enough pools created, make some
	if (component_pools.size() <= component_id) {
		component_pools.resize(component_id + 1, nullptr);
	}

	// If we have a pool allocated but it's empty then fill it
	if (component_pools[component_id] == nullptr) {
		component_pools.push_back(new ComponentPool(sizeof(T)));
	}

	// Set the mask of the entity to mark it as included
	entities[entity].mask.set(component_id);

	// Create a new component of type T at the designated place in memory,
	// that being inside of the component pool for type T and at the index of the entity
	// Then return a pointer to that newly created component
	return new (component_pools[component_id].get(entity)) T();
}

template <typename T>
void EntityManager::remove_component(EntityID entity) {
	entities[entity].mask.unset(get_component_id<T>());
}

template <typename T>
T* EntityManager::get_component(EntityID entity) {
	ComponentID component_id = get_component_id<T>();

	// If the entity does not "have" the selected component return null
	if (!entities[id].mask.test(component_id)) return nullptr;

	// Get a pointer to the location in memory of the component,
	// that being inside of the component pool for type T and at the index of the entity
	// Then explicitly cast it to a pointer of type T and return it
	return static_cast<T*>(component_pools[component_id].get(entity));
}
#pragma once
#include "Lib.h"
#include "ComponentPool.h"

struct EntityManager {
public:
	struct EntityDesc {
		EntityID id;
		ComponentMask mask;
	};

	// Create an entity and return its ID
	EntityID create_entity();

	// Assign a component of type T to an entity
	template <typename T>
	T* assign_component(EntityID entity);

	// Remove a component of type T to an entity
	template <typename T>
	void remove_component(EntityID entity);

	// Get a list of all entityes
	template <typename T>
	std::vector<EntityID> matching_entities();

	template <typename T>
	T* get_component(EntityID entity);
private:
	std::vector<EntityDesc> entities{};
	std::vector<ComponentPool> component_pools{};
};

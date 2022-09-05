#include "EntityManager.h"

EntityID EntityManager::create_entity() {
	// Create and add a new entity with an empty mask and an ID of the current number of entities
	entities.push_back(EntityManager::EntityDesc{entities.size(), ComponentMask{}});
	
	// Return the ID of the newly created entity
	return entities.back().id;
}

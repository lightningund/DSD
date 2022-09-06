#pragma once
#include "Lib.hpp"
#include "EntityManager.hpp"

struct SceneView {
	struct Iterator {
		// Keeps a pointer to the main entity manager so we can actually get all the entities
		EntityManager* manager{};

		// Keeps track of what entity ID we are currently on
		EntityID index{};

		// Keeps track of what components we are looking for
		ComponentMask mask{};

		// Keeps track of whether or not we care about actually checking for components
		bool all{};

		// Constructor
		Iterator(EntityManager* manager, EntityID index, ComponentMask mask, bool all);

		// Return the EntityID we're currently at
		EntityID operator* () const;

		// Comparisons
		bool operator== (const Iterator& other) const;
		bool operator!= (const Iterator& other) const;

		// Move the Iterator forward
		Iterator& operator++ ();

		// Check if the index we are currently on is valid
		// Aka if it points to an entity that has the components we are looking for
		bool valid_index();
	};

	// Keeps a pointer to the main entity manager so we can actually get all the entities
	EntityManager* manager{nullptr};

	// Keeps track of what components we are looking for
	ComponentMask mask{};

	// Keeps track of whether or not we care about actually checking for components
	bool all{false};

	// General constructor where we don't give it a mask so it just returns all entities
	SceneView(EntityManager& manager);

	// Specific constructor where we actually say what we are looking for
	SceneView(EntityManager& manager, ComponentMask mask);

	// Alternate version of the specific constructor where we can pass types directly instead of a mask
	template<typename... ComponentTypes>
	SceneView(EntityManager& manager) {
		this->manager = manager;
		// Unpack the template parameters into an initializer list
		int component_ids[] = {get_component_id<ComponentTypes>()...};

		for (int i = 0; i < sizeof...(ComponentTypes); i ++) {
			mask.set(component_ids[i]);
		}
	}

	// Return an Iterator at the index of the first valid entity
	const Iterator begin() const;

	// Return an Iterator at the index of the last entity (validity is not checked)
	const Iterator end() const;
};

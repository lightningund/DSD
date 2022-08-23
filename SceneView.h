#pragma once
#include "Lib.h"
#include "EntityManager.h"

struct SceneView {
	struct Iterator {
		EntityManager* manager{};
		EntityID index{};
		ComponentMask mask{};
		bool all{};

		// Constructor
		Iterator(EntityManager* manager, EntityID index, ComponentMask mask, bool all);

		// Return the EntityID we're currently at
		EntityID operator* () const;

		// Compare two Iterators
		bool operator== (const Iterator& other) const;
		bool operator!= (const Iterator& other) const;

		// Move the Iterator forward
		Iterator& operator++ ();

		bool valid_index();
	};

	EntityManager* manager{nullptr};
	ComponentMask mask{};
	bool all{false};

	SceneView(EntityManager& manager);
	SceneView(EntityManager& manager, ComponentMask mask);

	// Return an Iterator to the beginning of this view
	const Iterator begin() const;

	// Return an Iterator to the end of this view 
	const Iterator end() const;
};

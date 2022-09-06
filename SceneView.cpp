#include "SceneView.hpp"

SceneView::Iterator::Iterator(EntityManager* manager, EntityID index, ComponentMask mask, bool all)
	: manager{manager}, index{index}, mask{mask}, all{all} {}

EntityID SceneView::Iterator::operator* () const {
	return index;
}

bool SceneView::Iterator::operator== (const Iterator& other) const {
	return index == other.index;
}

bool SceneView::Iterator::operator!= (const Iterator& other) const {
	return index != other.index;
}

SceneView::Iterator& SceneView::Iterator::operator++ () {
	// Increment the index by one, and then keep incrementing it until we hit a valid entity or the end of the list
	do {
		index ++;
	} while(index < manager->entities.size() && !valid_index());
	return *this;
}

bool SceneView::Iterator::valid_index() {
	// Check if the entity at our current index fulfills our mask requirement
	return mask_check(manager->entities[index].mask, mask);
}

SceneView::SceneView(EntityManager& manager) {
	this->manager = &manager;
	this->all = true;
}

SceneView::SceneView(EntityManager& manager, ComponentMask mask) {
	this->manager = &manager;
	this->mask = mask;
}

const SceneView::Iterator SceneView::begin() const {
	EntityID first_index = 0;
	// Increment the index while the entity at our checking index is invalid, and until we reach the end of the list
	while (!mask_check(manager->entities[first_index].mask, mask)
		&& first_index < manager->entities.size()) {
		first_index ++;
	}

	return Iterator{manager, first_index, mask, all};
}

const SceneView::Iterator SceneView::end() const {
	return Iterator{manager, manager->entities.size(), mask, all};
}

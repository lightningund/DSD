#include "Mech.h"

Mech::Mech() : Mech(MechData{}) {

}

Mech::Mech(int health, int armor, int shield, int energy) : Mech(MechData{ 0, health, armor, shield, energy, 1, 1, 1, 1 }) {

}

Mech::Mech(MechData data) {
	this->data = data;
	this->state.energy = data.energy;
	this->state.health = data.health;
	this->state.shield = data.shield;
}

MechData& Mech::getMechData() {
	return data;
}
MechState& Mech::getMechState() {
	return state;
}
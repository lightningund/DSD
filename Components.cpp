#include "Components.h"
#include "Hitbox.h"

using namespace Components;

Damageable::Damageable() {

}

void Damageable::take_damage(double dmg) {
	health -= dmg;
}

double Damageable::health_percent() {
	return health / max_health;
}

Sign::Sign() {
	parent.hitbox.size = Vec2{50, 50};

	parent.texture.loadFromFile("./res/sprites/sign.png");
	parent.sprite.setTexture(parent.texture);
}
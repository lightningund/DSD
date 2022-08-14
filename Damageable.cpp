#include "Damageable.h"

void Damageable::take_damage(double dmg) {
	health -= dmg;
}

double Damageable::health_percent() {
	return health / max_health;
}

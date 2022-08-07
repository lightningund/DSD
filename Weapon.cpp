#include "Weapon.h"

Weapon::Weapon() : Weapon(10, 10) {}

Weapon::Weapon(double dmg, double fire_rate) : dmg{dmg}, fire_rate{fire_rate} {}
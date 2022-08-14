#pragma once

class Damageable {
private:
	const double max_health{100};
	double health{100};
public:
	void take_damage(double dmg);
	double health_percent();
};

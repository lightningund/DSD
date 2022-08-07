#pragma once
#ifndef MECH
#define MECH

typedef struct {
	int mechNum = 0; //Which Mech is it
	int health = 100; //How much Health does it have
	int shield = 100; //How much Shield does it have
	int armor = 100; //How much Armor does it have
	int energy = 100; //How much Energy does it have
	float strength = 100;
	float effeciency = 100;
	float duration = 100;
	float range = 100;
} MechData;

typedef struct {
	int energy = 100;
	int health = 100;
	int shield = 100;
	int shieldCoolDownTimer = 0;
} MechState;

class Mech {
private:
	int mechType;
	MechData data;
	MechState state;
public:
	Mech();
	Mech(int, int, int, int);
	Mech(MechData);
	MechData& getMechData();
	MechState& getMechState();
};
#endif //!MECH
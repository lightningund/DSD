#pragma once

#include "Lib.h"

struct Hitbox {
private:
	Vec2 pos{};
	Vec2 size{};
	bool has_collision{true};
public:
	bool point_overlaps(Vec2 point);
};

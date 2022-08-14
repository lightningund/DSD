#pragma once

#include "Lib.h"

struct Hitbox {
private:
	bool has_collision{true};
public:
	Vec2 pos{};
	Vec2 size{};
	bool point_overlaps(Vec2 point);
};

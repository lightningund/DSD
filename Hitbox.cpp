#include "Hitbox.h"
#include "Lib.h"

bool Hitbox::point_overlaps(Vec2 point) {
	bool x_overlap = point.x > pos.x && point.x < pos.x + size.x;
	bool y_overlap = point.y > pos.y && point.y < pos.y + size.y;
	return x_overlap && y_overlap;
}

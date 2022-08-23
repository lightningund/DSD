#pragma once

#include <SFML/Graphics.hpp>
#include <bitset>

#include <iostream>

using Circle = sf::CircleShape;
using Rect = sf::RectangleShape;
using RWind = sf::RenderWindow;
using Wind = sf::Window;
using KB = sf::Keyboard;
using M = sf::Mouse;

using EntityID = unsigned long long;
using ComponentID = uint8_t;

// This is 2^64-1, we are not going to make component pools that big
//constexpr EntityID MAX_ENTITIES = (1 << (sizeof(EntityID) * 8)) - 1;
constexpr EntityID MAX_ENTITIES = 10000;
constexpr ComponentID MAX_COMPONENTS = (1 << (sizeof(ComponentID) * 8)) - 1;
using ComponentMask = std::bitset<MAX_COMPONENTS>;

extern ComponentID component_counter;

// Get the unique ID of a component type
template <typename T>
ComponentID get_component_id() {
	static ComponentID component_id = component_counter++;
	return component_id;
}

// Create a component mask from a list of types
template<typename... ComponentTypes>
ComponentMask create_mask() {
	ComponentMask mask;
	// Unpack the template parameters into an initializer list
	int component_ids[] = {get_component_id<ComponentTypes>()...};

	for (int i = 0; i < sizeof...(ComponentTypes); i ++) {
		mask.set(component_ids[i]);
	}

	return mask;
}

//Color
typedef struct Col {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Col;

//2D-Vector
template <typename T>
struct Vec2G {
	T x{};
	T y{};

	bool operator== (const Vec2G<T> a) const {
		return x == a.x && y == a.y;
	}

	bool operator!= (const Vec2G<T> a) const {
		return x != a.x || y != a.y;
	}

	void operator+= (const Vec2G<T> a) {
		x += a.x;
		y += a.y;
	}

	void operator-= (const Vec2G<T> a) {
		x -= a.x;
		y -= a.y;
	}

	void operator*= (const T a) {
		x *= a;
		y *= a;
	}

	void operator/= (const T a) {
		x /= a;
		y /= a;
	}

	Vec2G<T> operator+ (const Vec2G<T> a) const {
		return Vec2G<T>{x + a.x, y + a.y};
	}

	Vec2G<T> operator- (const Vec2G<T> a) const {
		return Vec2G<T>{x - a.x, y - a.y};
	}

	Vec2G<T> operator* (const T a) const {
		return Vec2G<T>{x * a, y * a};
	}

	Vec2G<T> operator/ (const T a) const {
		return Vec2G<T>{x / a, y / a};
	}
};

typedef Vec2G<double> Vec2;

// Generate a new Color object with grayscale input with full opacity
Col color(uint8_t gray);

// Generate a new Color object with grayscale and alpha input
Col color(uint8_t gray, uint8_t alpha);

// Generate a new Color object with red, green, and blue inputs and full opacity
Col color(uint8_t red, uint8_t green, uint8_t blue);

// Generate a new Color object with red, green, blue, and alpha inputs
Col color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

// Generate a new Color object with red, green, blue, and alpha inputs, all in one number
Col color(uint32_t val);

//Limit a number
double limitVal(double limitee, double limit);

//Limit a number with different upper and lower bounds
double limitVal(double limitee, double upper_lim, double lower_lim);

//Check if a number is outside of bounds
bool isLimited(double limitee, double limit);

//Check if a number is outside of different upper and lower bounds
bool isLimited(double limitee, double upper_lim, double lower_lim);

//Check if 2 squares overlap
bool overlap(double ax, double ay, double aw, double ah, double bx, double by, double bw, double bh);

//Find the angle of a vector
double getAngle(Vec2);

// Convert an input in radians into degrees
double radiansToDegrees(double radians);

// Convert from Col to sf::Color
sf::Color col_to_sf_color(Col col);

// Convert from Vec2 to sf::Vector2f
sf::Vector2f vec2_to_sf_vec2f(Vec2 vec);

bool mask_check(ComponentMask subject, ComponentMask goal);

constexpr Col BLACK{0, 0, 0, 255};
constexpr Col GREY{128, 128, 128, 255};
constexpr Col WHITE{255, 255, 255, 255};
constexpr Col RED{255, 0, 0, 255};
constexpr Col GREEN{0, 255, 0, 255};
constexpr Col BLUE{0, 0, 255, 255};
constexpr Col YELLOW{255, 255, 0, 255};
constexpr Col PURPLE{255, 0, 255, 255};
constexpr Col CYAN{0, 255, 255, 255};
constexpr Col ORANGE{255, 128, 0, 255};

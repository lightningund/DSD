#pragma once

#include <SFML/Graphics.hpp>
#include <bitset>

#include <iostream>

enum WeaponType{PRIMARY, SECONDARY, MELEE};

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
	
	// Generate a new Color object with grayscale input with full opacity
	constexpr Col(uint8_t gray)
		: Col{gray, gray, gray, 255} {}

	// Generate a new Color object with grayscale and alpha input
	constexpr Col(uint8_t gray, uint8_t alpha)
		: Col{gray, gray, gray, alpha} {}

	// Generate a new Color object with red, green, and blue inputs and full opacity
	constexpr Col(uint8_t red, uint8_t green, uint8_t blue)
		: Col{red, green, blue, 255} {}

	// Generate a new Color object with red, green, blue, and alpha inputs, all in one number
	constexpr Col(uint32_t val)
		: Col{val >> 24, (val >> 16) & 0xFF, (val >> 8) & 0xFF, val & 0xFF} {}

	// Generate a new Color object with red, green, blue, and alpha inputs
	constexpr Col(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
		: r{red}, g{green}, b{blue}, a{alpha} {}
} Col;

//2D-Vector
template <typename T>
struct Vec2G {
	T x{};
	T y{};

	constexpr Vec2G() : x{}, y{} {}

	constexpr Vec2G(const T x, const T y) : x{x}, y{y} {}

	constexpr Vec2G(const Vec2G<T>& base) : x{base.x}, y{base.y} {}

	template <typename U>
	constexpr Vec2G(const Vec2G<U>& base) : x{T(base.x)}, y{T(base.y)} {}

	template <typename U>
	constexpr Vec2G(const sf::Vector2<U>& base) : x{T(base.x)}, y{T(base.y)} {}

	double get_length() const {
		return sqrt(x * x + y * y);
	}

	double get_sq_length() const {
		return x * x + y * y;
	}

	Vec2G<T> set_length(const double len) {
		double scale_factor = len / get_length();
		*this *= scale_factor;
		return *this;
	}

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

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Vec2G<T> vec) {
	stream << vec.x << ", " << vec.y;
	return stream;
}

using Vec2 = Vec2G<double>;

// Generate a new Color object with grayscale input with full opacity
Col color(const uint8_t gray);

// Generate a new Color object with grayscale and alpha input
Col color(const uint8_t gray, const uint8_t alpha);

// Generate a new Color object with red, green, and blue inputs and full opacity
Col color(const uint8_t red, const uint8_t green, const uint8_t blue);

// Generate a new Color object with red, green, blue, and alpha inputs
Col color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha);

// Generate a new Color object with red, green, blue, and alpha inputs, all in one number
Col color(const uint32_t val);

// Limit a number
double limit_val(const double limitee, const double limit);

// Limit a number with different upper and lower bounds
double limit_val(const double limitee, const double upper_lim, const double lower_lim);

// Check if a number is outside of bounds
bool is_limited(const double limitee, const double limit);

// Check if a number is outside of different upper and lower bounds
bool is_limited(const double limitee, const double upper_lim, const double lower_lim);

// Check if 2 squares overlap
bool overlap(const double ax, const double ay, const double aw, const double ah, const double bx, const double by, const double bw, const double bh);

// Find the angle of a vector
double get_angle(const Vec2);

// Get the rise/run of a vector
double get_slope(const Vec2);

Vec2 vec_from_angle(const double angle);

// Convert an input in radians into degrees
double radians_to_degrees(const double radians);

// Convert from Col to sf::Color
sf::Color col_to_sf_color(const Col col);

// Convert from Vec2 to sf::Vector2f
sf::Vector2f vec2_to_sf_vec2f(const Vec2 vec);

bool mask_check(const ComponentMask subject, const ComponentMask goal);

std::string operator+(const std::string str, const int num);
std::string operator+(const std::string str, const double num);
std::string operator+(const int num, const std::string str);
std::string operator+(const double num, const std::string str);

template <typename T>
T max(std::vector<T> arr) {
	T max_val{arr[0]};

	for (auto val : arr) {
		if (val > max_val) {
			max_val = val;
		}
	}

	return max_val;
}

template <typename T>
T min(std::vector<T> arr) {
	T min_val{arr[0]};

	for (auto val : arr) {
		if (val < min_val) {
			min_val = val;
		}
	}

	return min_val;
}

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

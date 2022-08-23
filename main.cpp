#include <SFML/Graphics.hpp>
#include <iostream>

#include "Lib.h"
#include "SceneView.h"
#include "Components.h"
#include "EntityManager.h"

void update(sf::RenderWindow& wind, EntityManager& manager);
void render_objs(sf::RenderWindow& wind, EntityManager& manager);

struct test {};

using namespace Components;

int main() {
	constexpr auto WIDTH = 800;
	constexpr auto HEIGHT = 800;
	constexpr auto STAT_UPDATE_RATE = 0.5;

	int frame_counter = 0;
	sf::Int64 frame_time_counter = 0;

	EntityManager manager{};
	
	EntityID player = manager.create_entity();
	Hitbox* player_hbox = manager.assign_component<Hitbox>(player);
	Health* player_health = manager.assign_component<Health>(player);
	SpriteSet* player_spriteset = manager.assign_component<SpriteSet>(player);
	manager.assign_component<Moveable>(player);
	manager.assign_component<Player>(player);

	player_hbox->pos = Vec2{100, 100};
	player_hbox->size = Vec2{50, 50};
	player_health->health = 100;
	player_health->max_health = 100;
	player_spriteset->texture.loadFromFile("res/sprites/player.png");
	player_spriteset->sprite.setTexture(player_spriteset->texture);

	EntityID dummy = manager.create_entity();
	manager.assign_component<Hitbox>(dummy);

	EntityID sign = manager.create_entity();
	Hitbox* sign_hbox = manager.assign_component<Hitbox>(sign);
	SpriteSet* sign_spriteset = manager.assign_component<SpriteSet>(sign);
	Health* sign_health = manager.assign_component<Health>(sign);
	manager.assign_component<Sign>(sign);

	sign_hbox->pos = Vec2{200, 100};
	sign_hbox->size = Vec2{50, 50};
	sign_health->health = 100;
	sign_health->max_health = 100;
	sign_spriteset->texture.loadFromFile("res/sprites/sign.png");
	sign_spriteset->sprite.setTexture(sign_spriteset->texture);

	EntityID sign2 = manager.create_entity();
	Hitbox* sign2_hbox = manager.assign_component<Hitbox>(sign2);
	SpriteSet* sign2_spriteset = manager.assign_component<SpriteSet>(sign2);
	manager.assign_component<Sign>(sign2);

	sign2_hbox->pos = Vec2{300, 100};
	sign2_hbox->size = Vec2{50, 50};
	sign2_spriteset->texture.loadFromFile("res/sprites/sign.png");
	sign2_spriteset->sprite.setTexture(sign2_spriteset->texture);

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Deep Sea Death");
	
	sf::Clock clk;

	while (window.isOpen()) { //Main Loop
		if (clk.getElapsedTime().asMicroseconds() >= (1000000 / 60)) {
			frame_time_counter += clk.getElapsedTime().asMicroseconds();
			frame_counter ++;

			if (frame_time_counter >= 1000000 * STAT_UPDATE_RATE) {
				sf::Int64 frame_time = clk.getElapsedTime().asMicroseconds();
				double frame_rate = frame_counter / STAT_UPDATE_RATE;
				frame_time_counter = 0;
				frame_counter = 0;

				std::cout << frame_time / 1000 << "ms " << frame_rate << "fps\n";
			}
			clk.restart();

			update(window, manager);

			render_objs(window, manager);
		}
	}

	return 0;
}

void move_entity(Vec2 movement, EntityID entity, EntityManager& manager) {
	Hitbox* hbox = manager.get_component<Hitbox>(entity);
	hbox->pos += movement;
}

void damage_entity(double amnt, EntityID entity, EntityManager& manager) {
	Health* health = manager.get_component<Health>(entity);
	health->health -= amnt;
}

void update(sf::RenderWindow& wind, EntityManager& manager) {
	sf::Event event;
	while (wind.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			wind.close();
		}
	}

	ComponentMask player_mask = create_mask<Player>();
	for (EntityID player : SceneView(manager, player_mask)) {
		Vec2 movement{};
		if (KB::isKeyPressed(KB::W)) movement += Vec2{0, -1};
		if (KB::isKeyPressed(KB::A)) movement += Vec2{-1, 0};
		if (KB::isKeyPressed(KB::S)) movement += Vec2{0, 1};
		if (KB::isKeyPressed(KB::D)) movement += Vec2{1, 0};

		if (movement != Vec2{0, 0}) {
			move_entity(movement * 10, player, manager);
		}

		if (M::isButtonPressed(M::Left)) {
			damage_entity(1, player, manager);
		}
	}
	
	if (KB::isKeyPressed(KB::Escape)) {
		wind.close();
	}
}

void render_objs(sf::RenderWindow& wind, EntityManager& manager) {
	wind.clear();
	ComponentMask renderable_mask = create_mask<Hitbox, SpriteSet>();
	for (EntityID entity : SceneView(manager, renderable_mask)) {
		Hitbox* hbox = manager.get_component<Hitbox>(entity);
		SpriteSet* spriteset = manager.get_component<SpriteSet>(entity);

		spriteset->sprite.setPosition(vec2_to_sf_vec2f(hbox->pos));
		spriteset->sprite.setScale(vec2_to_sf_vec2f(hbox->size / 32.0));
		wind.draw(spriteset->sprite);
	}

	ComponentMask healthbar_mask = create_mask<Health>() | renderable_mask;
	for (EntityID entity : SceneView(manager, healthbar_mask)) {
		constexpr auto healthbar_height = 20;
		constexpr auto healthbar_trim = 2;

		Hitbox* hbox = manager.get_component<Hitbox>(entity);
		Health* health = manager.get_component<Health>(entity);
		double health_percent = health->health / health->max_health;

		Rect bar_bg{{float(hbox->size.x), float(healthbar_height)}};
		bar_bg.setPosition(float(hbox->pos.x), float(hbox->pos.y + hbox->size.y));
		bar_bg.setFillColor(col_to_sf_color(GREY));
		Rect bar{bar_bg};
		bar.move(healthbar_trim, healthbar_trim);
		bar.setSize({float((hbox->size.x - healthbar_trim * 2) * health_percent), float(healthbar_height - healthbar_trim * 2)});
		bar.setFillColor(col_to_sf_color(RED));
		wind.draw(bar_bg);
		wind.draw(bar);
	}
	wind.display();
}
//
//void render_damageable(sf::RenderWindow& wind, EntityID obj) {
//	constexpr auto healthbar_height = 20;
//	constexpr auto healthbar_trim = 3;
//
//	Hitbox hbox = obj.hitbox;
//
//	Rect bar_bg{{float(hbox.size.x), float(healthbar_height)}};
//	bar_bg.setPosition(float(hbox.pos.x), float(hbox.pos.y + hbox.size.y));
//	bar_bg.setFillColor(col_to_sf_color(GREY));
//	Rect bar{bar_bg};
//	bar.move(healthbar_trim, healthbar_trim);
//	bar.setSize({float((hbox.size.x - healthbar_trim * 2) * obj.health_percent()), float(healthbar_height - healthbar_trim * 2)});
//	bar.setFillColor(col_to_sf_color(RED));
//	wind.draw(bar_bg);
//	wind.draw(bar);
//}
//
//void player_shoot() {
//
//}
//
//void player_move(double, double) {
//
//}
//
//void player_face(double, double) {
//
//}

// I wrote this code and I don't want to lose it so I'm stashing it away here for the moment
// bool Hitbox::point_overlaps(Vec2 point) {
//	bool x_overlap = point.x > pos.x && point.x < pos.x + size.x;
//	bool y_overlap = point.y > pos.y && point.y < pos.y + size.y;
//	return x_overlap && y_overlap;
// }

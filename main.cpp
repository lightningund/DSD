#include <SFML/Graphics.hpp>
#include <iostream>

#include "Lib.h"
#include "Components.h"
#include "EntityManager.h"

void update(sf::RenderWindow& wind, EntityManager manager);
void render_objs(sf::RenderWindow& wind, EntityManager manager);

int main() {

	constexpr auto WIDTH = 800;
	constexpr auto HEIGHT = 800;
	constexpr auto STAT_UPDATE_RATE = 0.5;

	int frame_counter = 0;
	sf::Int64 frame_time_counter = 0;

	EntityManager manager;

	EntityID player = manager.create_entity();
	manager.assign_component<Components::Hitbox>(player);
	manager.assign_component<Components::Damageable>(player);

	EntityID sign = manager.create_entity();
	manager.assign_component<Components::Hitbox>(sign);
	manager.assign_component<Components::Damageable>(sign);
	manager.assign_component<Components::Sign>(sign);

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

void update(sf::RenderWindow& wind, EntityManager manager) {
	sf::Event event;
	while (wind.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			wind.close();
		}
	}

	player.update();

	if (KB::isKeyPressed(KB::W)) {
		player.move(0, -1);
	}
	if (KB::isKeyPressed(KB::A)) {
		player.move(-1, 0);
	}
	if (KB::isKeyPressed(KB::S)) {
		player.move(0, 1);
	}
	if (KB::isKeyPressed(KB::D)) {
		player.move(1, 0);
	}
	if (M::isButtonPressed(M::Left)) {
		player.shoot();
		//player.take_damage(10);
	}
	if (KB::isKeyPressed(KB::Escape)) {
		wind.close();
	}
	sf::Vector2i MP = M::getPosition(wind);
	//player.face(((MP.x - player.getCenter().x) / 10), ((MP.y - player.getCenter().y) / 10));
}

void render_objs(sf::RenderWindow& wind, EntityManager manager) {
	wind.clear();
	for (Entity* obj : objs) {
		obj->render(wind);
	}
	wind.display();
}

void render_damageable(sf::RenderWindow& wind, EntityID obj) {
	constexpr auto healthbar_height = 20;
	constexpr auto healthbar_trim = 3;

	Hitbox hbox = obj.hitbox;

	Rect bar_bg{{float(hbox.size.x), float(healthbar_height)}};
	bar_bg.setPosition(float(hbox.pos.x), float(hbox.pos.y + hbox.size.y));
	bar_bg.setFillColor(col_to_sf_color(GREY));
	Rect bar{bar_bg};
	bar.move(healthbar_trim, healthbar_trim);
	bar.setSize({float((hbox.size.x - healthbar_trim * 2) * obj.health_percent()), float(healthbar_height - healthbar_trim * 2)});
	bar.setFillColor(col_to_sf_color(RED));
	wind.draw(bar_bg);
	wind.draw(bar);
}

void player_shoot() {

}

void player_move(double, double) {

}

void player_face(double, double) {

}

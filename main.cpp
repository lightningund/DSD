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

sf::Font font{};

// Nothing in here has any comments because it is in constant flux
int main() {
	font.loadFromFile("res/UbuntuMono-Regular.ttf");
	constexpr auto WIDTH{800};
	constexpr auto HEIGHT{800};
	constexpr auto STAT_UPDATE_RATE{0.5};

	int frame_counter{0};
	sf::Int64 frame_time_counter{0};

	sf::RenderWindow window{sf::VideoMode(WIDTH, HEIGHT), "Deep Sea Death"};

	sf::Clock clk{};

	EntityManager manager{};
	
	EntityID player = manager.create_entity();
	auto player_hbox = manager.assign_component<Hitbox>(player);
	auto player_health = manager.assign_component<Health>(player);
	auto player_primary = manager.assign_component<Primary>(player);
	auto player_secondary = manager.assign_component<Secondary>(player);
	auto player_melee = manager.assign_component<Melee>(player);
	auto player_player = manager.assign_component<Player>(player);
	auto player_spriteset = manager.assign_component<SpriteSet>(player);
	auto player_ammo_disp = manager.assign_component<AmmoDisplay>(player);
	auto player_health_disp = manager.assign_component<HealthDisplay>(player);
	manager.assign_component<Moveable>(player);

	player_hbox->pos = Vec2{100, 100};
	player_hbox->size = Vec2{50, 50};
	player_health->health = 100;
	player_health->max_health = 100;
	player_primary->ammo_reserve_max = 200;
	player_primary->ammo_reserve = 200;
	player_primary->magazine_max = 20;
	player_primary->magazine = 20;
	player_primary->dmg = 5;
	player_primary->fire_rate = 1.0;
	player_secondary->ammo_reserve_max = 100;
	player_secondary->ammo_reserve = 100;
	player_secondary->magazine_max = 10;
	player_secondary->magazine = 10;
	player_secondary->dmg = 5;
	player_secondary->fire_rate = 0.5;
	player_melee->attack_speed = 1.2;
	player_melee->dmg = 20;
	player_melee->range = 2;
	player_player->curr_wep = player_primary;
	player_spriteset->texture.loadFromFile("res/sprites/player.png");
	player_spriteset->sprite.setTexture(player_spriteset->texture);
	player_ammo_disp->target = (Gun*)player_player->curr_wep;
	player_health_disp->target = player_health;

	EntityID sign = manager.create_entity();
	auto sign_hbox = manager.assign_component<Hitbox>(sign);
	auto sign_spriteset = manager.assign_component<SpriteSet>(sign);
	auto sign_health = manager.assign_component<Health>(sign);
	manager.assign_component<Sign>(sign);

	sign_hbox->pos = Vec2{200, 100};
	sign_hbox->size = Vec2{50, 50};
	sign_health->health = 100;
	sign_health->max_health = 100;
	sign_spriteset->texture.loadFromFile("res/sprites/sign.png");
	sign_spriteset->sprite.setTexture(sign_spriteset->texture);

	EntityID sign2 = manager.create_entity();
	auto sign2_hbox = manager.assign_component<Hitbox>(sign2);
	auto sign2_spriteset = manager.assign_component<SpriteSet>(sign2);
	manager.assign_component<Sign>(sign2);

	sign2_hbox->pos = Vec2{300, 100};
	sign2_hbox->size = Vec2{50, 50};
	sign2_spriteset->texture.loadFromFile("res/sprites/sign.png");
	sign2_spriteset->sprite.setTexture(sign2_spriteset->texture);

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
	auto hbox = manager.get_component<Hitbox>(entity);
	hbox->pos += movement;
}

void damage_entity(double amnt, EntityID entity, EntityManager& manager) {
	auto health = manager.get_component<Health>(entity);
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

void draw_sprites(sf::RenderWindow& wind, EntityManager& manager) {
	ComponentMask renderable_mask = create_mask<Hitbox, SpriteSet>();
	for (EntityID entity : SceneView(manager, renderable_mask)) {
		auto hbox = manager.get_component<Hitbox>(entity);
		auto spriteset = manager.get_component<SpriteSet>(entity);

		spriteset->sprite.setPosition(vec2_to_sf_vec2f(hbox->pos));
		spriteset->sprite.setScale(vec2_to_sf_vec2f(hbox->size / 32.0));
		wind.draw(spriteset->sprite);
	}
}

void draw_healthbar(sf::RenderWindow& wind, double health_percent, double x, double y, double width, double height) {
	float trim = float(height) * 0.1f;
	Rect bar_bg{{float(width), float(height)}};
	bar_bg.setPosition(float(x), float(y));
	bar_bg.setFillColor(col_to_sf_color(GREY));
	Rect bar{bar_bg};
	bar.move(trim, trim);
	bar.setSize({(float(width) - trim * 2) * float(health_percent), float(height) - trim * 2});
	bar.setFillColor(col_to_sf_color(RED));
	wind.draw(bar_bg);
	wind.draw(bar);
}

void draw_healthbars(sf::RenderWindow& wind, EntityManager& manager) {
	ComponentMask healthbar_mask = create_mask<Health>();
	for (EntityID entity : SceneView(manager, healthbar_mask)) {
		constexpr auto healthbar_height = 20;

		auto hbox = manager.get_component<Hitbox>(entity);
		auto health = manager.get_component<Health>(entity);
		double health_percent = health->health / health->max_health;

		draw_healthbar(wind, health_percent, hbox->pos.x, hbox->pos.y + hbox->size.y, hbox->size.x, healthbar_height);
	}
}

void draw_ui(sf::RenderWindow& wind, EntityManager& manager) {
	ComponentMask health_disp_mask = create_mask<HealthDisplay>();
	for (EntityID entity : SceneView(manager, health_disp_mask)) {
		auto disp = manager.get_component<HealthDisplay>(entity);
		auto healthbar_width = wind.getSize().x * 0.15;
		auto healthbar_height = healthbar_width * 0.2;
		auto healthbar_trim = healthbar_height * 0.1;
		auto healthbar_padding = healthbar_trim * 5;
		auto healthbar_x = wind.getSize().x - healthbar_width - healthbar_padding;
		auto healthbar_y = healthbar_padding;

		auto health = disp->target;
		auto health_percent = health->health / health->max_health;

		draw_healthbar(wind, health_percent, healthbar_x, healthbar_y, healthbar_width, healthbar_height);
	}

	ComponentMask ammo_disp_mask = create_mask<AmmoDisplay>();
	for (EntityID entity : SceneView(manager, health_disp_mask)) {
		auto disp = manager.get_component<AmmoDisplay>(entity);
		auto wep = disp->target;

		if (wep != nullptr) {
			sf::Text text;
			text.setFont(font);
			text.setPosition(wind.getSize().x * 0.8f, wind.getSize().y * 0.9f);
			text.setString(wep->magazine + std::string("/") + wep->magazine_max);
			text.setCharacterSize(24);
			text.setFillColor(col_to_sf_color(WHITE));
			wind.draw(text);
		}
	}
}

void render_objs(sf::RenderWindow& wind, EntityManager& manager) {
	wind.clear();

	draw_sprites(wind, manager);
	draw_healthbars(wind, manager);
	draw_ui(wind, manager);

	wind.display();
}

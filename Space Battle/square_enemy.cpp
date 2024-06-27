#include "square_enemy.h"
#include <raylib.h>
#include <cmath>
#include <time.h>

Square_enemy::Square_enemy() {
	active = false;
	a_block = false;
	block = false;
	a_timer = clock();
	timer = clock();
	position = { -1000,-1000 };
	speed = { 0,0 };
	f_speed = 3.0f;
	size = 30;
	rotation = 0;
	health = 100;
	texture = LoadTexture(".\\square_enemy.png");
}

void Square_enemy::Draw() {
	DrawTexture(texture, position.x - size / 2, position.y - size / 2, WHITE);
}

void Square_enemy::Update(Player player) {
	rotation = (atan2(player.position.x - position.x, player.position.y - position.y) * -57.29578f) + 180;

	if (block == true and (clock() - timer > 500)) {
		block = false;
	}

	if (a_block == true and (clock() - a_timer > 1000)) {
		a_block = false;
		a_timer = clock();
	}

	if (block == false and a_block == false) {
		speed.x = sin(rotation * DEG2RAD) * f_speed;
		speed.y = -(cos(rotation * DEG2RAD) * f_speed);
	}

	position.x += speed.x;
	position.y += speed.y;

	if (a_block == false and clock() - a_timer > 5000) {
		speed.x *= 4;
		speed.y *= 4;
		a_block = true;
		timer = clock();
		a_timer = clock();
	}

	if (position.x > GetScreenWidth() + 75) position.x = -(45);
	else if (position.x < -(75)) position.x = GetScreenWidth() + 45;
	if (position.y > (GetScreenHeight() + 75)) position.y = -(45);
	else if (position.y < -(75)) position.y = GetScreenHeight() + 45;

	if (health <= 0) {
		active = false;
	}
}

void Square_enemy::Reset() {
	active = true;
	a_block = false;
	block = false;
	a_timer = clock();
	timer = clock();
	speed = { 0,0 };
	f_speed = 3.0f;
	size = 30;
	rotation = 0;
	health = 100;
}
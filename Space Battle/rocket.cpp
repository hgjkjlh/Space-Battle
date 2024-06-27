#include "rocket.h"
#include <time.h>

Rocket::Rocket() {
	active = false;
	position = { -100,-100 };
	speed = { 0,0 };
	f_speed = 5.0f;
	size = 10;
	rotation = 0;
	damage = 10;
	timer = clock();
	burst = false;
	burst_timer = clock();
	texture = LoadTexture(".\\rocket.png");
	burst_texture = LoadTexture(".\\burst.png");
}

void Rocket::Draw() {
	if (burst == false) {
		DrawTexture(texture, position.x - size / 2, position.y - size / 2, WHITE);
	}
	else if (burst == true) {
		DrawTexture(burst_texture, position.x - size * 4, position.y - size * 4, WHITE);
	}
}

void Rocket::Update(Player &player) {
	rotation = (atan2(player.position.x - position.x, player.position.y - position.y) * -57.29578f) + 180;

	speed.x = sin(rotation * DEG2RAD) * f_speed;
	speed.y = -(cos(rotation * DEG2RAD) * f_speed);

	if (burst == false) {
		position.x += speed.x;
		position.y += speed.y;
	}

	if (clock() - timer > 2000 and burst == false) {
		burst = true;
		burst_timer = clock();
	}

	if (CheckCollisionPointCircle(player.position, position, size * 3) and burst == false) {
		burst = true;
		burst_timer = clock();
		player.health -= 50;
	}

	if (burst == true and clock() - burst_timer > 200) {
		active = false;
	}
}
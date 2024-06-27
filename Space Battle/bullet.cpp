#include "bullet.h"

Bullet::Bullet() {
	active = false;
	position = { -100,-100 };
	speed = { 0,0 };
	radius = 5;
	damage = 10;
	texture = LoadTexture(".\\bullet.png");
}

void Bullet::Draw() {
	DrawTexture(texture, position.x - radius, position.y - radius, WHITE);
}

void Bullet::Update() {
	position.x += speed.x;
	position.y += speed.y;
}
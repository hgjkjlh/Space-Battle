#pragma once
#include <raylib.h>
#include "player.h"

class Rocket
{
public:
	Rocket();
	bool active;
	Vector2 position;
	Vector2 speed;
	float f_speed;
	int size;
	float rotation;
	int damage;
	int timer;
	bool burst;
	int burst_timer;
	Texture2D texture;
	Texture2D burst_texture;
	void Draw();
	void Update(Player &player);
	void Burst();
};
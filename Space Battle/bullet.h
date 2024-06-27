#pragma once
#include <raylib.h>

class Bullet
{
public:
	Bullet();
	bool active;
	Vector2 position;
	Vector2 speed;
	float radius;
	int damage;
	Texture2D texture;
	void Draw();
	void Update();
	void Attack();
};
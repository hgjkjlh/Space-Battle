#pragma once
#include "player.h"
#include "asteroid.h"
#include "square_enemy.h"
#include "double_square_enemy.h"

class Game
{
public:
	Game(int max_big_asteroids, int max_medium_asteroids, int max_small_asteroids);
	Player player;
	Square_enemy sq_enemies[10];
	Double_square_enemy d_sq_enemies[10];
	int max_big_asteroids;
	int max_medium_asteroids;
	int max_small_asteroids;
	Asteroid big_asteroids[10];
	Asteroid medium_asteroids[10];
	Asteroid small_asteroids[20];
	bool preparation;
	int level;
	bool win;
	void Draw();
	void Update();
	void Collision();
	void CreateAsteroid();
	void Collision_Enemy();
	bool Chek_Enemy();
	void Level(int level);
	void Reset(int max_big_asteroids, int max_medium_asteroids, int max_small_asteroids);
};
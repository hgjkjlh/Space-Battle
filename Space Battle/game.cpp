#include "game.h"
#include <time.h>

Game::Game(int max_big_asteroids, int max_medium_asteroids, int max_small_asteroids) {
    this->max_big_asteroids = max_big_asteroids;
    this->max_medium_asteroids = max_medium_asteroids;
    this->max_small_asteroids = max_small_asteroids;
    player = Player();
    sq_enemies[10];
    d_sq_enemies[10];
    big_asteroids[max_big_asteroids];
    medium_asteroids[max_medium_asteroids];
    small_asteroids[max_small_asteroids];
    preparation = false;
    level = 1;
    win = false;
}

void Game::Draw() {
    player.DrawRoundBullet();
    player.Draw();
    for (int i = 0; i < max_small_asteroids; ++i) {
        if (small_asteroids[i].active == true) {
            small_asteroids[i].Draw();
        }
    }
    for (int i = 0; i < max_medium_asteroids; ++i) {
        if (medium_asteroids[i].active == true) {
            medium_asteroids[i].Draw();
        }
    }
    for (int i = 0; i < max_big_asteroids; ++i) {
        if (big_asteroids[i].active == true) {
            big_asteroids[i].Draw();
        }
    }
    for (int i = 0; i < 10; ++i) {
        if (sq_enemies[i].active == true) {
            sq_enemies[i].Draw();
        }
        if (d_sq_enemies[i].active == true) {
            d_sq_enemies[i].Draw();
        }
    }
    for (int i = 0; i < 10; ++i) {
        if (d_sq_enemies[i].active == true) {
            d_sq_enemies[i].DrawRocket();
        }
    }
}

void Game::Update() {
    int var;
    srand(time(0));

    player.Move();
    player.UpdateRoundBullet();

    for (int i = 0; i < max_big_asteroids; i++)
    {
        if (big_asteroids[i].active)
        {
            big_asteroids[i].Update();
            big_asteroids[i].Update();

            if (big_asteroids[i].position.x > GetScreenWidth() + big_asteroids[i].radius * 3) big_asteroids[i].active = false;
            else if (big_asteroids[i].position.x < 0 - big_asteroids[i].radius * 3) big_asteroids[i].active = false;
            if (big_asteroids[i].position.y > GetScreenHeight() + big_asteroids[i].radius * 3) big_asteroids[i].active = false;
            else if (big_asteroids[i].position.y < 0 - big_asteroids[i].radius * 3) big_asteroids[i].active = false;
        }
        else {
            big_asteroids[i] = Asteroid();
            big_asteroids[i].radius = 30;
            var = rand() % 3;
            Vector2 position = big_asteroids[i].GetPosition(var);
            Vector2 speed = big_asteroids[i].GetSpeed(1);
            big_asteroids[i].position = position;
            big_asteroids[i].speed = speed;
            big_asteroids[i].health = 100;
            big_asteroids[i].active = true;
            big_asteroids[i].texture = LoadTexture(".\\big_asteroid.png");
        }
    }
    for (int i = 0; i < max_medium_asteroids; i++)
    {
        if (medium_asteroids[i].active)
        {
            medium_asteroids[i].Update();
            medium_asteroids[i].Update();

            if (medium_asteroids[i].position.x > GetScreenWidth() + medium_asteroids[i].radius * 3) medium_asteroids[i].active = false;
            else if (medium_asteroids[i].position.x < 0 - medium_asteroids[i].radius * 3) medium_asteroids[i].active = false;
            if (medium_asteroids[i].position.y > GetScreenHeight() + medium_asteroids[i].radius * 3) medium_asteroids[i].active = false;
            else if (medium_asteroids[i].position.y < 0 - medium_asteroids[i].radius * 3) medium_asteroids[i].active = false;
        }
        else {
            medium_asteroids[i] = Asteroid();
            medium_asteroids[i].radius = 20;
            var = rand() % 3;
            Vector2 position = medium_asteroids[i].GetPosition(var);
            Vector2 speed = medium_asteroids[i].GetSpeed(2);
            medium_asteroids[i].position = position;
            medium_asteroids[i].speed = speed;
            medium_asteroids[i].health = 50;
            medium_asteroids[i].active = true;
            medium_asteroids[i].texture = LoadTexture(".\\medium_asteroid.png");
        }
    }
    for (int i = 0; i < max_small_asteroids; i++)
    {
        if (small_asteroids[i].active)
        {
            small_asteroids[i].Update();

            if (small_asteroids[i].position.x > GetScreenWidth() + small_asteroids[i].radius * 3) small_asteroids[i].active = false;
            else if (small_asteroids[i].position.x < 0 - small_asteroids[i].radius * 3) small_asteroids[i].active = false;
            if (small_asteroids[i].position.y > GetScreenHeight() + small_asteroids[i].radius * 3) small_asteroids[i].active = false;
            else if (small_asteroids[i].position.y < 0 - small_asteroids[i].radius * 3) small_asteroids[i].active = false;
        }
        else {
            small_asteroids[i] = Asteroid();
            small_asteroids[i].radius = 10;
            var = rand() % 3;
            Vector2 position = small_asteroids[i].GetPosition(var);
            Vector2 speed = small_asteroids[i].GetSpeed(3);
            small_asteroids[i].position = position;
            small_asteroids[i].speed = speed;
            small_asteroids[i].health = 30;
            small_asteroids[i].active = true;
            small_asteroids[i].texture = LoadTexture(".\\small_asteroid.png");
        }
    }

    player.Shoot();

    for (int i = 0; i < player.max_bullets; i++)
    {
        if ((player.bullets[i].active))
        {
            for (int a = 0; a < max_big_asteroids; a++)
            {
                if (big_asteroids[a].active && CheckCollisionCircles(player.bullets[i].position, player.bullets[i].radius, big_asteroids[a].position, big_asteroids[a].radius))
                {
                    player.bullets[i].active = false;
                    big_asteroids[a].health -= player.bullets[i].damage;
                    if (big_asteroids[a].health <= 0) {
                        big_asteroids[a].active = false;
                    }
                }
            }

            for (int b = 0; b < max_medium_asteroids; b++)
            {
                if (medium_asteroids[b].active && CheckCollisionCircles(player.bullets[i].position, player.bullets[i].radius, medium_asteroids[b].position, medium_asteroids[b].radius))
                {
                    player.bullets[i].active = false;
                    medium_asteroids[b].health -= player.bullets[i].damage;
                    if (medium_asteroids[b].health <= 0) {
                        medium_asteroids[b].active = false;
                    }
                }
            }

            for (int c = 0; c < max_small_asteroids; c++)
            {
                if (small_asteroids[c].active && CheckCollisionCircles(player.bullets[i].position, player.bullets[i].radius, small_asteroids[c].position, small_asteroids[c].radius))
                {
                    player.bullets[i].active = false;
                    small_asteroids[c].health -= player.bullets[i].damage;
                    if (small_asteroids[c].health <= 0) {
                        small_asteroids[c].active = false;
                    }
                }
            }
        }
    }

    if (player.health < 400 and clock() - player.treatment_count > 100) {
        player.treatment_count = clock();
        player.health += 1;
    }
}

void Game::Collision() {
    Vector3 collider1 = { player.position.x + sin(player.rotation * DEG2RAD) * (20 / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (20 / 2.5f), 12 };
    Vector3 collider2 = { player.position.x - sin(player.rotation * DEG2RAD) * (20 / 2.5f), player.position.y + cos(player.rotation * DEG2RAD) * (20 / 2.5f), 6 };
    
    for (int a = 0; a < max_big_asteroids; a++)
    {
        if (CheckCollisionCircles({ collider1.x, collider1.y }, collider1.z, big_asteroids[a].position, big_asteroids[a].radius) && big_asteroids[a].active) {
            if ((player.speed.x >= 0 and big_asteroids[a].speed.x <= 0) or (player.speed.x <= 0 and big_asteroids[a].speed.x >= 0)) {
                player.speed.x *= -1;
                big_asteroids[a].speed.x *= -1;
                big_asteroids[a].position.x += big_asteroids[a].speed.x;
            }
            else if ((player.speed.x >= 0 and big_asteroids[a].speed.x >= 0) or (player.speed.x <= 0 and big_asteroids[a].speed.x <= 0)) {
                if (abs(player.speed.x) >= abs(big_asteroids[a].speed.x)) {
                    player.speed.x *= -1;
                }
                else {
                    big_asteroids[a].speed.x *= -1;
                    big_asteroids[a].position.x += big_asteroids[a].speed.x;
                }
            }
            if ((player.speed.y >= 0 and big_asteroids[a].speed.y <= 0) or (player.speed.y <= 0 and big_asteroids[a].speed.y >= 0)) {
                player.speed.y *= -1;
                big_asteroids[a].speed.y *= -1;
                big_asteroids[a].position.y += big_asteroids[a].speed.y;
            }
            else if ((player.speed.y >= 0 and big_asteroids[a].speed.y >= 0) or (player.speed.y <= 0 and big_asteroids[a].speed.y <= 0)) {
                if (abs(player.speed.y) >= abs(big_asteroids[a].speed.y)) {
                    player.speed.y *= -1;
                }
                else {
                    big_asteroids[a].speed.y *= -1;
                    big_asteroids[a].position.y += big_asteroids[a].speed.y;
                }
            }
            player.block = true;
            player.health -= 10;
        }
        else if (CheckCollisionCircles({ collider2.x, collider2.y }, collider2.z, big_asteroids[a].position, big_asteroids[a].radius) && big_asteroids[a].active) {
            if ((player.speed.x >= 0 and big_asteroids[a].speed.x <= 0) or (player.speed.x <= 0 and big_asteroids[a].speed.x >= 0)) {
                player.speed.x *= -1;
                big_asteroids[a].speed.x *= -1;
                big_asteroids[a].position.x += big_asteroids[a].speed.x;
            }
            else if ((player.speed.x >= 0 and big_asteroids[a].speed.x >= 0) or (player.speed.x <= 0 and big_asteroids[a].speed.x <= 0)) {
                if (abs(player.speed.x) >= abs(big_asteroids[a].speed.x)) {
                    player.speed.x *= -1;
                }
                else {
                    big_asteroids[a].speed.x *= -1;
                    big_asteroids[a].position.x += big_asteroids[a].speed.x;
                }
            }
            if ((player.speed.y >= 0 and big_asteroids[a].speed.y <= 0) or (player.speed.y <= 0 and big_asteroids[a].speed.y >= 0)) {
                player.speed.y *= -1;
                big_asteroids[a].speed.y *= -1;
                big_asteroids[a].position.y += big_asteroids[a].speed.y;
            }
            else if ((player.speed.y >= 0 and big_asteroids[a].speed.y >= 0) or (player.speed.y <= 0 and big_asteroids[a].speed.y <= 0)) {
                if (abs(player.speed.y) >= abs(big_asteroids[a].speed.y)) {
                    player.speed.y *= -1;
                }
                else {
                    big_asteroids[a].speed.y *= -1;
                    big_asteroids[a].position.y += big_asteroids[a].speed.y;
                }
            }
            player.block = true;
            player.health -= 10;
        }
    }

    for (int a = 0; a < max_medium_asteroids; a++)
    {
        if (CheckCollisionCircles({ collider1.x, collider1.y }, collider1.z, medium_asteroids[a].position, medium_asteroids[a].radius) && medium_asteroids[a].active) {
            if ((player.speed.x >= 0 and medium_asteroids[a].speed.x <= 0) or (player.speed.x <= 0 and medium_asteroids[a].speed.x >= 0)) {
                player.speed.x *= -1;
                medium_asteroids[a].speed.x *= -1;
                medium_asteroids[a].position.x += medium_asteroids[a].speed.x;
            }
            else if ((player.speed.x >= 0 and medium_asteroids[a].speed.x >= 0) or (player.speed.x <= 0 and medium_asteroids[a].speed.x <= 0)) {
                if (abs(player.speed.x) >= abs(medium_asteroids[a].speed.x)) {
                    player.speed.x *= -1;
                }
                else {
                    medium_asteroids[a].speed.x *= -1;
                    medium_asteroids[a].position.x += medium_asteroids[a].speed.x;
                }
            }
            if ((player.speed.y >= 0 and medium_asteroids[a].speed.y <= 0) or (player.speed.y <= 0 and medium_asteroids[a].speed.y >= 0)) {
                player.speed.y *= -1;
                medium_asteroids[a].speed.y *= -1;
                medium_asteroids[a].position.y += medium_asteroids[a].speed.y;
            }
            else if ((player.speed.y >= 0 and medium_asteroids[a].speed.y >= 0) or (player.speed.y <= 0 and medium_asteroids[a].speed.y <= 0)) {
                if (abs(player.speed.y) >= abs(medium_asteroids[a].speed.y)) {
                    player.speed.y *= -1;
                }
                else {
                    medium_asteroids[a].speed.y *= -1;
                    medium_asteroids[a].position.y += medium_asteroids[a].speed.y;
                }
            }
            player.block = true;
            player.health -= 10;
        }
        else if (CheckCollisionCircles({ collider2.x, collider2.y }, collider2.z, medium_asteroids[a].position, medium_asteroids[a].radius) && medium_asteroids[a].active) {
            if ((player.speed.x >= 0 and medium_asteroids[a].speed.x <= 0) or (player.speed.x <= 0 and medium_asteroids[a].speed.x >= 0)) {
                player.speed.x *= -1;
                medium_asteroids[a].speed.x *= -1;
                medium_asteroids[a].position.x += medium_asteroids[a].speed.x;
            }
            else if ((player.speed.x >= 0 and medium_asteroids[a].speed.x >= 0) or (player.speed.x <= 0 and medium_asteroids[a].speed.x <= 0)) {
                if (abs(player.speed.x) >= abs(medium_asteroids[a].speed.x)) {
                    player.speed.x *= -1;
                }
                else {
                    medium_asteroids[a].speed.x *= -1;
                    medium_asteroids[a].position.x += medium_asteroids[a].speed.x;
                }
            }
            if ((player.speed.y >= 0 and medium_asteroids[a].speed.y <= 0) or (player.speed.y <= 0 and medium_asteroids[a].speed.y >= 0)) {
                player.speed.y *= -1;
                medium_asteroids[a].speed.y *= -1;
                medium_asteroids[a].position.y += medium_asteroids[a].speed.y;
            }
            else if ((player.speed.y >= 0 and medium_asteroids[a].speed.y >= 0) or (player.speed.y <= 0 and medium_asteroids[a].speed.y <= 0)) {
                if (abs(player.speed.y) >= abs(medium_asteroids[a].speed.y)) {
                    player.speed.y *= -1;
                }
                else {
                    medium_asteroids[a].speed.y *= -1;
                    medium_asteroids[a].position.y += medium_asteroids[a].speed.y;
                }
            }
            player.block = true;
            player.health -= 10;
        }
    }

    for (int a = 0; a < max_small_asteroids; a++)
    {
        if (CheckCollisionCircles({ collider1.x, collider1.y }, collider1.z, small_asteroids[a].position, small_asteroids[a].radius) && small_asteroids[a].active) {
            if ((player.speed.x >= 0 and small_asteroids[a].speed.x <= 0) or (player.speed.x <= 0 and small_asteroids[a].speed.x >= 0)) {
                player.speed.x *= -1;
                small_asteroids[a].speed.x *= -1;
                small_asteroids[a].position.x += small_asteroids[a].speed.x;
            }
            else if ((player.speed.x >= 0 and small_asteroids[a].speed.x >= 0) or (player.speed.x <= 0 and small_asteroids[a].speed.x <= 0)) {
                if (abs(player.speed.x) >= abs(small_asteroids[a].speed.x)) {
                    player.speed.x *= -1;
                }
                else {
                    small_asteroids[a].speed.x *= -1;
                    small_asteroids[a].position.x += small_asteroids[a].speed.x;
                }
            }
            if ((player.speed.y >= 0 and small_asteroids[a].speed.y <= 0) or (player.speed.y <= 0 and small_asteroids[a].speed.y >= 0)) {
                player.speed.y *= -1;
                small_asteroids[a].speed.y *= -1;
                small_asteroids[a].position.y += small_asteroids[a].speed.y;
            }
            else if ((player.speed.y >= 0 and small_asteroids[a].speed.y >= 0) or (player.speed.y <= 0 and small_asteroids[a].speed.y <= 0)) {
                if (abs(player.speed.y) >= abs(small_asteroids[a].speed.y)) {
                    player.speed.y *= -1;
                }
                else {
                    small_asteroids[a].speed.y *= -1;
                    small_asteroids[a].position.y += small_asteroids[a].speed.y;
                }
            }
            player.block = true;
            player.health -= 10;
        }
        else if (CheckCollisionCircles({ collider2.x, collider2.y }, collider2.z, small_asteroids[a].position, small_asteroids[a].radius) && small_asteroids[a].active) {
            if ((player.speed.x >= 0 and small_asteroids[a].speed.x <= 0) or (player.speed.x <= 0 and small_asteroids[a].speed.x >= 0)) {
                player.speed.x *= -1;
                small_asteroids[a].speed.x *= -1;
                small_asteroids[a].position.x += small_asteroids[a].speed.x;
            }
            else if ((player.speed.x >= 0 and small_asteroids[a].speed.x >= 0) or (player.speed.x <= 0 and small_asteroids[a].speed.x <= 0)) {
                if (abs(player.speed.x) >= abs(small_asteroids[a].speed.x)) {
                    player.speed.x *= -1;
                }
                else {
                    small_asteroids[a].speed.x *= -1;
                    small_asteroids[a].position.x += small_asteroids[a].speed.x;
                }
            }
            if ((player.speed.y >= 0 and small_asteroids[a].speed.y <= 0) or (player.speed.y <= 0 and small_asteroids[a].speed.y >= 0)) {
                player.speed.y *= -1;
                small_asteroids[a].speed.y *= -1;
                small_asteroids[a].position.y += small_asteroids[a].speed.y;
            }
            else if ((player.speed.y >= 0 and small_asteroids[a].speed.y >= 0) or (player.speed.y <= 0 and small_asteroids[a].speed.y <= 0)) {
                if (abs(player.speed.y) >= abs(small_asteroids[a].speed.y)) {
                    player.speed.y *= -1;
                }
                else {
                    small_asteroids[a].speed.y *= -1;
                    small_asteroids[a].position.y += small_asteroids[a].speed.y;
                }
            }
            player.block = true;
            player.health -= 10;
        }
    }
}

bool Game::Chek_Enemy() {
    for (int i = 0; i < 10; ++i) {
        if (sq_enemies[i].active == true) {
            return true;
        }
        if (i == 9) {
            for (int j = 0; j < 10; ++j) {
                if (d_sq_enemies[j].active == true) {
                    return true;
                }
                if (j == 9) {
                    return false;
                }
            }
        }
    }
}

void Game::Collision_Enemy() {
    Vector3 collider1 = { player.position.x + sin(player.rotation * DEG2RAD) * (20 / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (20 / 2.5f), 12 };
    Vector3 collider2 = { player.position.x - sin(player.rotation * DEG2RAD) * (20 / 2.5f), player.position.y + cos(player.rotation * DEG2RAD) * (20 / 2.5f), 6 };
    for (int i = 0; i < player.max_bullets; ++i) {
        if (player.bullets[i].active == true) {
            for (int j = 0; j < 10; ++j) {
                Rectangle sq_enemy = { sq_enemies[j].position.x, sq_enemies[j].position.y, sq_enemies[j].size, sq_enemies[j].size };
                if (CheckCollisionCircleRec(player.bullets[i].position, player.bullets[i].radius, sq_enemy) and sq_enemies[j].active == true) {
                    player.bullets[i].active = false;
                    sq_enemies[j].health -= player.bullets[i].damage;
                }
            }
        }
    }
    for (int i = 0; i < player.max_bullets; ++i) {
        if (player.bullets[i].active == true) {
            for (int j = 0; j < 10; ++j) {
                Rectangle d_sq_enemy = { d_sq_enemies[j].position.x, d_sq_enemies[j].position.y, d_sq_enemies[j].size, d_sq_enemies[j].size };
                if (CheckCollisionCircleRec(player.bullets[i].position, player.bullets[i].radius, d_sq_enemy) and d_sq_enemies[j].active == true) {
                    player.bullets[i].active = false;
                    d_sq_enemies[j].health -= player.bullets[i].damage;
                }
            }
        }
    }
    for (int i = 0; i < max_small_asteroids; ++i) {
        for (int j = 0; j < 10; ++j) {
            Rectangle sq_enemy = { sq_enemies[j].position.x, sq_enemies[j].position.y, sq_enemies[j].size, sq_enemies[j].size };
            if (CheckCollisionCircleRec(small_asteroids[i].position, small_asteroids[i].radius, sq_enemy)) {
                sq_enemies[j].speed.x *= -1;
                sq_enemies[j].position.x += sq_enemies[j].speed.x;
                sq_enemies[j].speed.y *= -1;
                sq_enemies[j].position.y += sq_enemies[j].speed.y;
                sq_enemies[j].block = true;
                sq_enemies[j].timer = clock();
            }
        }
    }
    for (int i = 0; i < max_medium_asteroids; ++i) {
        for (int j = 0; j < 10; ++j) {
            Rectangle sq_enemy = { sq_enemies[j].position.x, sq_enemies[j].position.y, sq_enemies[j].size, sq_enemies[j].size };
            if (CheckCollisionCircleRec(medium_asteroids[i].position, medium_asteroids[i].radius, sq_enemy)) {
                sq_enemies[j].speed.x *= -1;
                sq_enemies[j].position.x += sq_enemies[j].speed.x;
                sq_enemies[j].speed.y *= -1;
                sq_enemies[j].position.y += sq_enemies[j].speed.y;
                sq_enemies[j].block = true;
                sq_enemies[j].timer = clock();
            }
        }
    }
    for (int i = 0; i < max_big_asteroids; ++i) {
        for (int j = 0; j < 10; ++j) {
            Rectangle sq_enemy = { sq_enemies[j].position.x, sq_enemies[j].position.y, sq_enemies[j].size, sq_enemies[j].size };
            if (CheckCollisionCircleRec(big_asteroids[i].position, big_asteroids[i].radius, sq_enemy)) {
                sq_enemies[j].speed.x *= -1;
                sq_enemies[j].position.x += sq_enemies[j].speed.x;
                sq_enemies[j].speed.y *= -1;
                sq_enemies[j].position.y += sq_enemies[j].speed.y;
                sq_enemies[j].block = true;
                sq_enemies[j].timer = clock();
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        if (CheckCollisionCircles({ collider1.x, collider1.y }, collider1.z, { sq_enemies[i].position.x + sq_enemies[i].size / 2, sq_enemies[i].position.y + sq_enemies[i].size / 2}, sq_enemies[i].size / 2) and sq_enemies[i].active == true) {
            player.speed.x *= -1;
            player.position.x += (player.speed.x + sq_enemies[i].speed.x * 2);
            player.speed.y *= -1;
            player.position.y += (player.speed.y + sq_enemies[i].speed.y * 2);
            player.block = true;
            if (sq_enemies[i].block == false and sq_enemies[i].a_block == false) {
                sq_enemies[i].speed.x *= -1;
                sq_enemies[i].speed.y *= -1;
            }
            sq_enemies[i].block = true;
            sq_enemies[i].timer = clock();
            player.health -= 10;
            sq_enemies[i].health -= 5;
        }
    }

    for (int i = 0; i < max_small_asteroids; ++i) {
        for (int j = 0; j < 10; ++j) {
            Rectangle d_sq_enemy = { d_sq_enemies[j].position.x, d_sq_enemies[j].position.y, d_sq_enemies[j].size, d_sq_enemies[j].size };
            if (CheckCollisionCircleRec(small_asteroids[i].position, small_asteroids[i].radius, d_sq_enemy)) {
                d_sq_enemies[j].speed.x *= -1;
                d_sq_enemies[j].position.x += sq_enemies[j].speed.x;
                d_sq_enemies[j].speed.y *= -1;
                d_sq_enemies[j].position.y += sq_enemies[j].speed.y;
                d_sq_enemies[j].block = true;
                d_sq_enemies[j].timer = clock();
            }
        }
    }
    for (int i = 0; i < max_medium_asteroids; ++i) {
        for (int j = 0; j < 10; ++j) {
            Rectangle d_sq_enemy = { d_sq_enemies[j].position.x, d_sq_enemies[j].position.y, d_sq_enemies[j].size, d_sq_enemies[j].size };
            if (CheckCollisionCircleRec(medium_asteroids[i].position, medium_asteroids[i].radius, d_sq_enemy)) {
                d_sq_enemies[j].speed.x *= -1;
                d_sq_enemies[j].position.x += sq_enemies[j].speed.x;
                d_sq_enemies[j].speed.y *= -1;
                d_sq_enemies[j].position.y += sq_enemies[j].speed.y;
                d_sq_enemies[j].block = true;
                d_sq_enemies[j].timer = clock();
            }
        }
    }
    for (int i = 0; i < max_big_asteroids; ++i) {
        for (int j = 0; j < 10; ++j) {
            Rectangle d_sq_enemy = { d_sq_enemies[j].position.x, d_sq_enemies[j].position.y, d_sq_enemies[j].size, d_sq_enemies[j].size };
            if (CheckCollisionCircleRec(big_asteroids[i].position, big_asteroids[i].radius, d_sq_enemy)) {
                d_sq_enemies[j].speed.x *= -1;
                d_sq_enemies[j].position.x += sq_enemies[j].speed.x;
                d_sq_enemies[j].speed.y *= -1;
                d_sq_enemies[j].position.y += sq_enemies[j].speed.y;
                d_sq_enemies[j].block = true;
                d_sq_enemies[j].timer = clock();
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        if (CheckCollisionCircles({ collider1.x, collider1.y }, collider1.z, { d_sq_enemies[i].position.x + d_sq_enemies[i].size / 2, d_sq_enemies[i].position.y + d_sq_enemies[i].size / 2 }, d_sq_enemies[i].size / 2) and d_sq_enemies[i].active == true) {
            player.speed.x *= -1;
            player.position.x += (player.speed.x + sq_enemies[i].speed.x * 2);
            player.speed.y *= -1;
            player.position.y += (player.speed.y + sq_enemies[i].speed.y * 2);
            player.block = true;
            if (d_sq_enemies[i].block == false) {
                d_sq_enemies[i].speed.x *= -1;
                d_sq_enemies[i].speed.y *= -1;
            }
            d_sq_enemies[i].block = true;
            d_sq_enemies[i].timer = clock();
            player.health -= 10;
            d_sq_enemies[i].health -= 5;
        }
    }
}

void Game::Level(int level) {
    if (level == 1) {
        if (preparation == false) {
            for (int i = 0; i < 3; ++i) {
                sq_enemies[i].Reset();
            }
            d_sq_enemies[0].Reset();
            sq_enemies[0].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 - 200 };
            sq_enemies[1].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 };
            sq_enemies[2].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 + 200 };
            d_sq_enemies[0].position = { -45, float(GetScreenHeight()) / 2 };
            preparation = true;
        }
        if (preparation == true) {
            Collision_Enemy();
            for (int i = 0; i < 3; ++i) {
                if (sq_enemies[i].active == true) {
                    sq_enemies[i].Update(player);
                }
            }
            if (d_sq_enemies[0].active == true) {
                d_sq_enemies[0].Update(player);
                d_sq_enemies[0].Shoot();
                d_sq_enemies[0].UpdateRoket(player);
            }
        }
    }
    else if (level == 2) {
        if (preparation == false) {
            for (int i = 0; i < 4; ++i) {
                sq_enemies[i].Reset();
            }
            for (int i = 0; i < 2; ++i) {
                d_sq_enemies[i].Reset();
            }

            sq_enemies[0].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 - 200 };
            sq_enemies[1].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 };
            sq_enemies[2].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 + 200 };
            sq_enemies[3].position = { -45,float(GetScreenHeight()) / 2 };
            d_sq_enemies[0].position = { -45,float(GetScreenHeight()) / 2 - 200 };
            d_sq_enemies[1].position = { -45,float(GetScreenHeight()) / 2 + 200 };
            
            preparation = true;
        }
        if (preparation == true) {
            Collision_Enemy();
            for (int i = 0; i < 4; ++i) {
                if (sq_enemies[i].active == true) {
                    sq_enemies[i].Update(player);
                }
            }
            for (int i = 0; i < 2; ++i) {
                if (d_sq_enemies[i].active == true) {
                    d_sq_enemies[i].Update(player);
                    d_sq_enemies[i].Shoot();
                    d_sq_enemies[i].UpdateRoket(player);
                }
            }
        }
    }
    else if (level == 3) {
        if (preparation == false) {
            for (int i = 0; i < 6; ++i) {
                sq_enemies[i].Reset();
            }
            for (int i = 0; i < 4; ++i) {
                d_sq_enemies[i].Reset();
            }

            sq_enemies[0].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 - 200 };
            sq_enemies[1].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 };
            sq_enemies[2].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 + 200 };
            sq_enemies[3].position = { -45,float(GetScreenHeight()) / 2 - 200 };
            sq_enemies[4].position = { -45,float(GetScreenHeight()) / 2 };
            sq_enemies[5].position = { -45,float(GetScreenHeight()) / 2 + 200 };
            d_sq_enemies[0].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 - 400 };
            d_sq_enemies[1].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 + 400 };
            d_sq_enemies[2].position = { -45,float(GetScreenHeight()) / 2 - 400 };
            d_sq_enemies[3].position = { -45,float(GetScreenHeight()) / 2 + 400 };
            
            preparation = true;
        }
        if (preparation == true) {
            Collision_Enemy();
            for (int i = 0; i < 6; ++i) {
                if (sq_enemies[i].active == true) {
                    sq_enemies[i].Update(player);
                }
            }
            for (int i = 0; i < 4; ++i) {
                if (d_sq_enemies[i].active == true) {
                    d_sq_enemies[i].Update(player);
                    d_sq_enemies[i].Shoot();
                    d_sq_enemies[i].UpdateRoket(player);
                }
            }
        }
    }
    else if (level == 4) {
        if (preparation == false) {
            for (int i = 0; i < 8; ++i) {
                sq_enemies[i].Reset();
            }
            for (int i = 0; i < 8; ++i) {
                d_sq_enemies[i].Reset();
            }

            sq_enemies[0].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 - 200 };
            sq_enemies[1].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 };
            sq_enemies[2].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 + 200 };
            sq_enemies[3].position = { -45,float(GetScreenHeight()) / 2 - 200 };
            sq_enemies[4].position = { -45,float(GetScreenHeight()) / 2 };
            sq_enemies[5].position = { -45,float(GetScreenHeight()) / 2 + 200 };
            sq_enemies[6].position = { float(GetScreenWidth()) / 2, -45 };
            sq_enemies[7].position = { float(GetScreenWidth()) / 2, float(GetScreenHeight()) + 45 };
            d_sq_enemies[0].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 - 400 };
            d_sq_enemies[1].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 + 400 };
            d_sq_enemies[2].position = { -45,float(GetScreenHeight()) / 2 - 400 };
            d_sq_enemies[3].position = { -45,float(GetScreenHeight()) / 2 + 400 };
            d_sq_enemies[4].position = { float(GetScreenWidth()) / 2 - 200, -45 };
            d_sq_enemies[5].position = { float(GetScreenWidth()) / 2 + 200, -45 };
            d_sq_enemies[6].position = { float(GetScreenWidth()) / 2 - 200, float(GetScreenHeight()) + 45 };
            d_sq_enemies[7].position = { float(GetScreenWidth()) / 2 + 200, float(GetScreenHeight()) + 45 };

            preparation = true;
        }
        if (preparation == true) {
            Collision_Enemy();
            for (int i = 0; i < 8; ++i) {
                if (sq_enemies[i].active == true) {
                    sq_enemies[i].Update(player);
                }
            }
            for (int i = 0; i < 8; ++i) {
                if (d_sq_enemies[i].active == true) {
                    d_sq_enemies[i].Update(player);
                    d_sq_enemies[i].Shoot();
                    d_sq_enemies[i].UpdateRoket(player);
                }
            }
        }
    }
    else if (level == 5) {
        if (preparation == false) {
            for (int i = 0; i < 8; ++i) {
                sq_enemies[i].Reset();
            }
            for (int i = 0; i < 8; ++i) {
                d_sq_enemies[i].Reset();
            }

            sq_enemies[0].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 - 200 };
            sq_enemies[1].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 };
            sq_enemies[2].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 + 200 };
            sq_enemies[3].position = { -45,float(GetScreenHeight()) / 2 - 200 };
            sq_enemies[4].position = { -45,float(GetScreenHeight()) / 2 };
            sq_enemies[5].position = { -45,float(GetScreenHeight()) / 2 + 200 };
            sq_enemies[6].position = { float(GetScreenWidth()) / 2, -45 };
            sq_enemies[7].position = { float(GetScreenWidth()) / 2, float(GetScreenHeight()) + 45 };
            sq_enemies[8].position = { float(GetScreenWidth()) / 2 - 400, -45 };
            sq_enemies[9].position = { float(GetScreenWidth()) / 2 + 400, float(GetScreenHeight()) + 45 };
            d_sq_enemies[0].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 - 400 };
            d_sq_enemies[1].position = { float(GetScreenWidth()) + 45,float(GetScreenHeight()) / 2 + 400 };
            d_sq_enemies[2].position = { -45,float(GetScreenHeight()) / 2 - 400 };
            d_sq_enemies[3].position = { -45,float(GetScreenHeight()) / 2 + 400 };
            d_sq_enemies[4].position = { float(GetScreenWidth()) / 2 - 200, -45 };
            d_sq_enemies[5].position = { float(GetScreenWidth()) / 2 + 200, -45 };
            d_sq_enemies[6].position = { float(GetScreenWidth()) / 2 - 200, float(GetScreenHeight()) + 45 };
            d_sq_enemies[7].position = { float(GetScreenWidth()) / 2 + 200, float(GetScreenHeight()) + 45 };
            d_sq_enemies[8].position = { float(GetScreenWidth()) / 2 + 400, -45 };
            d_sq_enemies[9].position = { float(GetScreenWidth()) / 2 - 400, float(GetScreenHeight()) + 45 };

            preparation = true;
        }
        if (preparation == true) {
            Collision_Enemy();
            for (int i = 0; i < 10; ++i) {
                if (sq_enemies[i].active == true) {
                    sq_enemies[i].Update(player);
                }
            }
            for (int i = 0; i < 10; ++i) {
                if (d_sq_enemies[i].active == true) {
                    d_sq_enemies[i].Update(player);
                    d_sq_enemies[i].Shoot();
                    d_sq_enemies[i].UpdateRoket(player);
                }
            }
        }
    }
    else {
        win = true;
    }
}

void Game::Reset(int max_big_asteroids, int max_medium_asteroids, int max_small_asteroids) {
    this->max_big_asteroids = max_big_asteroids;
    this->max_medium_asteroids = max_medium_asteroids;
    this->max_small_asteroids = max_small_asteroids;
    player = Player();
    sq_enemies[10];
    d_sq_enemies[10];
    big_asteroids[max_big_asteroids];
    medium_asteroids[max_medium_asteroids];
    small_asteroids[max_small_asteroids];
    preparation = false;
    level = 1;
    for (int i = 0; i < max_big_asteroids; ++i) {
        big_asteroids[i] = Asteroid();
    }
    for (int i = 0; i < max_medium_asteroids; ++i) {
        medium_asteroids[i] = Asteroid();
    }
    for (int i = 0; i < max_small_asteroids; ++i) {
        small_asteroids[i] = Asteroid();
    }
    for (int i = 0; i < 10; ++i) {
        sq_enemies[i] = Square_enemy();
    }
    for (int i = 0; i < 10; ++i) {
        d_sq_enemies[i] = Double_square_enemy();
    }
}
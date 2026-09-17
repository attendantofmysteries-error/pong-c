#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "rectangle.h"
#include "circle.h"
#include "globals.h"
#include "game.h"

int32 main() {
  game_t game;
  game_init(&game, (Vector2){100, 100}, (Vector2){800, 600});

  rectangle_t player;
  rectangle_t enemy;
  rectangle_init(&player, (Vector2){40, 250}, 20, 100);
  rectangle_init(&enemy, (Vector2){740, 250}, 20, 100);
  boolean was_colliding_player = false;
  boolean was_colliding_enemy = false;
  float32 player_speed = 10.0f; 
  float32 enemy_speed = 4.0f;

  circle_t ball;
  circle_init(&ball, (Vector2){game.window_size.x / 2, game.window_size.y / 2}, 10);

  Vector2 ball_start_direction = {GetRandomValue(0, 1) ? 1 : -1, GetRandomValue(0, 1) ? 1 : -1};

  float32 ball_speed = 250.0f;

  int32 hit_count = 0;

  boolean game_over = false;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (!game.match_over) {
      game_update(&game);
      circle_update(&ball,
        (Vector2){
          ball.position.x + (ball_start_direction.x * ball_speed * game.delta_time), 
          ball.position.y + (ball_start_direction.y * ball_speed * game.delta_time)});
      // Ball collision with window borders
      if (ball.position.y <= 0 || ball.position.y >= game.window_size.y) {
        ball_start_direction.y *= -1;
      }
      if (ball.position.x <= 0 || ball.position.x >= game.window_size.x) {
        ball_start_direction.x *= -1;
      }
      // Ball collision with paddles

      boolean colliding_player = CheckCollisionCircleRec(ball.position, ball.radius,
          (Rectangle){player.position.x, player.position.y, player.width, player.height});

      if (colliding_player && !was_colliding_player) {
        ball_start_direction.x = fabsf(ball_start_direction.x);

        ball_start_direction.y = GetRandomValue(0, 1) ? 1 : -1;

        hit_count++;
      }
      was_colliding_player = colliding_player;

      boolean colliding_enemy = CheckCollisionCircleRec(ball.position, ball.radius,
        (Rectangle){enemy.position.x, enemy.position.y, enemy.width, enemy.height});

      if (colliding_enemy && !was_colliding_enemy) {
        ball_start_direction.x = fabsf(ball_start_direction.x) * -1;

        ball_start_direction.y *= GetRandomValue(0, 1) ? 1 : -1;

        hit_count++;
      }
      was_colliding_enemy = colliding_enemy;
      // Player movement
      if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        rectangle_update(&player, (Vector2){player.position.x, player.position.y - player_speed});
      }
      if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        rectangle_update(&player, (Vector2){player.position.x, player.position.y + player_speed});
      }

      // Enemy movement
      if (ball.position.y < enemy.position.y) {
        rectangle_update(&enemy, (Vector2){enemy.position.x, enemy.position.y - enemy_speed});
      }
      if (ball.position.y > enemy.position.y) {
        rectangle_update(&enemy, (Vector2){enemy.position.x, enemy.position.y + enemy_speed});
      }
      // Paddle collision with window borders
      if (enemy.position.y < 0) {
        rectangle_update(&enemy, (Vector2){enemy.position.x, 0});
      }
      if (enemy.position.y + enemy.height > game.window_size.y) {
        rectangle_update(&enemy, (Vector2){enemy.position.x, game.window_size.y - enemy.height});
      }
      if (player.position.y < 0) {
        rectangle_update(&player, (Vector2){player.position.x, 0});
      }
      if (player.position.y + player.height > game.window_size.y) {
        rectangle_update(&player, (Vector2){player.position.x, game.window_size.y - player.height});
      }

      // Reset ball and paddles if the ball goes out of bounds
      
      if (hit_count >= 3) {
        ball_speed += 50.0f;

        hit_count = 0;

        enemy_speed += 1.0f;

        Clamp(enemy_speed, 4.0f, 12.0f);
      }

      if (ball.position.x < player.position.x + player.width) {
        game.enemy_score++;
        // Reset ball position and direction
        circle_update(&ball, (Vector2){game.window_size.x / 2, game.window_size.y / 2});

        ball_start_direction.x = GetRandomValue(0, 1) ? 1 : -1;
        ball_start_direction.y = GetRandomValue(0, 1) ? 1 : -1;

        rectangle_update(&player, (Vector2){40, 250});
        rectangle_update(&enemy, (Vector2){740, 250});

        ball_speed = 250.0f; // Reset ball speed to initial value

      } else if (ball.position.x > enemy.position.x + enemy.width) {
        game.player_score++;

        // Reset ball position and direction
        circle_update(&ball, (Vector2){game.window_size.x / 2, game.window_size.y / 2});

        ball_start_direction.x = GetRandomValue(0, 1) ? 1 : -1;
        ball_start_direction.y = GetRandomValue(0, 1) ? 1 : -1;

        rectangle_update(&player, (Vector2){40, 250});
        rectangle_update(&enemy, (Vector2){740, 250});

        ball_speed = 250.0f; // Reset ball speed to initial value
      }
      if (game.player_score >= 2 || game.enemy_score >= 2) {
        game.match_over = true;
      }

      rectangle_draw(&player);
      rectangle_draw(&enemy);

      circle_draw(&ball);

      DrawText(TextFormat("Player: %d", game.player_score), 10, 10, 20, WHITE);
      DrawText(TextFormat("Enemy: %d", game.enemy_score), game.window_size.x - 120, 10, 20, WHITE);
    } else {
      on_match_over(&game);
    }
    if (game.game_over) {
      break;
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
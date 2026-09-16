#include "game.h"


void game_init(game_t *game, Vector2 window_position, Vector2 window_size) {
  game->window_position = window_position;
  game->window_size = window_size;
  game->player_score = 0;
  game->enemy_score = 0;
  game->match_over = false;
  game->game_over = false;

  InitWindow((int)window_size.x, (int)window_size.y, "Pong");
  SetWindowPosition((int)window_position.x, (int)window_position.y);
  SetWindowState(FLAG_WINDOW_RESIZABLE); // Allow window resizing
  SetTargetFPS(60);
}

void game_update(game_t *game) {
  game->delta_time = GetFrameTime();
}

void on_game_over(game_t *game) {
  if (game->player_score > game->enemy_score) {
    DrawText("Game Over! You win!", game->window_size.x / 2 - 200, (game->window_size.y / 2) - 100, 40, GREEN);
    DrawText("Do you want to play a new game [Y/N]", (game->window_size.x / 2) - 300, game->window_size.y / 2, 40, WHITE);
  } else {
    DrawText("Game Over! You lose!", game->window_size.x / 2 - 200, (game->window_size.y / 2) - 100, 40, RED);
    DrawText("Do you want to restart [Y/N]", (game->window_size.x / 2) - 285, game->window_size.y / 2, 40, WHITE);
  }
  if (IsKeyPressed(KEY_Y)) {
    game->match_over = false;
  } else if (IsKeyPressed(KEY_N)) {
    game->game_over = true;
  }
}
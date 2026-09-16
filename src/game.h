#pragma once

#include "globals.h"

#include <raylib.h>

typedef struct game {
  Vector2 window_position;
  Vector2 window_size;
  int32   player_score;
  int32   enemy_score;
  boolean match_over;
  boolean game_over;
  float32 delta_time;
} game_t;

void game_init(game_t* game, Vector2 window_position, Vector2 window_size);
void game_update(game_t* game);
void on_game_over(game_t* game);

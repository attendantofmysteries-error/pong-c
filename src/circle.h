#pragma once
#include "globals.h"
#include <raylib.h>


typedef struct circle {
  Vector2 position;
  float32 radius;
} circle_t;

void circle_init(circle_t *c, Vector2 position, float radius);
void circle_update(circle_t *c, Vector2 newPosition);
void circle_draw(circle_t *c);
#pragma once
#include "globals.h"
#include <raylib.h>


typedef struct rectangle {
  Vector2 position;
  float32 width;
  float32 height;
} rectangle_t;

void rectangle_init(rectangle_t *rect, Vector2 position, float32 width, float32 height);
void rectangle_update(rectangle_t *rect, Vector2 newPosition);
void rectangle_draw(rectangle_t *rect);

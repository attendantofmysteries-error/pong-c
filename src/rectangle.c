#include "rectangle.h"

void rectangle_init(rectangle_t *rect, Vector2 position, float32 width, float32 height) {
  rect->position = position;
  rect->width = width;
  rect->height = height;
}

void rectangle_update(rectangle_t *rect, Vector2 newPosition) {
  rect->position = newPosition;
}

void rectangle_draw(rectangle_t *rect) {
  DrawRectangle(rect->position.x, rect->position.y, rect->width, rect->height, WHITE);
}
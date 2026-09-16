#include "circle.h"

void circle_init(circle_t *c, Vector2 position, float32 radius) {
  c->position = position;
  c->radius = radius;
}

void circle_update(circle_t *c, Vector2 newPosition) {
  c->position = newPosition;
}

void circle_draw(circle_t *c) {
  DrawCircle(c->position.x, c->position.y, c->radius, WHITE);
}
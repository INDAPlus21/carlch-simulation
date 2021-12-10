#include "grid.h"

Square* 
SquareCreate(int size, int diff, int visc, float dt) {
  Square* s = malloc(sizeof(*s));
  int N = size;

  s->size = size;
  s->dt = dt;
  s->diff = diff;
  s->visc = visc;

  s->s = calloc(N * N, sizeof(float));
  s->density = calloc(N * N, sizeof(float));

  s->vx = calloc(N * N, sizeof(float));
  s->vx0 = calloc(N * N, sizeof(float));

  s->vy = calloc(N * N, sizeof(float));
  s->vy0 = calloc(N * N, sizeof(float));

  return s;
}

void 
SquareFree(Square* s) {
  free(s->s);
  free(s->density);
  free(s->vx);
  free(s->vx0);
  free(s->vy);
  free(s->vy0);
  free(s);
}

void 
SquareAddDensity(Square *s, int x, int y, float amount) {
  int N = s->size;
  s->density[IDX(x, y)] += amount;
}

void 
SquareAddVelocity(Square *s, int x, int y, float amountX, float amountY) {
  int N = s->size;
  int idx = IDX(x, y);

  s->vx[idx] += amountX;
  s->vy[idx] += amountY;
}

void
renderD(Square* s, SDL_Renderer* gRenderer) {
  int N = s->size;
  for(int j = 0; j < N; j++)
    for(int i = 0; i < N; i++) {
      float x = i * 1;
      float y = j * 1;
      uint8_t d = s->density[IDX(i, j)];
      // SDL_Rect fillRect = { 480 / N, 480 / N, i * (480 / N), j * (480 / N)};
      SDL_Rect fillRect = {480, 480, 0, 0};
      SDL_SetRenderDrawColor(gRenderer, d, d, d, 0x00);
      SDL_RenderFillRect(gRenderer, &fillRect);
    }
}
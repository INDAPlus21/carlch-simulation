#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Represent 2D array as a single array.
#define IDX(x, y) ((x) + (N * y))
#define SIZE 5


typedef struct Square {
  int size;
  float dt, diff, visc;
  float *s, *density;
  float *vx, *vx0, *vy, *vy0;
} Square;

// Create square.
Square* SquareCreate(int size, int diff, int visc, float dt);

// Free allocated memory.
void SquareFree(Square* s);

// Increase density in square.
void SquareAddDensity(Square *s, int x, int y, float amount);

// Increase velocity and direction in square.
void SquareAddVelocity(Square *s, int x, int y, float amountX, float amountY);

void renderD();

#endif
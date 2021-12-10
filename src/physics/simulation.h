#ifndef SIM_H
#define SIM_H

#include "grid.h"
#include <math.h>

#define DIFFUSE 0.5f

// Do it all baby.
void nextStep(Square* sq);

// Set boundry cells to limit size of simulation.
void setBond(int b, float* x, int N);

// Solve linear equations.
void linearSolve(int b, float* x, float* x0, float a, float c, int iter, int N);

// Simulate diffusion.
void diffuse(int b, float* x, float* x0, float diff, float dt, int iter, int N);

// 
void project(float* vX, float* vY, float* p, float* div, int iter, int N);

// Check where particles are and are going to be.
void advect(int b, float* d, float* d0, float* vX, float* vY, float dt, int N);
#endif
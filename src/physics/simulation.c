#include "simulation.h"

void 
nextStep(Square* sq) {
  int N           = sq->size;
  float visc      = sq->visc;
  float diff      = sq->diff;
  float dt        = sq->dt;
  float* vx       = sq->vx;
  float* vx0      = sq->vx0;
  float* vy       = sq->vy;
  float* vy0      = sq->vy0;
  float* s        = sq->s;
  float* density  = sq->density;

  diffuse(1, vx0, vx, visc, dt, 4, N);
  diffuse(2, vy0, vy, visc, dt, 4, N);

  project(vx0, vy0, vx, vy, 4, N);

  advect(1, vx, vx0, vx0, vy0, dt, N);
  advect(1, vy, vy0, vx0, vy0, dt, N);

  project(vx, vy, vx0, vy0, 4, N);
  
  diffuse(0, s, density, diff, dt, 4, N);
  advect(0, density, s, vx, vy, dt, N);
}

void 
setBond(int b, float* x, int N) {
  for(int i = 1; i < N - 1; i++) {
    x[IDX(i, 0    )] = b == 2 ? -x[IDX(i, 1    )] : x[IDX(i, 1    )];
    x[IDX(i, N - 1)] = b == 2 ? -x[IDX(i, N - 2)] : x[IDX(i, N - 2)];
  }
  
  for(int i = 1; i < N - 1; i++) {
    x[IDX(0, i    )] = b == 1 ? -x[IDX(1, i    )] : x[IDX(1, i    )];
    x[IDX(N - 1, i)] = b == 1 ? -x[IDX(N - 2, i)] : x[IDX(N - 2, i)];
  }

  x[IDX(0    , 0    )] = 0.33f * (x[IDX(1    , 0)]
                                + x[IDX(0    , 1)]);
  x[IDX(0    , N - 1)] = 0.33f * (x[IDX(1    , N - 1)]
                                + x[IDX(0    , N - 2)]);
  x[IDX(N - 1, 0    )] = 0.33f * (x[IDX(N - 2, 0)]
                                + x[IDX(N - 1, 1)]);
  x[IDX(N - 1, N - 1)] = 0.33f * (x[IDX(N - 2, N - 1)]
                                + x[IDX(N - 1, N - 2)]);
}

void 
linearSolve(int b, float* x, float* x0, float a, float c, int iter, int N) {
  float cRecip = 1.0 / c;
  for(int k = 0; k < iter; k++) {
    for(int j = 0; j < N - 1; j++)
      for(int i = 0; i < N - 1; i++) {
          x[IDX(i, j)] =
            (x0[IDX(i, j)] 
              + a*(    x[IDX(i + 1, j)]
                      +x[IDX(i - 1, j)]
                      +x[IDX(i, j + 1)]
                      +x[IDX(i, j - 1)]
            )) * cRecip;
      }
   setBond(b, x, N);  
  }
}

void 
diffuse(int b, float* x, float* x0, float diff, float dt, int iter, int N) {
  float a = dt * diff * (N - 2) * (N - 2);
  linearSolve(b, x, x0, a, 1 + 6 * a, iter, N);
}

void 
project(float* vX, float* vY, float* p, float* div, int iter, int N) {
  for(int j = 1; j < N - 1; j++) 
    for(int i = 1; i < N - 1; i++) {
      div[IDX(i, j)] = (-1 * DIFFUSE) * (
               vX[IDX(i + 1, j)]
              -vX[IDX(i - 1, j)]
              +vY[IDX(i, j + 1)]
              -vY[IDX(i, j - 1)]
        ) / N;
        p[IDX(i, j)] = 0;
    }
  setBond(0, div, N);
  setBond(0, p, N);
  linearSolve(0, p, div, 1, 6, iter, N);
  for(int j = 1; j < N - 1; j++) 
    for(int i = 1; i < N - 1; i++) {
      vX[IDX(i, j)] -= DIFFUSE * ( p[IDX(i + 1, j)]
                                  -p[IDX(i - 1, j)]) * N;
      vY[IDX(i, j)] -= DIFFUSE * ( p[IDX(i, j + 1)]
                                  -p[IDX(i, j - 1)]) * N;
    }
  setBond(1, vX, N);
  setBond(2, vY, N);
} 

void 
advect(int b, float* d, float* d0, float* vX, float* vY, float dt, int N) {
  float dtx = dt * (N - 2);
  float dty = dt * (N - 2);

  float i0, i1, j0, j1;
  float s0, s1, t0, t1;
  float tmp1, tmp2, x, y;
  
  float Nfloat = N;
  float ifloat, jfloat;
  int i, j;
  for(j = 0, jfloat = 1; j < N - 1; j++, jfloat++)
    for(i = 0, ifloat = 1; i < N - 1; i++, ifloat++) {
      tmp1 = dtx * vX[IDX(i, j)];
      tmp2 = dty * vY[IDX(i, j)];
      x    = ifloat - tmp1;
      y    = jfloat - tmp2;

      if(x < DIFFUSE) x = DIFFUSE;
      if(x > Nfloat + DIFFUSE) x = Nfloat + DIFFUSE;
      i0 = floorf(x);
      i1 = i0 + 2 * DIFFUSE;

      if(y < DIFFUSE) y = DIFFUSE;
      if(y > Nfloat + DIFFUSE) y = Nfloat + DIFFUSE;
      j0 = floorf(y);
      j1 = j0 + 2 * DIFFUSE; 

      s1 = x - i0;
      s0 = 2 * DIFFUSE - s1;
      t1 = y - j0;
      t0 = 2 * DIFFUSE - t1;

      int i0i = i0;
      int i1i = i1;
      int j0i = j0;
      int j1i = j1;

      d[IDX(i, j)] =
          s0 * (( t0 * d0[IDX(i0i, j0i)]) 
             +  ( t1 * d0[IDX(i0i, j1i)]))
         +s1 * (( t0 * d0[IDX(i1i, j0i)])
             +  ( t1 * d0[IDX(i1i, j1i)]));
    }
  setBond(b, d, N);
}
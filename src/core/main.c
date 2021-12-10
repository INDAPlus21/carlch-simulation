// Written by the spaghetti monster rawr
// Compile using:
// gcc main.c -I/Library/Frameworks/SDL2.framework/Header -F/Library/Frameworks -framework SDL2 -I/Library/Frameworks/SDL2

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../physics/grid.h"
#include "../physics/simulation.h"

#define SCREENTITLE "Rawr owo nuzzles your xd"

int
main() {
  Square* sq = SquareCreate(120, 1, 1, 16);

  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialize SDL2 livrary!\n");
    return -1;
  } 

  SDL_Window *window = SDL_CreateWindow(SCREENTITLE,
                                        0, 0,
                                        480, 480, 0);
  if(!window) {
    printf("Failed to create window!\n");
    return -1;
  }
  SDL_Renderer *gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_UpdateWindowSurface(window);
  SDL_Event e;
  int isQuit = 0;
  int x, y, px, py;
  int buttons;
  int N = sq->size;
  while(!isQuit) {
    if(SDL_PollEvent(&e) != 0)
      if(e.type == SDL_QUIT) isQuit = 1;
      
      buttons = SDL_GetMouseState(&x, &y);
      int ax = x * 480/N;
      int ay = y * 480/N;
      SquareAddDensity(sq, ax, ay, 2.0f);
      SquareAddVelocity(sq, x, y, x - px, y - py);
      px = x;
      py = y;

      printf("x : %d, y : %d, density : %3.2f\n", x, y, sq->density[IDX(ax, ay)]);

      nextStep(sq);
      renderD(sq, gRenderer);
      SDL_RenderPresent(gRenderer);

      long yar = 0;
      while(yar != 100000) {
        yar++;
      }
  }
  SDL_DestroyWindow(window);
  SquareFree(sq);
  SDL_Quit();
}

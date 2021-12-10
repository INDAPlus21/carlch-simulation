#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 5
#define ALIVE 1
#define DEAD 0

#define LENGTH SIZE * SIZE
#define X_FOR for(int x = 0; x < SIZE; x++)
#define Y_FOR for(int y = 0; y < SIZE; y++)
#define XY_FOR X_FOR Y_FOR
#define FOR_ARR for(int i = 0; i < LENGTH; i++)
#define ID(x, y) (x + SIZE * y)

void
printArray(int* a) {
  fputc('\n', stdout);
  for(int y = 0; y < SIZE; y++) {
    X_FOR printf("%d ", a[x + SIZE * y]);
    fputc('\n', stdout);
  }
}

void
evolve(int* a) {
  int x, y, i, j, n, index, neighbour;
  int* r = calloc(LENGTH * sizeof(int), LENGTH);
  XY_FOR {
    index = ID(x, y);
    n = 0;
    for(i = x - 1; i <= x + 1; i++) 
    for(j = y - 1; j <= y + 1; j++) {
      neighbour = ID(i, j); 
      if(x % 5 == 0 && i == x - 1) continue;
      if(x % 5 == 4 && i == x + 1) continue;
      if((i == x && j == y) || a[neighbour] == DEAD) continue;
      n++;
    }
    if(n == 3 || (n == 2 && a[index] == 1)) r[index] = ALIVE;
    else if(n > 3 && a[index] == 1) r[index] = DEAD;
  }
  FOR_ARR a[i] = r[i];
  free(r);
}

int 
main(){
    int* c;
    long long unsigned step = 0;
    c = malloc(LENGTH * sizeof(int));
    FOR_ARR c[i] = rand() % 2;

    while(1) {
      system("clear");
      printf("Array of step %llu\n", step);
      printArray(c);
      evolve(c);
      step++;
      sleep(1);
    }
    return 0;
}

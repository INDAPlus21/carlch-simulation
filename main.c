#include <stdio.h>
#include <stdlib.h>

#define X_FOR for(int x = 0; x < COL; x++)
#define Y_FOR for(int y = 0; y < ROW; y++)
#define XY_FOR X_FOR Y_FOR
#define YX_FOR Y_FOR X_FOR
#define ID(x, y) (x + COL * y);


#define ROW 5
#define COL 5
#define ALIVE 1
#define DEAD 0

void
printArray(int* a) {
  fputc('\n', stdout);
  for(int y = 0; y < ROW; y++) {
    X_FOR printf("%d ", a[x + COL * y]);
  fputc('\n', stdout);
  }
}

void
evolve(int* a) {
  int x, y, i, j, n, index, neighbour;
  int* r;
  r = calloc(ROW * COL * sizeof(int), ROW * COL);

  int* t;
  t = calloc(25 * sizeof(int), 25);

  for(x = 0; x < COL; x++)
    for(y = 0; y < ROW; y++) {
      index = ID(x, y);
      n = 0;
      for(i = x - 1; i <= x + 1; i++) 
        for(j = y - 1; j <= y + 1; j++) {
          if(x % 5 == 0 && i == x - 1) continue;
          if(x % 5 == 4 && i == x + 1) continue;
          neighbour = ID(i, j); 
          if((i == x && j == y) || a[neighbour] == DEAD) continue;
          n++;
        }
      
      if(n == 3 || (n == 2 && a[index] == 1)) r[index] = ALIVE;
      else if(n > 3 && a[index] == 1) r[index] = DEAD;

      t[x + COL * y] = n;
    }

  printArray(t);
  free(t);

  for(i = 0; i < COL * ROW; i++)
    a[i] = r[i];
  
  free(r);
}

int 
main(){
    int* c;
    c = malloc(COL * ROW * sizeof(int));
    XY_FOR c[x + COL * y] = rand() % 2;
    printArray(c);
    evolve(c);
    printf("\n");
    printArray(c);
    return 0;
}

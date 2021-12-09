#include <stdio.h>
#include <stdlib.h>

#define X_FOR for(int x = 0; x < COL; x++)
#define Y_FOR for(int y = 0; y < ROW; y++)
#define XY_FOR X_FOR Y_FOR
#define YX_FOR Y_FOR X_FOR

#define ROW 7
#define COL 7

int 
aliveCells(int a[ROW][COL], int y, int x) {
  int i, j, count = 0;
  for(i = y - 1; i <= y + 1; i++)
  for(j = x - 1; j <= x + 1; j++) {
    if((i == y && j == x) || (i < 0 || y < 0) || (i >= ROW || j >= COL)) continue;
    if(a[i][j] == 1) count++;
  }
  return count;
}

void
printArray(int a[ROW][COL]) {
  for(int y = 0; y < ROW; y++) {
    X_FOR printf("%d ", a[y][x]);
  fputc('\n', stdout);
  }
}

int 
main(){
    int a[ROW][COL], b[ROW][COL];
    int i,j;
    int neighbour_live_cell;

    YX_FOR a[y][x] = rand() % 2;

    printf("Initial Stage:\n");
    printArray(a);
 
    for(i=0; i<ROW; i++){
        for(j=0;j<COL;j++){
            neighbour_live_cell = aliveCells(a,i,j);
            if(a[i][j]==1 && (neighbour_live_cell==2 || neighbour_live_cell==3)){
                b[i][j]=1;
            }
 
            else if(a[i][j]==0 && neighbour_live_cell==3){
                b[i][j]=1;
            }
 
            else{
                b[i][j]=0;
            }
        }
    }
 
    //print next generation
    printf("\nNext Generation:\n");
    printArray(b);
 
    return 0;
}
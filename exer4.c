/*
Author: Alwyn Dy
Date: 2021, March 12
*/

#include<stdio.h>

#define MAXSIZE 50

typedef struct{
    int value;
    int discovered;
    int x, y;
} Pixel;

typedef struct{
    int n;
    int m;
    Pixel grid[MAXSIZE][MAXSIZE];
} PixelGrid;

void initGrid (PixelGrid *pG);
PixelGrid createGrid();
void printGrid(PixelGrid pG);
void mooreNeighborhood (PixelGrid *pG, int y, int x);

int main() {

    PixelGrid pG = createGrid();

    int ctr=0;
    // loops until a value of 1 is found in the grid and must be undiscovered
    for (int i=1; i<=pG.n; i++){
        for (int j=1; j<=pG.m; j++){
            if (pG.grid[i][j].value==1 && pG.grid[i][j].discovered == 0){
                mooreNeighborhood(&pG, i, j);
                ctr++;
            }
        }
    }

    printf("%d", ctr);



    return 0;
}

// initializes all value, discovered, y, x values of the pixel grid to 0
void initGrid (PixelGrid *pG){
    for (int i=0; i<pG->n+3; i++){
        for (int j=0; j<pG->m+3; j++){
            pG->grid[i][j].value = 0;
            pG->grid[i][j].discovered = 0;
            pG->grid[i][j].y = i;
            pG->grid[i][j].x = j;
        }
    }

    return;
}

// prompts user input to enter grid size and grid values
PixelGrid createGrid(){
    PixelGrid pG;
    scanf("%d %d", &pG.n, &pG.m);

    initGrid(&pG);

    for (int i=1; i <= pG.n; i++){
        for (int j=1; j <= pG.m; j++){
            scanf("%d", &pG.grid[i][j].value);
        }
    }

    return pG;
}

void printGrid(PixelGrid pG){
    for (int i=1; i<=pG.n; i++){
        for (int j=1; j<=pG.m; j++){
            printf("%d ", pG.grid[i][j].value);
        }
        printf("\n");
    }

    return;
}

// uses the moore neighborhood algorithm
void mooreNeighborhood (PixelGrid *pG, int y, int x){

    // returns if pixel already discovered
    if (pG->grid[y][x].discovered == 1)
        return;
    
    pG->grid[y][x].discovered = 1;
    
    int tempX=x, tempY=y;

    // gets values of neigboring pixels
    Pixel neighbors[8] = {pG->grid[tempY][--tempX],  pG->grid[--tempY][tempX], pG->grid[tempY][++tempX], pG->grid[tempY][++tempX], pG->grid[++tempY][tempX], pG->grid[++tempY][tempX], pG->grid[tempY][--tempX], pG->grid[tempY][--tempX]};

    // goes to each neighbor with value of 1
    for (int i=0; i<8; i++){
        if (neighbors[i].value==1){
            mooreNeighborhood(pG, neighbors[i].y, neighbors[i].x);
        }
    }    
}


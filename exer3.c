/*
Author: Alwyn Dy
Date: 2021, March 10
*/

#include<stdio.h>

void printGrid(int arr[][3]);
int findInArr(int a, int b, int arr[][3]);
int checkWin(int arr[][3]);
void clearArr (int arr[][3]);


int main(){
    int arr[3][3]; // stores game data. values: 0 if empty, 1 for X, 2 for O
    int i=0, temp1, temp2, turn, won;

    clearArr(arr);
    while (++i<10){
        // prints the grid
        printGrid(arr);

        // checks if someone won the game
        won = checkWin(arr);
        if (won%10 != 0){
            printf("\n\nEND OF GAME. %c won. ", won%10==1? 'X':'O');
            return 0;
        }
            
        // determines who's turn to play
        if (i%2 == 1){
            printf("X's turn ");
            turn=1;
        }
        else {
            printf("O's turn ");
            turn=2;
        }

        // prompts user to enter values for row and column
        printf("\n\nRow: ");
        scanf("%d", &temp1);
        printf("Column: ");
        scanf("%d", &temp2);

        // checks if entered values are valid (within 1-3)
        if (temp1 >= 1 && temp1 <= 3 && temp2 >= 1 && temp2 <= 3){

            // checks if theres duplicate of entered values in array
            if (findInArr(temp1-1, temp2-1, arr)==0)
                arr[temp1-1][temp2-1] = turn;

            else {
                printf("(%d, %d) Occupied!", temp1, temp2);
                --i;
            }
        }
        else{
            printf("Entered values are not valid\n");
            --i;
        } 

        printf("\n\n");     
    }

    printGrid(arr);
    
    won = checkWin(arr);
    if (won%10 != 0){
        printf("\n\nEND OF GAME. %c won. ", won%10==1? 'X':'O');
        return 0;
    }

    printf("END OF GAME. No winner.");

    return 0;
}


// prints the grid based on array information
// array stores game data
void printGrid(int arr[][3]){
    int i, j;

    for (i=1; i<6; i++){
        for (j=1; j<12; j++){
            // verticals
            if (i%2 != 0 && j%4 == 0 )
                printf("|");

            // horizontals
            else if (i%2 == 0 && j%4 != 0)
                printf("-");
            
            // intersections
            else if (i%2 == 0 && j%4 == 0)
                printf("+");

            // prints X or O depending on array information
            // array stores game data
            // (i-1)/2) AND (j-2)/4 are formula for converting i&j to array locations
            else if (i%2 != 0 && (j==2 || j==6 || j==10)) {
                
                // for X
                if (arr[((i-1)/2)][(j-2)/4] == 1)
                    printf("X");
                
                // for O
                else if (arr[((i-1)/2)][(j-2)/4]==2)
                    printf("O");
                else 
                    printf(" ");
            }
            else printf(" ");

        }
        printf("\n");
    }

    return;
}

// locates location (a,b) in array
// returns 1 if valid value is found (i.e. 1 or 2)
// returns 0 no player owns the cell
int findInArr(int a, int b, int arr[][3]){
    int i;

    if (arr[a][b]!=0)
        return 1;
    else 
        return 0;

}

// check if someone won
// checks each row, column, and diagonal if there are 3 similar values
// game is won if there are 3 values in same row, column, or diagonal
// return codes (2 digits): 
//      left digit is win-code (found at rightmost of every return) (helpful for debugging algo)
//      right digit is winning player
int checkWin(int arr[][3]){
    int i;

    //check diagonals
    if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])
        return arr[1][1]+10;

    else if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0])
        return arr[1][3]+20;

    // check all rows
    for (i=0; i<3; i++){
        if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])
            return arr[i][0]+30;
    }

    //check all columns
    for (i=0; i<3; i++){
        if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i])
            return arr[0][i]+40;
    }
    
    return 0;
}


// clears all elements in array
// writes 0 to all spaces
void clearArr (int arr[][3]){
    int i, j;

    for (i=0; i<3; i++){
        for (j=0; j<3; j++){
            arr[i][j]=0;
        }
    }
    return;
}
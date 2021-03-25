/*
Author: Alwyn Dy
Date: 2021, March 21
*/

#include <stdio.h>
#include <time.h>       
#include <stdlib.h>     
#include <unistd.h>     
#include <conio.h>

#define NPLAYERS 4      // number of players playing the game, max player is 4
#define NSNAKES 3       // number of snakes in the game
#define NLADDERS 3      // number of ladders in the game

typedef struct {
    int x, y;
} Player;

typedef struct{
    int startX, startY;
    int endX, endY;
} Snake;

typedef struct {
    int startX, startY;
    int endX, endY;
} Ladder;

// initialization and printing
void printBoard (Snake *snakeArr, Ladder *ladderArr, Player *playerArr);
void initSnakesLadders (Snake *snakeArr, Ladder *ladderArr);
void initPlayers (Player *playerArr);

// for snakes
int locateSnake (Snake *snakeArr, int y, int x, int mode);
int isGoodSnake(Snake *snakeArr, int index);
int checkSnake (Snake *s, int y, int x);

// for ladders
int locateLadder (Ladder *ladderArr, int y, int x, int mode);
int isNiceLadder (Ladder *ladderArr, Snake *snakeArr, int index);
int checkLadder (Ladder *l, int y, int x);

// for players
int locatePlayer(Player *p, int y, int x);
int movePlayer (Player *p, Snake *snakeArr, Ladder *ladderArr, int moves);
int checkLanding (Snake *snakeArr, Ladder *ladderArr, Player *p);

// misc functions
int randNum(int n);
int absol (int n);

int main(){
    Snake snakeArr[NSNAKES];
    Ladder ladderArr[NLADDERS];
    Player playerArr[NPLAYERS];

    printf("\nNOTE. Initializing the snakes and ladders may take time.\n");
    sleep(1);

    // initialize snakes, ladders, and players
    initSnakesLadders(snakeArr, ladderArr);
    initPlayers(playerArr);

    // initialize variables used in game
    int roundCtr = 0, playerTurn, playerStatus=-1, moves, landing;
    char playing;

    printBoard(snakeArr, ladderArr, playerArr);
    do{
        playerTurn = roundCtr%NPLAYERS;         // gets player for this round

        switch (playerTurn){                    // used for printing
            case 0:
                playing = 'A';
                break;
            case 1:
                playing = 'B';
                break;
            case 2:
                playing = 'C';
                break;
            case 3:
                playing = 'D';
                break;
            }

        printf("\n\n%c's turn",  playing);
        printf("\n  %c, press <Enter> to continue", playing);
        getch();

        moves = (randNum(roundCtr)%6)+1;                             // equivalent to rolling the dice
        playerStatus = movePlayer((playerArr+playerTurn), snakeArr, ladderArr, moves); 
        landing = checkLanding(snakeArr, ladderArr, playerArr+playerTurn);

        printBoard(snakeArr, ladderArr, playerArr);
        printf("\n%c rolls a %d",  playing, moves);

        // special case if player apporaches final cell
        switch (playerStatus){
            case 0:
                printf("\n   Oops! %c needs to roll the exact moves needed to win. Try again next turn.", playing);    
                break;
            case 1:
                printf("\n   Congrats! %c won the game", playing);
                break;
        }

        // if player lands on a ladder or snake
        switch (landing/10){
            case 1:
                printf("\n   %c lands on a snake and goes down %d rows", playing, (snakeArr+(landing%10))->endY - (snakeArr+(landing%10))->startY);
                break;      
            case 2:
                printf("\n   %c lands on a ladder and goes up %d rows", playing, ((ladderArr+(landing%10))->startY - (ladderArr+(landing%10))->endY));
                break;
        }

        roundCtr++;
    } while (playerStatus!=1);

    printf("\n\nThe game finished in %d rounds.", roundCtr);

    return 0;
}


void printBoard (Snake *snakeArr, Ladder *ladderArr, Player *playerArr){
    int snekFlag, ladderFlag;

    printf("\n");

    // prints the board
    for (int i=0; i<(3*10)+1; i++){
        for (int j=0; j<(5*10)+1; j++){

            // prints the borders of the board
            if (i%3 == 0 && j%5 == 0)
                printf("+");
            else if (i%3 == 0 && j%5 !=0)
                printf("-");
            else if (1%3 != 0 && j%5 == 0)
                printf("|");
            else if (i==1 && j==1)
                printf("#");

            else{
                // prints snakes
                if ((i-1)%3 == 0 && (j+1)%5 == 0){
                    snekFlag = locateSnake(snakeArr, (i-1)/3, (j-4)/5, -1);
                    if ( snekFlag == 0)
                        printf("S");
                    else if (snekFlag == 1)
                        printf("s");
                    else printf(" ");
                }

                // prints ladders
                else if ((i-1)%3 == 0 && (j-1)%5 == 0){
                    ladderFlag = locateLadder(ladderArr, (i-1)/3, (j-1)/5, -1);
                    if (ladderFlag == 0)
                        printf("L");
                    else if (ladderFlag == 1)
                        printf("l");
                    else printf(" ");
                }

                // prints players
                else if ((i+1)%3 == 0 && j%5 != 0){
                    switch (j%5){
                        case 1:
                            if (locatePlayer((playerArr+0), (i-2)/3,(j-1)/5))
                                printf("A");
                            else printf(" ");
                            break;
                        case 2: 
                            if (locatePlayer((playerArr+1), (i-2)/3, (j-2)/5))
                                printf("B");
                            else printf(" ");
                            break;
                        case 3: 
                            if (locatePlayer((playerArr+2), (i-2)/3, (j-3)/5))
                                printf("C");
                            else printf(" ");
                            break;
                        case 4: 
                            if (locatePlayer((playerArr+3), (i-2)/3, (j-4)/5))
                                printf("D");
                            else printf(" ");
                            break;
                        default:
                            printf(" ");
                            break;
                    }
                }
                    
                else printf(" ");
            }
        }
        printf("\n");
    }

    return;
}

// randomizes the start and end coordinates for snake and ladder
// while randomizing, it checks if the snakes and ladders are valid (goodSnake and niceLadder)
// VALID if 
//      starting row of snake < ending row of snake && ending row of ladder < starting row of ladder
//      coordinates are unique
//      doesnt start or end at the starting or ending cells
//      have enough diversity in length and distance from other snakes/ladders
void initSnakesLadders (Snake *snakeArr, Ladder *ladderArr){
    int i, j, seed=1, seed2=randNum(42);
    
    // initializes snakes 
    int notGoodSnakeFlag, notGoodPitFlag=1;
    do{
        printf("\nGathering snakes...");
        for (i=0; i<NSNAKES; i++){
            notGoodSnakeFlag=1;
            do{
                printf("\n    snake %d", i);            // for printing purposes

                // randomizer uses system time as seed and adds various seeds to amplify difference in time
                (snakeArr+i)->startX = randNum(++seed2*seed++)%10;
                (snakeArr+i)->startY = randNum(++seed2*seed++)%10;
                (snakeArr+i)->endX = randNum(++seed2*seed++)%10;
                (snakeArr+i)->endY = randNum(++seed2*seed++)%10;

                
                if (isGoodSnake(snakeArr, i) == 1){     // check if the snake is VALID
                    notGoodSnakeFlag=0;
                    printf(" ----- DONE");
                }
                else {
                    notGoodSnakeFlag=1;
                    printf(" ----- FAILED");
                }
            } while (notGoodSnakeFlag==1);              // loops until the snake is VALID
            sleep(1);                                   // allows time to change between initialization of each snake
        }
        
        // assesses all snakes if they are VALID
        // must have enough diversity in length and distance from other snakes
        if (isGoodSnake(snakeArr, -1) == 1)
            notGoodPitFlag = 0;
        else {
            notGoodPitFlag = 1;
            printf("\nSnakes not good.\n");
        }
    } while (notGoodPitFlag == 1);                      // loops until all the snakes are valid

    printf("\n");                                       // for printing 

    // initializes ladders
    int notNiceLadderFlag, notNiceLadderCollectionFlag=1;
    do{
        printf("\nConstructing ladders ");
        for (i=0; i<NLADDERS; i++){
            notNiceLadderFlag = 1;
            do{
                printf("\n    ladder %d", i);

                // randomizer uses system time as seed and adds various seeds to amplify difference in time
                (ladderArr+i)->startX = randNum(++seed2*seed++)%10;
                (ladderArr+i)->startY = randNum(++seed2*seed++)%10;
                (ladderArr+i)->endX = randNum(++seed2*seed++)%10;
                (ladderArr+i)->endY = randNum(++seed2*seed++)%10;

                if (isNiceLadder(ladderArr, snakeArr, i) == 1){         // checks if all ladders are VALID
                    notNiceLadderFlag = 0;
                    printf(" ----- DONE");
                }
                else{
                    notNiceLadderFlag = 1;
                    printf(" ----- FAILED");
                }
            }  while (notNiceLadderFlag == 1);                          // loops until this ladder is VALID

            sleep(1);
        }

        // assesses all ladders if they are VALID
        // must have enough diversity in length and distance from other ladders
        if (isNiceLadder(ladderArr, snakeArr, -1) == 1)                 
            notNiceLadderCollectionFlag=0;
        else{
            notNiceLadderCollectionFlag=1;
            printf("\nLadders not good.\n");
        }
    } while (notNiceLadderCollectionFlag==1);                           // loops until ALL ladders are valid

    return;
}

// intialize players to starting location
void initPlayers (Player *playerArr){
    for (int i=0; i<4; i++){
        (playerArr+i)->x = 0;
        (playerArr+i)->y = 9;
    }

    return;
}

// has 2 modes 
// mode == -1
//      checks ALL snakes for matching coordintes in parameters
// mode !=- 1
//      checks snake indexes 0 to ([mode]-1) for matching coordinates
//      is used to verify if snake is unique or not
int locateSnake (Snake *snakeArr, int y, int x, int mode){

    // simply finds the location of x and y in snek values
    if (mode == -1){
        for (int i=0; i<NSNAKES; i++){
            if ((snakeArr+i)->startX == x && (snakeArr+i)->startY == y)
                return 0;
            else if ((snakeArr+i)->endX == x && (snakeArr+i)->endY == y)
                return 1;
        }
        return -1;
    }

    // checks if snake with same x and y is already present
    else {
        for (int i=0; i<mode; i++){
            if ((snakeArr+i)->startX == x && (snakeArr+i)->startY == y)
                return 1;
            else if ((snakeArr+i)->endX == x && (snakeArr+i)->endY == y)
                return 1;
        }

        return -1; 
    }

}

int checkSnake (Snake *s, int y, int x){
    if ((s->startY == y && s->startX == x) || (s->endY == y && s->endX == x))
        return 1;
    else return 0;
}


// assesses if snake or snake group is VALID
// index accepts from -1 to NSNAKES 
//      if -1, evaluates entire snakeArr if all are good snakes
//      else, do checks to snakeArr[index] if snake is good
int isGoodSnake(Snake *snakeArr, int index){
    int goodPoints=0;
    int i;

    if (index != -1){

        //snek must have STARTY < snek ENDY
        if ((snakeArr+index)->startY < (snakeArr+index)->endY)
            goodPoints+=1;

        // must not start nor end at (0,0) 
        if (!checkSnake(snakeArr+index, 0,0))
            goodPoints+=10;

        // must not start nor end at (9,0) 
        if (!checkSnake(snakeArr+index, 9, 0))
            goodPoints+=100;

        // doesnt have same values (start and end locs) with other sneks
        if (locateSnake(snakeArr, (snakeArr+index)->startY, (snakeArr+index)->startX, index) == -1 && locateSnake(snakeArr, (snakeArr+index)->endX, (snakeArr+index)->endY, index) == -1)
            goodPoints+=1000;
        
        // a good snek has goodPoints of 1111
        if (goodPoints == 1111)
            return 1;
        else return 0;


    }
    else {
        // check if enough diversity of snek lengths (endY - startY > 5)
        for (i=0; i<NSNAKES-1; i++)
            if ((snakeArr+i)->endY - (snakeArr+i)-> startY > 5)
                goodPoints += 1;
        

        // check if good spacing between sneks (difference of one snake's startX AND endX to another snake's startX AND endX)
        for (i=0; i<NSNAKES-1; i++){
            for (int j=i+1; j<NSNAKES; j++){
                if (absol((snakeArr+i)->startX - (snakeArr+j)->startX) > 3)
                    goodPoints+=10;
            }
        }

        // good snake group must have at least [1][1] points
        if (goodPoints%10 >= 1 && goodPoints/10 >= 1)
            return 1;
        else return 0;
    }

}

// has 2 modes 
// mode == -1
//      checks ALL ladders for matching coordintes in parameters
// mode !=- 1
//      checks ladder indexes 0 to ([mode]-1) for matching coordinates
//      is used to verify if ladder is unique or not
int locateLadder (Ladder *ladderArr, int y, int x, int mode){

    // simply finds the location of x and y in ladder values
    if (mode== -1){
        for (int i=0; i<NLADDERS; i++){
            if ((ladderArr+i)->startX == x && (ladderArr+i)->startY == y)
                return 0;
            else if ((ladderArr+i)->endX == x && (ladderArr+i)->endY == y)
                return 1;
        }
    }

    // checks if ladder with same x and y is already present
    else {
        for (int i=0; i<mode; i++){
            if ((ladderArr+i)->startX == x && (ladderArr+i)->startY == y)
                return 1;
            else if ((ladderArr+i)->endX == x && (ladderArr+i)->endY == y)
                return 1;
        }
    }
    return -1;  
}

// checks if (x,y) coord matches Player p coords
int locatePlayer(Player *p, int y, int x){
    if (p->x == x && p->y == y)
        return 1;
    return 0;
}

int checkLadder (Ladder *l, int y, int x){
    if ((l->startY == y && l->startX == x) || (l->endY == y && l->endX == x))
        return 1;
    else return 0;
}

// assesses if ladder or group of ladder is VALID
// index accepts from -1 to NLADDERS 
//      if -1, evaluates ENTIRE ladderArr if all are VALID
//      else, do checks to snakeArr[index] if snake is good
int isNiceLadder (Ladder *ladderArr, Snake *snakeArr, int index) {
    int nicePoints = 0;
    int i;
    if (index != -1){
        //ladder must have STARTY > snek ENDY
        if ((ladderArr+index)->startY > (ladderArr+index)->endY)
            nicePoints+=1;

        // must not start nor end at (0,0) 
        if (!checkLadder(ladderArr+index, 0, 0))
            nicePoints+=10;   

        // must not start nor end at (9,0) 
        if (!checkLadder(ladderArr+index, 9, 0))
            nicePoints+=100;

        // doesnt have same values (start and end locs) with other sneks
        if (locateLadder(ladderArr, (ladderArr+index)->startY, (ladderArr+index)->startX, index) == -1 && locateLadder(ladderArr, (ladderArr+index)->endX, (ladderArr+index)->endY, index) == -1)
            nicePoints+=1000;
        
        // checks if ladder is unique, with respect to snakeArr
        if (locateSnake(snakeArr, (ladderArr+index)->startY, (ladderArr+index)->startX, -1) == -1 && locateSnake(snakeArr, (ladderArr+index)->endY, (ladderArr+index)->endX, -1) == -1)
            nicePoints+=10000;

        // nice ladder has 11111 nice points
        if (nicePoints == 11111)   
            return 1;
        else return 0;
    }

    // evaluates ladder if all are valid
    else {

        // check if enough diversity of ladder lengths (startY - endY > 5)
        for (i=0; i<NLADDERS; i++)
            if ((ladderArr+i)->startY - (ladderArr+i)->endY > 5)
                nicePoints++;
        
        // check if good spacing between sneks (difference of one snake's startX AND endX to another snake's startX AND endX)
        for (i=0; i<NLADDERS-1; i++){
            for (int j=i+1; j<NLADDERS; j++){
                if (absol((ladderArr+i)->startX - (ladderArr+j)-> startX) > 3)
                    nicePoints+=10;
            }
        }

        // good ladder group must have at least [1][1] points
        if (nicePoints%10 >= 1 && nicePoints/10 >= 1)
            return 1;
        else return 0;
    }
}

// moves Player p given [moves]
// return codes
//      -1 no winner
//      0 player exceeds moves needed to win
//      1 Player p won
int movePlayer (Player *p, Snake *snakeArr, Ladder *ladderArr, int moves){
    int temp;

    // rows that move player to left
    if (p->y%2 == 0){
        if (p->y == 0){                         // final row

            // exact moves to make Player p win
            if (p->x - moves == 0){             // player wins
                p->x = 0;
                return 1;
            }

            // if player exceeds the final cell, player loses turn
            else if (p->x - moves < 0)
                return 0;
            
            else p->x -= moves;                 // if nonwinning, just decrement x
        }

        else if (p->x - moves >= 0)             // rows 1-9
            p->x -= moves;

        else {                                  // if [moves] exceeds boundary
            temp = p->x;
            p->y -= 1;
            p->x = 0;
            movePlayer(p, snakeArr, ladderArr, moves-(temp+1));
        }
    } 
    
    // rows that move player to right
    else {

        // doesnt change rows (does not reach boundary)
        if (p->x + moves <= 9)
            p->x += moves;

        // when player reaches boundary given [moves]
        else {
            temp = p->x;
            p->y -= 1;
            p->x = 9;
            movePlayer(p, snakeArr, ladderArr, moves-(10-temp));
        }
    }
     
    return (-1);
}

// checks if Player p lands on a snake or ladder
// return codes indicate what the player landed on and the index
int checkLanding (Snake *snakeArr, Ladder *ladderArr, Player *p){

    // check if player lands on a snake
    for (int i=0; i<NSNAKES; i++){
        if ((snakeArr+i)->startX == p->x && (snakeArr+i)->startY == p->y){
            p->x = (snakeArr+i)->endX;
            p->y = (snakeArr+i)->endY;
            return 10+i;                        // return code, 1 for snake, i for index of snake
        }
    }

    // checks if player lands on ladder
    for (int i=0; i<NLADDERS; i++){
        if ((ladderArr+i)->startX == p->x && (ladderArr+i)->startY == p->y){
            p->x = (ladderArr+i)->endX;
            p->y = (ladderArr+i)->endY;
            return 20+i;                        // return code, 2 for ladder, i for index of ladder
        }
    }
    return -1;
}

// generate random numbers
// n is there since running this function successively returns the same number
int randNum(int n){
    srand((unsigned int)time(NULL)+n);  //sets the seed of  the random() function to the system time
    return rand();
}

// takes absolute value
int absol (int n){
    if (n < 0)
        return -n;
    else return n;
}


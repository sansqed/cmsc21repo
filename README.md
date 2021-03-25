# CMSC 21 Repository

This README.md will provide overview of the exercise and the functions in each exercise file.

---

## Day of the Week `exer1.c`
Given a year, a day, and a month, display 2 things:
1. the day of the week that date falls on
2. what day of the year it is.

    
### **Functions**

- `int isLeapYear(int y);`\
Calculates if Year `y` is leap year or not

- `int r(int y, int m);`\
Modulo operator: $y\mod m$  . Used in `gaussCalendar()`

- `int gaussCalendar (int a);`\
Gauss calendar method to find the day of the week for January 1 of Year `a`.\
Returns 0 (Sunday) to 6 (Saturday).

- `int daysOfMonth (int year, int month);`\
Returns the total number of days for a given month and year

- `int countingDays (int year, int month, int day);`\
Counts how many days is the given date from January 1st

- `int whichDayOfWeek (int days, int janOne);`\
Calculates the day of the week based on the arguments: number of days from Janury 1, and the day of the week of January 1.\
 Returns 0 (Sunday) to 6 (Saturday).

- `int suffix (int days);`\
Adds suffix to numbers for ordinal order (i.e -st, -nd, -rd, -th). Used in conjunction with an array with elements {"st", "nd", "rd", "th"}

- `int isValidDate(int input[]);`\
Checks if the given `input[]` is a valid date.\
`input[]` is array for the date with a format `[year, month, day]`\
Returns boolean. 

---
## Recursion `exer2.c`

Given a choice input (1 - 3), accept arguments and perform an operation based on the following choice inputs:

- **Choice input 1:** 2 positive integers follow---A and B; print out the quotient (whole integer part only) when A is divided by B; NO DIVISION, MULTIPLICATION, OR MODULO ALLOWED
- **Choice input 2:** 2 integers follow---A and B; determine whether they are relatively prime or not; print 1 if relatively prime, 0 if not
- **Choice input 3:** an integer (2 - 20) follows---A; accept and store A more sorted (ascending) integers; accept final search integer N; print 1 if N is one of the A integers, 0 if not.

### **Functions**
- `int divide(int a, int b);`\
Recursive division using subtraction.\
Returns only integers, $\lfloor\frac{a}{b}\rfloor$


- `int gcd(int a, int b);`\
Recursive Euclidean algorithm for finding GCD. \
If GCD is 1, it is relatively prime. Else not.

- `int isSorted (int arr[], int size, int i);`\
Recursively check if `arr[]` is sorted given its `size`. `i` is used for counter, increments every level in the stack.

- `int binarySearch (int arr[], int n, int l, int r);`\
Recursive algorithm for binary search

---
## Tic-Tac-Toe `exer3.c`
A tic-tac-toe game
### **Functions**
- `void printGrid(int arr[][3]);`\
    Prints the grid based on array information\
    Array stores game data

- `int findInArr(int a, int b, int arr[][3]);`\
    Locates location (a,b) in array\
    Returns
    - 1 if valid value is found (i.e. 1 or 2)
    - 0 no player owns the cell

- `int checkWin(int arr[][3]);`\
    Check if someone won\
    Checks each row, column, and diagonal if there are 3 similar values\
    Game is won if there are 3 values in same row, column, or diagonal\
    Return codes (2 digits): 
    - left digit is win-code (found at rightmost of every return) (helpful for debugging algo)
    - right digit is winning player

- `void clearArr (int arr[][3]);`\
    Clears all elements in array (i.e. writes 0 to all spaces)

---
## Object Counting `exer4.c`
Given a $NxM$ grid, count how many objects. An object is defined to be a `1` surrounded `0` in all eight neigbboring pixels.\
For instance, 
- 1 object 
    ```
    0 1 0 0
    1 0 0 0
    1 0 0 0
    0 1 1 1
    ```
- 3 objects
    ```
    1 0 0 0
    0 0 1 0
    0 0 1 0
    1 0 0 0
    ```
### **Structures**
- `Pixel`
    - `int value` - stores `1` or `0`.
    - `int discovered` - (`1` or `0`) `1` If pixel is already discovered, else `0`
    - `int x, y` - coordinates of the pixel in the pixelGrid

- `PixelGrid`
    - `int n, m` - stores the size of grid
    - `Pixel grid[MAXSIZE][MAXSIZE]` - initializes a 2D array of Pixels

### **Functions**
- `void initGrid (PixelGrid *pG);`\
     Initialize all `value` and `discovered` variables of each pixel in the grid to 0 and assign the `x` and `y` coordinates of each pixel in the grid

- `PixelGrid createGrid();`\
    Prompts user input to enter grid size and grid values\
    Returns a PixelGrid

- `void printGrid(PixelGrid pG);`\
    Prints the pixel grid

- `void mooreNeighborhood (PixelGrid *pG, int y, int x);`\
    Uses the moore neighborhood algorithm to search neighboring pixels for a `1`.\
    If `1` is found, recursively goes through all the neighbors, given the pixel is undiscovered (discovered==0)

---

## Sorting `exer5.c`
Sorting Algorithm: Insertion sort.\
Sort the array using pointers and the `+` operator

### **Functions**
- `void insertionSort (int *arr, int size);`\
    Loops entirety of array and checks if an element is unsorted\
    if unsorted, runs `insert()`

- `void insert (int *arr, int item);`\
    Used in conjuction with `insertionSort()`\
    Inserts `item` to a certain index in the array to make it relatively sorted

- `void printArray(const int *arr, int size);`\
    Prints the array

---

## Snakes and Ladders game `exer6.c`
A Snakes and Ladders game with randomized locations of the snakes and ladders

### **Structures**
- `Player`\
  Stores the x-y coordinates of the player

- `Snake` and `Ladder`\
    Stores the `startX`, `startY`, `endX`, and `endY` coordinates used in the game

### **`#define` declarations**
- `NPLAYERS`\
    Number of players playing the game, max of 4

- `NSNAKES` and `NLADDERS`\
    Number of snakes and ladders in the game

### **Functions**
- `void printBoard (Snake *snakeArr, Ladder *ladderArr, Player *playerArr);`\
    Prints the board with the game data

- `void initSnakesLadders (Snake *snakeArr, Ladder *ladderArr);`\
    Initializes the snakes and ladders
    randomizes the start and end coordinates for snake and ladder\
    while randomizing, it checks if the snakes and ladders are valid (goodSnake and niceLadder)\
    ***VALID if***
     - starting row of snake < ending row of snake && ending row of ladder < starting row of ladder
     - coordinates are unique
     - doesnt start or end at the starting or ending cells
     - have enough diversity in length and distance from other snakes/ladders

- `void initPlayers (Player *playerArr);`\
    Intialize players to starting location [y-x coordinate (9,0)]

- `int locateSnake (Snake *snakeArr, int y, int x, int mode);`\
    Locates the snake with the same y-x coordinate as the arguments\
    Has 2 modes 
    - `mode == -1`
        - Checks ALL snakes for matching coordintes in parameters
        - Returns 0 if y-x coordinate is the start of snake,
        - Returns 1 if end of snake
        - If neither, returns -1
    - `mode !=- 1`
         - Checks snake indexes 0 to ([mode]-1) for matching coordinates
         - Returns 1 if it has matching coord, else 0
         - Is used to verify if snake is unique or not

- `int isGoodSnake(Snake *snakeArr, int index);`\
    Assesses if snake or snake group is VALID\
    - Index accepts from -1 to `NSNAKES` 
        - if -1, evaluates entire `snakeArr` if all are good snakes
        - else, do checks to `snakeArr[index]` if snake is good

    Returns Boolean

- `int checkSnake (Snake *s, int y, int x);`\
    Checks if Snake s has the same coordinate as the arguments or not\
    Returns boolean

- `int locateLadder (Ladder *ladderArr, int y, int x, int mode);`\
    Locates the ladder with the same y-x coordinate as the arguments\
    Has 2 modes 
    - `mode == -1`
        - checks ALL ladders for matching coordintes in parameters\
        - Returns 0 if y-x coordinate is the start of ladder,
        - Returns 1 if end of ladder
        - If neither, returns -1
    - `mode !=- 1`
        - checks ladder indexes 0 to `([mode]-1)` for matching coordinates
        - Returns 1 if it has matching coord, else 0
        - Is used to verify if ladder is unique or not    

- `int isNiceLadder (Ladder *ladderArr, Snake *snakeArr, int index);`\
    Assesses if ladder or group of ladder is VALID
    - Index accepts from -1 to NLADDERS 
        - if -1, evaluates ENTIRE ladderArr if all are VALID
        - else, do checks to snakeArr[index] if snake is good

    Returns Boolean

- `int checkLadder (Ladder *l, int y, int x);`\
    Checks if Ladder l matches the y-x coordinate\
    Returns 1 if match, else 0

- `int locatePlayer(Player *p, int y, int x);`\
    Checks if (y,x) coord matches Player p coordinates\
    Returns boolean

- `int movePlayer (Player *p, Snake *snakeArr, Ladder *ladderArr, int moves);`\
    Moves Player p given [moves]
    - Return codes
        - -1 no winner
        - 0 player exceeds moves needed to win
        - 1 Player p won

- `int checkLanding (Snake *snakeArr, Ladder *ladderArr, Player *p);`\
    Checks if Player p lands on a snake or ladder\
    Return codes (2 digits) indicate what the player landed on (1 for snake, 2 for ladder) [tenth digit] and the index [ones digit]

- `int randNum(int n);`\
    Generate random numbers\
    `n` is there to add something to the system time (used as seed for generating random numbers) since running this function successively returns the same number

- `int absol (int n);`\
    Takes absolute value of `n`


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

---

## Fractions `exer7.c`
### **Structure**
- `Fraction`
    - `int nume` $\to$ numerator
    - `int denom` $\to$ denominator

### **Functions**
- `Fraction add (Fraction a, Fraction b);`\
    Addition of fractions

- `Fraction subtract (Fraction a, Fraction b);`\
    Subtraction of fractions

- `Fraction multiply (Fraction a, Fraction b);`\
    Multiplication of fractions

- `Fraction division (Fraction a, Fraction b);`
    Division of fractions

- `Fraction getFraction ();`\
    Prompts user input for the fraction values\
    - If player inputs '/', denominator is asked\
    - Else, denominator is automatically 1

- `void printFraction (Fraction f);`\
    Prints the fraction\
    If denominator is 1, only print numerator

- `int gcf(int a, int b);`\
    Euclidean algorithm for finding gcf\
    Recursive

- `void simplify (Fraction *f);`\
    Simplify the fraction\
    Finds the gcf of numererator and denominator and divides it with gcf

- `int absol (int n);`\
    Get absolute value of `n`

---

## Strings `exer8.c`
Accept an integer choice (1 - 2), accept string arguments (at most 15 characters each) and perform an operation based on the following choice inputs:

Choice input 1: 2 strings follow---A and B; print out the concatenation of A and B\
Choice input 2: 3 arguments follow, 1 string---A and 2 integers---B and C; print out the slice of A from B to C.

### **Structures**
- `Vector`
  - int size; $\to$ stores the length of string
  - int capacity;  $\to$ stores the capacity of string, 10 at first
  - char *str; $\to$ stores the string

### **Functions**
- `void initString(Vector* vecString, char* string);`\
    accept string, insert string into Vector

- `void concatenate(Vector* combined, Vector* a, Vector* b);`\
    concat Vector a & b, put result in Vector combined

- `void slice(Vector* sliced, Vector* source, int start, int end);` \
    takes a portion of source starting from start and ends at end - 1

- `void initVector(Vector *v);` \
    Initializes the vector.\
    size = 0, capacity = 10, str is dynamically allocated
- `void printVector (Vector *v);`\
    Prints the string in the vector
- `int strLen (char *str);`\
    Returns the length of the string
- `void resize (Vector *v, int size);`\
    Resize the vector\
    accepts Vector v and size >= -1
    - if size == -1, double the size of v
    - else, make size of v = size

## Student Information System `exer9.c`
### **Structures**
- Student
  - `char studNum[15];` $\to$ stores student number, hyphenated, at most 15 chars
  - `char lastName[15], firstName[15];`  $\to$ stores student's last and first name, should not have spaces, at most 15 chars
  - `char course[15];` 
  - `int yrLevel;`
  - `int age;` $\to$ age >= 0
  - `char sex;` $\to$ 'M' or 'F'
  - `int finalGrade;` $\to$ 0 - 100, 60 passing

  - `struct Student *next;` $\to$ pointer to the next student in the list
- SRecord
  - `Student *head;` $\to$ pointer to the head of student record
  - `Student *tail;` $\to$ pointer to the tail of the student record
  - `int size;` $\to$ size of the record, how many students are in the student record

### **Functions**
- `void menu ();`
```
    STUDENT INFORMATION SYSTEM
1. Enrol a student
2. Drop a student
3. Edit a student
4. Display all students
5. Filter students by last name
6. Filter students by student number
7. Filter students by year level
8. Filter students by course
9. Filter students by sex
10. Filter students by passing
11. Filter students by failing
12. Sort students by last name
13. Sort students by student number
14. Exit
```

- `void printStudent (Student *s, int mode);`\
    Prints student info\
    2 modes: 
    - mode 0 -> print specific student info
    - mode 1 -> prints editable student info

- `Student *initStudent ();`\
    Prompts user to input student details

- `void initRecord (SRecord *record);`\
    Initialize record\
    All values are zero (head, tail, and size)

- `int enrolStudent (SRecord *record, Student *s);`\
    Places the student at the end of the record\
    Increments size of record

- `void insertStudent(SRecord *record, Student *s, int index);`\
    Inserts student in the record at index

- `void dropStudent (SRecord *record, int index);`\
    drops student from the record\
    int index is the index of the student to be dropped\
    adjusts the record to remove the student\
    frees the memory allocated for that student

- `void editStudent (SRecord *record, int index, int fieldToEdit);`\
    edit student information\
    fieldToEdit accepts an int 1-8, corresponding to student information

- `void displayAllStudents (SRecord record);`\
    display all students in the record

- `void filterStudents (SRecord *record, int mode, char *detailToMatch);`\
    filter students in the record depending on int mode\
    int mode accepts 0-6 [last name, student number, year level, course, sex, passing, failing]\
    detailToMatch is the detail needed for filtering

- `void sortRecord (SRecord *record, int mode);`\
    sorts the record depending on mode\
    mode accepts 0-3 [sort by last name, student number, first name (iff multiple last names exist)]

- `int strCmpLower (char *str1, char *str2);`\
    compares the lowercase version of str1 and str2\
    similar to strcmp
    - returns 1 if str1 > str2
    - returns -1 if str1 < str2
    - returns 0 if str1 == str2

- `int isStrSimilar (char *str1, char *str2);`\
    compares if str1 and str1 are similar

- `int getStudentIndex (SRecord record, char *studNum);`\
    returns student index based on student number\
    returns -1 if student not in record

- `Student *getStudent (SRecord *record,int index);`\
    gets student based on index in the record

- `int isValidStudNum (char *str);`\
    valid student number must contain only numbers and hyphen


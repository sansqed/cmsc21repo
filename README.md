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
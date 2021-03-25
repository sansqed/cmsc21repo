# Blog for CMSC 21
###### tags: `Acads` `CMSC21`

## Week 1
I didn't really have a hard time writing the programs for the exercises since I'm already quite familiar with C from my first year of comsci in CIT. I've also developed a skill for debugging my codes from my coding experiences.

However, I had difficulty writing the recursive algorithm behind the Euclidean Algorithm for finding the GCD. Thankfully our notes from Discrete Math from the last semester had a pseudocode for it and it was just a matter of converting it to recursion (I also consulted the good 'ol stack overflow for this :3). 

I'm making it a habit to add comments to my codes since I may use these algorithms as reference for my future programs. Also, I'll start to backup my codes to my Github account for a repository of my codes. 

I'll also start creating a file that summarizes my program's functions, in case I may need to find and use algorithms that I had written before, it would be easy for me to locate these algorithms.

I'm looking forward to the upcoming weeks for much more challenging coding exercises.

---
## Week 2

### 2D Arrays
2D arrays are just like boxes inside boxes. 

Imagine a scenario where you bought a lot of cellphones from different sellers as a giveaway for some event. Usually, and if bought legitemately, each phone will be enclosed inside a box. Inside these phone boxes are other boxes that contain the charger and other accessories. If, for some reason, you need to *borrow* one of these included accessories, you first need to locate which phone model/brand it belongs, then when you open the correct phone box, you have to locate the correct box where it is packed. The same is true for 2D arrays, sans the suspiciousness. 

### Tic-tac-toe

At first I planned to make a 1D array with a size of 18 where the x and y coordinates of the X and O are adjacent to one another and I just had to loop through every other element. 

However, I realized it would be much easier to make a 3x3 array and replicate the game data to the array. Arbitrarily, I chose Xs to be 1, Os be 2, and empty cells be 0. For example, the 2D array
```
{{0,0,1},

{0,1,2},

{2,0,1}}
```

would translate to 

```
   |   | X
---+---+---
   | X | O
---+---+---
 O |   | X

```
This way, locating the Xs and Os will be much more intuitive.

Printing the grid with the game data (`void printGrid(int arr[][3]);`) was a challenge. I thought the `j` (variable that takes care of the columns) would just be from 0 to 5, similar to `i`(for the rows). However, I didn't account for the 3 dashes.

I first took care of printing the grid without the game data with if else conditions. After visualizing and drawing the expected grid on a whiteboard and analyzing what column and rows should the `|`, `-`, and `+` characters be placed for values of `i` and `j`, I realized that it would be easier to start i and j from 1 since there would be patterns that would make printing easier the "lines" of the grid easier. The boundary for i would just be $3+2$, while j would have $4*3-1$ (the pattern `---+`, having a width of 4, repeats thrice and  the last one would have the `+` omitted)

For instance, the `|` should be placed on odd numbered rows (hence the `i%2!=0` condition) and columns with multiples of 4 (`j%4==0` condition). The `+` should be printed below the `|` (i.e. even rows). The remaining places in the even numbered rows will have `-`.

Adding the printing of game data required me to write a table that maps the locations of 1 and 2 (values for X and O) from the 2D array to the grid, create an equation out of it, then, after some algebra, figure out the formula to use. I came up with 2 formulas, $\frac{i-1}{2}$ and$\frac{j-2}{4}$ that uses the `i` and `j` values in the printing of the grid to find the corresponding coordinates in the 2D array.

For instance, using the values above, we find that `arr[0][2]` is a 1 (translates to X in the grid). It should be printed on the grid with `i=1` and `j=10`. 

Then it was just a matter of if else conditions to print the `X`, `O`, and ` ` (a space). 

For the function to check for the winner (`int checkWin(int arr[][3]);`), I just had to check for all the rows, columns, and diagonals for similar values in the array. I placed the conditions for the diagonals first since it's just $O(1)$. I also incorporated different 2-digit return codes for debugging purposes and to determine who won the game. The first digit is the win-code (determines how the player won, either thru diagonals, rows, or columns) and the second digit is the winner (either 1 or 2).

Lastly, I wrote 2 other miscellaneous functions: `void clearArr (int arr[][3]);` and `int findInArr(int a, int b, int arr[][3]);`. The first is just to initialize all the elements in the 2D array and assign a value of 0 to each cell. The second is to check if a cell is occupied, and is used in the int main to ensure the inputs from the users will not be duplicated.


### Object Counting

I really had a hard time with this one. I got stuck on checking if a pixel is in the corner of the grid or not, since I won't be able to find all 8 neighboring pixels if it is. However, after the coding session I realized that I could just expand the grid. I felt dumb after realizing that I could do that. I also planned to use structs because it is cool.

For the `Pixel` struct, I placed a variable called discovered, to replace the group variable in Sir Eli's code since I realized that the group numbers are unnecessary. 

I also took into consideration what Sir Eli said and made another struct called `PixelGrid` with `n` and `m` for the size and the grid 2D array. However, I had a hard time figuring out how to initialize the grid. In the end I just defined a `MAXSIZE` of 50 and use it as size for the array. Kinda hacky but I didn't want to use dynamic arrays since I forgot how to `malloc` and `calloc` and I read somewhere that you can't really have a 2D dynamic array *huehue*. 

I made an `initGrid` function to initialize all value and discovered variables of each pixel in the grid to 0 and assign the `x` and `y` values in each pixel. At first it didn't work but I realized that I'm changing the values of the `PixelGrid` and had to make it a pointer. 

Also wrote a `createGrid` function with a PixelGrid return type to take care of user prompts. And a `printGrid` to print the grid during the early hours of making this program and find out if the functions above work. 

All was fairly smooth until I wrote the algorithm for the object counting part. I initially planned to use the algorithm I found online where it searches for the first instance of a 1 in the neighboring pixels (clockwise) but the pseudocode was really confusing. To finish this exercise, I decided to use Sir Eli's code as reference for this part. The use of `discover` variable in my `Pixel` struct made the algorithm simpler and I just had to create a counter variable to count the objects since it would just have the same functionality as the `group` variable. I also made the `PixelGrid` a pointer since I will be changing its values in this function.

Also, up until this point, I haven't uploaded this blog to a website. I already made a wordpress site but I don't want to waste my time configuring the UI. Then I realized that I could just upload it on hackmd, taking inspiration from Sir Rub. That way, I can also write codes in my blog.

---

## Week 3 and 4 {#week-3-4}

### Pointers

An analogy for pointers would be... the social "dance" when you're trying to ask someone out for a date and you ask the help of a wingman--the wingman is the pointer. 

When initializing a pointer, you first indicate what data type you want it to point, then the memory address of the variable using the `&` if not an array. When you want to change the value of the pointed variable, you use the `*` or the `->` operators. You can also change the variable it points by using the `&` operator again, or the `+` operator for arrays. 

Likewise, when you ask the help of a wingman, you specify your *type* (gender, physical appearance, qualities, etc.), then you tell them your potentials (similar to the `&` operator). When you have something to say to the person you're asking out, you tell the wingman "Tell them I said *bla bla bla*" (similar to the `*` and `->` operators). When you realize you have no chance of having a date, you could tell the wingman your next potentials (similar to the `&` and `+` operators). 

### Sorting

I decided to use insertion sort to to sort the array. At first I had a hard time creating the algorithm but after writing it down on a whiteboard and breaking down its steps, I kinda got an idea and started coding it. I wasn't sure how to reassign the elements in the array using pointers so I wrote a `test()` function and figured that `*(arr+i)` would just work. There was a problem when I first run the program, but after debugging, I was just being careless and added 1 instead of subtracting 1 lmao. 

Insertion sort works by starting from the second element in the array until the last, searching for an element that's unorder (i.e. less than the previous element). If it detects one, it locates the index where, when *inserted*, makes the array more sorted. The insertion works by moving the other elements to the right to make room for insertion. When the outer loop (i.e. the loop that detects an unordered element) traverses the entirety of the array, the array is deemed to be sorted. This algorithm has a time complexity of $O(n^2)$.

This table shows the process of insertion sort


|Steps|     |     |     |     |     |
|-----|-----|-----|-----|-----|-----|
|  0  |  4  |  3  |  5  |  2  |  1  |
|  1  | [4] |**3**|  5  |  2  |  1  |
|  2  |  3  |  4  |  5  |  2  |  1  |
|  3  | [3] | [4] | [5] |**2**|  1  |
|  4  |  2  |  3  |  4  |  5  |  1  |
|  5  | [2] | [3] | [4] | [5] |**1**|
|  6  |  1  |  2  |  3  |  4  |  5  |

**Step 0** is the original unsorted array\
**Step 1** considers the 3 (in bold) as out of order and shifts 4 (inside square brackets) to the right to insert 3\
**Step 2** is the relatively ordered array\
**Step 3** considers 2 as out of order and shifts all the square-bracketed elements to the right and inserts 2 at index 0\
**Step 4** is the relatively ordered array\
**Step 5** considers 1 as out of order and shifts all the square-bracketed elements to the right and inserts 1 at index 0\
**Step 6** is the ordered array

### Snakes and Ladders
This exercise was really a challenge. At first, the exercise seemed relatively simple, but I realized that there are a lot of validation checks and algorithms needed to be implemented to make a valid Snakes and Ladders game. 

**First** is the randomization of the locations for the snakes and ladders. You can't just randomize the locations of the snakes and ladders and call it a day—there are certain conditions needed to make the snakes and ladders valid:

1. The head of the snake must be above the tail, and the start of the ladder must be below its end.
2. Both snakes and ladders must not start and end at locations (0,0) *\[the final cell where the winner is decided\]* and (9,0) *\[the starting cell for all players\]*
3. The locations of the snakes and ladders must be unique.

Furthermore, to make the game interesting, 

4. there has to be enough diversity in the lengths of the snakes and ladders, 
5. as well as its spacing from one another. 
   
To implement these conditions, I wrote a function to validate each snake and ladder for conditions 1, 2, and 3, and evaluate the snake and ladder arrays (i.e. evaluate the arrays as one) for conditions 4 and 5. I further wrote functions to implement specific tasks such as traversing the array to look for certain `x` and `y` values and detecting if the values for each snake and ladder are unique. 

**Second,** the player moves in a zigzag pattern along the board. Since I approached this with a 2D array in mind (but didn't really implemented a 2d array to make it less confusing), I had to decrement the `y` value everytime the player reaches the border and changes rows (since the topmost row is 0 and the bottommost is 9). Moreover, I had to reset the `x` value to the corresponding border and subtract the moves it took to reach the border from the total moves (i.e. the rolled dice). There is also a special condition when the player reaches the topmost row (row 0), specifically when it approaches the final cell. The player should roll the exact moves needed to win, else the player loses the turn. However, there are some rules that made the player *bounceback* when it rolls an inexact number; I chose to implement the former. 

**Third,** the dice rolls and the locations for each snake and ladder must be randomized. Using the system time as a seed, randomizing the dice was easy. However, due to the successiveness of initializing the snakes and ladders within a loop, the system doesn't have enough delay to change the time. Hence, I decided to add a number to the system time, and increment the it every randomization. Moreover, I also wrote a `sleep(1)` as a delay to allow the system to change the time, making the randomization even more varied. 

**Finally,** for some reason, there are certain bugs that I'm not sure how it was introduced. I was sure that my algorithm was correct, and yet some return values were unexpected and some conditions didn't work. For instance, when a player lands on a ladder, the program should print `A lands on a ladder and goes up 6 rows` or something like that, but it didn't. After hours of testing and writing `printf` statements on various locations in my code, I deduced that it was due to a certain function returning an incorrect value. To fix this, I just made another function to do this task, then it worked fine.

Furthermore, to make the game more customizable, I defined the values for the number of players playing the game and the number of snakes and ladders at the start of my code. Though the maximum number of players is just 4 because of the grid.

I have many improvements in mind that would make the program more efficient and more customizable, like having an array that stores the letters of the players instead of using A, B, C, and D, or just reusing functions to do certain task, but I don't want to ruin the working program so I'll just have to settle with this. Afterall, a program is never finished. 
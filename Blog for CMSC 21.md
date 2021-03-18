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
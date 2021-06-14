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

---

## Weeks 3 and 4

### Pointers

An analogy for pointers would be... the social "dance" when you're trying to ask someone out for a date and you ask the help of a wingman--the wingman is the pointer. 

When initializing a pointer, you first indicate what data type you want it to point, then the memory address of the variable using the `&`, if not an array. When you want to change the value of the pointed variable, you use the `*` or the `->` operators. You can also change the variable it points by using the `&` operator again, or the `+` operator for arrays. 

Likewise, when you ask the help of a wingman, you specify your *type* (gender, physical appearance, qualities, etc.), then you tell them your potentials (similar to the `&` operator). When you have something to say to the person you're asking out, you tell the wingman "Tell them I said *bla bla bla*" (similar to the `*` and `->` operators). When you realize you have no chance of having a date, you could tell the wingman your next potentials (similar to the `&` and `+` operators). However, this analogy breaks if you try to date the wingman.

### Sorting

I decided to use insertion sort to sort the array. At first I had a hard time creating the algorithm, but after writing it down on a whiteboard and breaking down its steps, I kinda got an idea and started coding it. I wasn't sure how to reassign the elements in the array using pointers so I wrote a `test()` function and figured that `*(arr+i)` would just work. There was a problem when I first run the program, but after debugging, I was just being careless and added 1 instead of subtracting 1 *lmao*. 

Insertion sort works by starting from the second element in the array until the last, searching for an element that's unorder (i.e. less than the previous element). If it detects one, another loop locates the index where, when *inserted*, makes the array more sorted. The insertion works by moving the other elements to the right to make room for insertion. When the outer loop (i.e. the loop that detects an unordered element) traverses the entirety of the array, the array is deemed to be sorted. This algorithm has a time complexity of $O(n^2)$.

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
This exercise was really a challenge. At first, it seemed relatively simple, but I realized that there are a lot of validation checks and algorithms needed to be implemented to make a valid Snakes and Ladders game. 

**First** is the randomization of the locations for the snakes and ladders. You can't just randomize the locations of the snakes and ladders and call it a day—there are certain conditions needed to make the snakes and ladders valid:

1. The head of the snake must be above the tail, and the start of the ladder must be below its end.
2. Both snakes and ladders must not start and end at x-y locations (0,0) *\[the final cell where the winner is decided\]* and (0,9) *\[the starting cell for all players\]*
3. The locations of the snakes and ladders must be unique.

Furthermore, to make the game interesting, 

4. there has to be enough diversity in the lengths of the snakes and ladders, as well as,
5. enough spacing from one another. 

To implement these conditions, I wrote a function to validate each snake and ladder for conditions 1, 2, and 3, and evaluate the snake and ladder arrays (i.e. evaluate the arrays as one) for conditions 4 and 5. I further wrote functions to implement specific tasks such as traversing the array to look for certain `x` and `y` values and detecting if the values for each snake and ladder are unique. However, this method made the program clunky and sometimes it takes a while to find valid snakes and ladders. Now that I think of it, I could've first randomized either the start or end coordinates of the snakes and ladders and use that as initial point to randomize the other set of coordinates (e.g. randomize the `endY` value of the snake so that the `startY` value will just be a random number from 0 to `endY-1`). This could've made the validation process shorter. *Oh well.*

**Second,** the player moves in a zigzag pattern along the board. Since I approached this with a 2D array in mind (but didn't really implemented a 2D array to make it less confusing), I had to decrement the `y` value (i.e. the row value) everytime the player reaches the border and changes rows (since the topmost row is 0 and the bottommost is 9). I also had to increment the `x` value for odd-numbered rows, and decrement it for even-numbered rows. Moreover, I had to reset the `x` value to the corresponding border and subtract the moves it took to reach the border from the total moves (i.e. the rolled dice). There is also a special condition when the player reaches the topmost row (row 0), specifically when it approaches the final cell. The player should roll the exact moves needed to win, else the player loses the turn. However, there are some rules that made the player *bounceback* when it rolls an inexact number; I chose to implement the former. 

**Third,** the dice rolls and the locations for each snake and ladder must be randomized. Using the system time as a seed in the `srand()`, randomizing the dice was alright. However, due to the successiveness of initializing the snakes and ladders within a loop, the system doesn't have enough delay to change the time. Hence, I decided to add a number to the system time, and increment it every randomization. Moreover, I also placed a `sleep(1)` as a delay to allow the system to change the time during initialization, hopefully making the randomization even more varied. 

**Finally,** for some reason, there are *mysterious* bugs in my code that I'm not sure how it was introduced or why it happened. I was certain that my algorithm was correct, and yet some return values were unexpected and some conditions didn't work. For instance, when a player lands on a ladder, the program should print `A lands on a ladder and goes up 6 rows` or something like that, but sometimes it didn't print. After hours of testing and writing `printf` statements on various locations in my code, I deduced that it was due to a certain function returning an incorrect value, which led to the `if` conditions not running; however I'm not quite sure why (at some point, I blamed the compiler for this bug and reinstalled it *lol*). To fix this, I just made another function to do this task, then it worked fine. If it weren't for those bugs, I would've finished this exercise earlier

Furthermore, to make the game more customizable, I defined the values for the number of players playing the game and the number of snakes and ladders at the start of my code using `#define`. Though the maximum number of players is just 4 because of the limitations of the grid.

I have several improvements in mind that would make the program more efficient and more customizable, like having an array that stores the letters of the players instead of just using A, B, C, and D everytime, or just reusing functions to do certain tasks, or perhaps rethinking my algorithms. But I don't want to ruin the working program so I'll just have to settle with this and save myself some headaches. Afterall, programs are never really finished. 

---

## Week 5
### Dynamic Memory Allocation
Reading the course notes, I kinda got an idea when and how to use `malloc()` and `free()`. However, I think I need a programming exercise where I can use those functions to fully understand their use cases and how they are used with other C functions and the nuances associated with using them. Perhaps, next week's exercises will be more exciting. 

To me, the idea of manually allocating the memory is interesting and I'm sure it will prove useful in the future and with more complex programs. After all, one of the perks of starting with the C language is being able to encounter and use functions that deal with deeper level functionalities. However, I don't think that dynamically allocating memories is appropriate in all cases. There are still some instance where a static memory is applicable and more convinient. For instance, if a variable or array will only be used once or has simple purpose in the overall code, static memory should just be fine. However if the said variable or array will store values that will get larger as the program progresses, dynamically allocating it would be more efficient.

I remember when I told my cousin, who is familiar with programming, that we are starting with the C language. He told me that the curriculum should've used more human-readable and easier languages like Python. However, I think for a computer science student, being acquianted and having deep knowledge about system-level programming is one of the essence of the course. Knowing how to code in old and low-level languages will be beneficial to us since we will understand how the computer will behave without the help of a more lenient language. Being immersed in difficult and unforgiving languages will make the high-level ones easier. 

---

## Week 6 and 7
### Lists
Lists are awesome!! I first heard about them while watching a Youtube video by Computerphile explaining pointers. At that time, I wasn't able to grasp the entirety of its content, but after rewatching it now, it all made sense. Though the video also introduced double pointers which I don't understand yet. I prefer the singly-linked list over the other lists presented in the course notes since it can be expanded easily. Sorting the singly-linked list is also relatively simple, algorithm-wise, compared to sorting arrays since I just have to change the `next` pointer of at most 3 variables. Conceptualizing the sorting algo was a challenge, but after creating another program to implement it in a much simpler list, I got the hang of it. 

I implemented the insertion sort in exercise 9 since there is already an `insertNode` function found in the course notes and it was just a matter of changing the variables to make it work. Though I want to try other sorting algorithms since I already implemented bubble and selection sort in the past. 

I had some difficulty doing the filtering of students in exercise 9. I initially planned to create another record to store the filtered list but I realized I need to make another instance of the student so that the `next` pointer won't change in the original student record. So instead, I just printed out the information of the student that matched the criteria. 

And finally, I got tired of retyping every student information when testing the algorithms of the program so I just wrote an auto hotkey script that automatically types the information for me and I just have to press key combinations to trigger it. I might do the same for future exercises so that I can focus my time and energy on actually making my program work. 

---

## Week 8

### File Handling

Honestly, I still have a hard time getting used to the different functions and arguments involved in file handling. Plus, the addition of file-position pointers makes it more complicated. However, I kinda get the difference between sequential access and random-access. 

Sequential access just reads the corresponding size of the data type from the file. For example, `int` has a size of 4 bytes in some compilers, and a `char` has a size of 1 byte. Using sequential access, we can have `fscanf(fp, "%d %c", &tempInt, &tempChar)` which gets an `int` and a `char` respectively from the file. However, this comes with drawbacks, since the order of these data types within the `fscanf()` function is important. Reversing the order (i.e. `"%c %d"`) would get different values. Additionally, the order in which these data types are encoded in the file must be the same when accessing them. This is prone to errors and bugs along the program. Another drawback is not being able to *jump* to different locations of the file since we cannot determine the location of the specific value we are looking for or its data type. Overwriting and updating files in sequential access can be quite chaotic since we aren't sure if we are changing the values of the next data because of the non-uniformity of the data types.

Random-access, on the other hand, doesn't come with these drawbacks, given the file only contains one data type or struct. With random-access, we can be sure that each *block* of data within the file has the same size and we can just utilize the `fseek()` function to *jump* anywhere within the file and know that the file-location pointer is either at the start or end of a *block* of data. Random-access is kinda like having an array of a struct but is stored in a file. Reading and writing in random-access utilizes the original struct used in encoding the data into the file. Moreover, overwriting a *block* of data in random-access is more tamed compared to sequential access since each *block* is fixed and we don't have to worry about unnecessarily changing the values of the succeeding data. With more complex programs such as the Student Information System 2, I realized that using the `fseek()` function whenever accessing a specific data saves a lot of headaches. 

Regarding the different file opening modes, I had a hard time at first because the `+` mode didn't work the first time I tried it in my program, so I had to experiment a bit. Though, in retrospect, I think I somehow messed up implementing it. Luckily it worked and it saved me a lot of thinking. I was also testing out the differences between having the `b` (the binary mode) and without it. I thought that without the binary mode, the `.bin` files would be much readable when opened in the regular text editors; I also tried it with `.txt` files, but it didn't change anything. I also had trouble with the `w` mode (write mode) since it kept erasing the previous student whenever I enroll a student in the SIS 2, unlike the sample code given in the course notes. In the end I just used the `a` mode (append mode). 

Finally, I really had a hard time adjusting to random-access since I've tried accessing a `.csv` file in C before and I thought they are the same and use the same functions to parse. I used `strtok()` with the `.csv` files and I tried it with random-access and it didn't work. After rereading the course notes, I realized parsing with random-access is much easier.

---

## Week 9-11
### C++

C++ is cooooolllll!!!!! Tho there are still some functionalities that I find easier to do in C than in C++ like being able to format how the `printf` prints 2 decimal places in floats; doing that in C++ requires using another library (idk if there's an easier method for this). But overall, I like how flexible C++ is and how it offers more built-in data types than C (like `bool` and `string`). I also had fun trying out exception handling. I like C++ more than C. `C++ > C` (tho it returns false if put into code *lol*)

There are also a lot of concepts in C++ that I'm still not familiar with, like namespaces, references,  the `>>`,  `<<`, and `::` operators, and templates. But I guess I'll understand them deeper if I'll code in C++ more and explore these concepts.

I'm also not familiar with file reading in C++. I did some readings aaand I came into the conclusion that I need to actually code using these functions in order to fully understand how they work. One thing I've learned from this course is to not be complacent on how simple the code from online tutorials and from the course notes are because it's much more complicated than it seems. I'm *planning* to code more in C++ during the break.

I've had experience using classes in Javascript when I did my immersion way back when I was in senior high so it was easier to comprehend. Tho the private, public, and protected access specifiers are kinda new to me so I just tested their boundaries when I started doing the exercises to really understand them. All in all, classes are interesting. I kinda wanna learn Object Oriented Programming.

---

## Week 12
### Code reuse

Code reuse is a bit complicated to understand. There are a lot of new concepts being introduced and using them would be much more confusing  than previously introduced concepts. Tho the `is-a` and `has-a` phrases are helpful in establishing the difference between composition and inheritance and making it more understandable. 

Doing the exercise, I had a hard time figuring out how to do the constructor in the derived classes. Thankfully, a blockmate helped me out and I learned that I can use the `:` operator between the constructor of the derived class and constructor of the base class. 

I don't know if this is really the case but I found similarities in having the `::`  operator when using the `std `namespace, the `Package` class , and the `Math` class from the course notes, and I came into conclusion that they are kinda similar. Like, we use the `::` operator to access the particular function found in that particular group of functions. It's like the `.` or `->` operators in pointers, except we don't really have to initialize a pointer variable.  

Overall, code reuse is interesting and I kinda wanna do more programming exercises regarding this topic. 






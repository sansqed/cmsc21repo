# CMSC 21 Repository

This readme.m will provide overview of functions in each exercise file.

---

## `exer1.c`
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
## `exer2.c`
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

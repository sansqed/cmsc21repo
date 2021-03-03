/*
Author: Alwyn Dy
Date: 2021, Mar 2
*/

#include<stdio.h>

int isLeapYear(int y);
int r(int y, int m);
int gaussCalendar (int a);
int daysOfMonth (int year, int month);
int countingDays (int year, int month, int day);
int whichDayOfWeek (int days, int janOne);
int suffix (int days);
int isValidDate(int input[]);

int main(){
    // initialize variables
    int input[3];
    int countDays, whichDay;

    // arrays that contain the day of the week and the suffix for numbers
    char dayOfWeek[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    char suffArr[4][3] = {"st", "nd", "rd", "th"};

    // prompts user input, checks validity
    // year-month-day format
    scanf("%d %d %d", &input[0], &input[1], &input[2]);
    if (!isValidDate(input)){
        printf("Error! Entered date is not valid.");
        return 0;
    }

    // calculates the day of the week and the -th day of entered date
    countDays = countingDays(input[0], input[1], input[2]);
    whichDay = whichDayOfWeek(countDays, gaussCalendar(input[0]));

    // checks validity of calculated -th day
    if (countDays==-1){
        printf("Error!");
        return 0;
    }

    // successful run, prints output
    printf("%s, %d%s day of the year", dayOfWeek[whichDay], countDays, suffArr[suffix(countDays)]);

    return 0;
}

// calculates if Year y is leap year or not
int isLeapYear(int y){
    if (y%400 == 0)
        return 1;
    else if (y%4 == 0 && y%100 != 0)
        return 1;
    else return 0;
}

// modulo operator used in gaussCalendar()
int r(int y, int m){
    return y%m;
}

// uses the Gauss Calendar Formula
int gaussCalendar (int a){
    return r(1+5*r(a-1,4)+4*r(a-1,100)+6*r(a-1,400),7);
}


// determines the total number of days within a month
int daysOfMonth (int year, int month){
    switch (month)
    {
    case 1: case 3:
    case 5: case 7:
    case 8: case 10: 
    case 12:
        return 31;
        break;
    
    case 4: case 6:
    case 9: case 11:
        return 30;

    case 2:
        if (isLeapYear(year))
            return 29;
        else return 28;
        break;

    default:
        return -1;
        break;
    }
}

// returns the day of the year
int countingDays (int year, int month, int day){
    int i, days=0;

    // loops month-1 times, add the total number of days per month to counter
    for (i=1; i<=12; i++){
        if (i==month)
            break;
        days += daysOfMonth(year, i);
    }

    // loops all the days in month until the input day is reached, increments counter
    // returns the total number of days if i reaches 'day'
    for (i=1; i<=daysOfMonth(year, month); i++){
        days++;
        if (i==day)
            return days;
    }

    return -1;
}

// calculates the day of week of the inputted day
// returns 0-6, uses array in main()
int whichDayOfWeek (int days, int janOne) {
    return r(days+janOne-1, 7);
}


// figure out the suffix of the number of days
// e.g. 1st, 42nd, 13th
// returns 0-3, uses array in main()
int suffix (int days){
    if (days%10==1 && days%100!=11)
        return 0;
    else if (days%10==2 && days%100!=12)
        return 1;
    else if (days%10==3 && days%100!=13)
        return 2;
    else return 3;
}

// checks the validity of entered date
int isValidDate(int input[]){
    if (input[1] < 1 || input[1] > 12)
        return 0;
    else if (input[2] < 1 || input[2] > daysOfMonth(input[0], input[1]))
        return 0;
    else if (input[0] < 1)
        return 0;
    else return 1;
}
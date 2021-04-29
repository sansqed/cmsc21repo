#include<stdio.h>
#include<time.h>

struct Instant {
    int seconds; // seconds from Unix epoch
};
typedef struct Instant Instant;

struct Date {
    int year;
    int month;
    int day;
};
typedef struct Date Date;

struct Time {
    int hour;
    int minute;
    int second;
};
typedef struct Time Time;

int daysAfterEpoch(Instant instant);        // returns the number of whole days represented by the Instant since the Unix epoch.
Date addDaysToEpoch(int days);              // returns the Date that is days days away from the Unix epoch. Don't forget about leap years.
Time calculateTime(Instant instant);        // returns the time portion represented by the Instant since the Unix epoch.
void Instant_display(Instant instant);      // prints out the date and time represented by the Instant in the ISO 8601 format: <year>-<month>-<day>T<hour>:<minute>:<second>Z (ex. 2021-03-30T12:01:31Z to represent 12:01:31 PM of March 30, 2021 UTC)

void printTime (Time t);
void printDate (Date d);
int isLeapYear (int y);

int main(){

    Instant inst;

    inst.seconds = (unsigned long)time(NULL);
    // inst.seconds = 1609372800;

    // scanf("%d", &inst.seconds);
    printf("\nUnix time: %d \n\n", inst.seconds);

    int days = daysAfterEpoch(inst);
    printf("Days after epoch: %d\n\n", days);

    Date d = addDaysToEpoch(days);
    printDate(d);

    printf("\n\n");

    Time t = calculateTime(inst);
    printTime(t);

    printf("\n\n");

    Instant_display(inst);

    return 0;
}

// returns the number of whole days represented by the Instant since the Unix epoch.
int daysAfterEpoch(Instant instant){
    return instant.seconds/86400;
}

// returns the Date that is days days away from the Unix epoch. Don't forget about leap years.
Date addDaysToEpoch(int days){
    Date d;
    d.year = 1970;
    d.month = 1;
    d.day = 1;

    int lessThanAYear = 0;
    int leapYearFlag;

    // determine year
    while(!lessThanAYear){
        leapYearFlag = isLeapYear(d.year);
        
        if (!leapYearFlag && days < 365)
            lessThanAYear = 1;
        else if (leapYearFlag && days < 366)
            lessThanAYear = 1;
        else if (leapYearFlag){
            days -= 366;
            d.year++;
        }
        else {
            days -= 365;
            d.year++;
        }
        
    }

    // determine month
    int lessThanAMonth = 0;
    while(!lessThanAMonth){
        switch(d.month){
            case 2:                                 // feb
                if (leapYearFlag){
                    if (days < 29)
                        lessThanAMonth = 1;
                    else 
                        days -= 29;
                }
                else {
                    if (days < 28)
                        lessThanAMonth = 1;
                    else 
                        days -= 28;
                }

                break;

            case 4: case 6: case 9: case 11:        // apr, jun, sept, nov
                if (days < 30)
                    lessThanAMonth = 1;
                else 
                    days -= 30;

                break;

            default:                                // jan, mar, may, jul, aug, oct, dec
                if (days < 31)
                    lessThanAMonth = 1;
                else 
                    days -= 31;
                break;
        }

        if (!lessThanAMonth)
            d.month++;
    }

    // determine day
    d.day += days;

    return d;
}

// returns the time portion represented by the Instant since the Unix epoch.
Time calculateTime(Instant instant){
    int temp = instant.seconds%86400;
    Time t;

    t.hour = temp/3600;
    temp -= t.hour*3600;

    t.minute = temp/60;
    temp -= t.minute*60;

    t.second = temp;

    return t;
    
}

// prints out the date and time represented by the Instant in the ISO 8601 format: <year>-<month>-<day>T<hour>:<minute>:<second>Z 
// (ex. 2021-03-30T12:01:31Z to represent 12:01:31 PM of March 30, 2021 UTC)
void Instant_display(Instant instant){
    Time t = calculateTime(instant);
    Date d = addDaysToEpoch(daysAfterEpoch(instant));

    // ternary operators and %c are used to maintain 2 digit values (e.g. '01' instead of '1')
    //      false statement in ternary (0) is NULL in ASCII
    printf("%d-%02d-%02dT%02d:%02d:%02dZ", d.year, d.month, d.day, t.hour, t.minute, t.second);
    return;
}

void printTime (Time t){
    printf("%d:%d:%d", t.hour, t.minute, t.second);

    return;
}

void printDate (Date d){
    printf("%d-%d-%d", d.year, d.month, d.day);

    return;
}

int isLeapYear (int y){
    if (y%400 == 0)
        return 1;
    else if (y%4 == 0 && y%100 != 0)
        return 1;

    return 0;
}
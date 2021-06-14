/*
Author: Alwyn Dy
Date: 2021, March 4
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Date{
    int year, month, day;
};
typedef struct Date Date;

Date getDate();
int getZodSign (Date d);
int isValidDate(Date d);
int *getDistanceFromStart (FILE *fp);
int sumAllLenBeforeIndex(int *distArr, int index);
void writeToFile (FILE *fp, Date d);
int *zodCounter (FILE *fp);

int main(){
    // store names of every zodiac sign
    char zodiacs[12][11] = {"Aquarius", "Pisces", "Aries", "Taurus", "Gemini", "Cancer", 
                            "Leo", "Virgo", "Libra", "Scorpio", "Sagittarius", "Capricorn"};

    Date d = getDate();                             // prompts user to enter birthday

    if (!isValidDate(d)){
        printf("Date not valid.\n");
        return -1;
    }

    int zodSign = getZodSign(d);                    // evaluate the zodiac sign for a given date

    FILE *donefp = fopen("data.in", "ab");          // open file in append binary mode to save inputted date
    if (!donefp)
        return -1;
    

    writeToFile(donefp, d);                         // write date to file
    fclose(donefp);                                 // closes file since writing is done

    donefp = fopen("data.in", "rb");                // open file in read binary mode to read saved data
    if (!donefp)
        return -1;
    
    int *zodCtrArr = zodCounter(donefp);            // evaluates the count for all zod signs evaluated beforehand
    fclose(donefp);                                 // closes file since evaluation is done

    char temp[255];                                 // string to store fortune

    FILE *datafp = fopen("data.for", "rb");         // open file for fortunes
    if (!datafp)
        return -1;
    

    int *distArr = getDistanceFromStart(datafp);    // array that stores the distance of the first char in each line from the start of file

    if (zodCtrArr[zodSign] <= 5){                   // only evaluates if count <= 5
        printf("%s: ", zodiacs[zodSign]);

        // moves file position pointer to the line of the fortune for a zod sign
        // gets the next fortune if a zod sign already asked for fortune
        fseek(datafp, distArr[zodSign +  (12 * (zodCtrArr[zodSign] - 1))], SEEK_SET);

        fgets(temp, 255, datafp);                   // retrieves the fortune for the zod sign, saves to temp
        puts(temp);                                 // prints the fortune for the zod sign
        fclose(datafp);                             // closes file
    }
    else                                            
        printf("Oh no. You're fortune has run out.");


    free (distArr);
    free (zodCtrArr);
    return 0;
}

// prompts user to enter date in the format [yyyy mm dd]
Date getDate(){
    Date d;
    scanf("%d %d %d", &d.year, &d.month, &d.day);
    return d;
}

// identifies the zodiac sign for a given date
// return [0,11]
int getZodSign (Date d){
    switch (d.month){
        case 1: 
            if (d.day >= 20 && d.day <= 31)      return 0;
            else if (d.day > 0 && d.day < 21)    return 11;
            break;
        case 2:
            if (d.day >= 19 && d.day <= 29)      return 1;
            else if (d.day > 0 && d.day < 19)    return 0;
            break;
        case 3: 
            if (d.day >= 21 && d.day <= 31)      return 2;
            else if (d.day > 0 && d.day < 21)    return 1;
            break;
        case 4: 
            if (d.day >= 20 && d.day <= 30)      return 3;
            else if (d.day > 0 && d.day < 20)    return 2;
            break;
        case 5: 
            if (d.day >= 21 && d.day <= 31)      return 4;
            else if (d.day > 0 && d.day < 21)    return 3;
            break;
        case 6: 
            if (d.day >= 21 && d.day <= 30)      return 5;
            else if (d.day > 0 && d.day < 21)    return 4;
            break;
        case 7: 
            if (d.day >= 23 && d.day <= 31)      return 6;
            else if (d.day > 0 && d.day < 23)    return 5;
            break;
        case 8: 
            if (d.day >= 23 && d.day <= 31)      return 7;
            else if (d.day > 0 && d.day < 23)    return 6;
            break;
        case 9: 
            if (d.day >= 23 && d.day <= 30)      return 8;
            else if (d.day > 0 && d.day < 23)    return 7;
            break;
        case 10: 
            if (d.day >= 23 && d.day <= 31)      return 9;
            else if (d.day > 0 && d.day < 23)    return 8;
            break;
        case 11: 
            if (d.day >= 22 && d.day <= 30)      return 10;
            else if (d.day > 0 && d.day < 22)    return 9;
            break;
        case 12: 
            if (d.day >= 22 && d.day <= 31)      return 12;
            else if (d.day > 0 && d.day < 22)    return 11;
            else                                 return -1;
            break;
        default:                                 return -1;
    }
}

// checks if date is valid
// checks d.month if d.day is within bounds of that month
int isValidDate(Date d){
    switch (d.month){
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            if (d.day > 31 || d.day < 1)
                return 0;
            break;
        
        case 4: case 6: case 9: case 11:
            if (d.day > 30 || d.day < 1)
                return 0;

        case 2:
            if ((d.year%4 != 0 || d.year&100 == 0 ) && (d.year%400 != 0))
                if (d.day == 29)
                    return 0;
            break;

        default:
            return 0;
            break;
    }

    return 1;
}

// returns an array that stores the distance of the first character of a line from start of file
int *getDistanceFromStart (FILE *fp){
    int *distArr =  malloc(sizeof *distArr * 60);
    char temp[255];
    distArr[0] = 0;
    for (int i=1; i<60; i++){
        fgets(temp, 255, fp);
        distArr[i] = strlen(temp) + distArr[i-1];
    }

    return distArr;
}

// writes Date d to FILE fp
void writeToFile (FILE *fp, Date d){
    fprintf(fp, "%04d-%02d-%02d\n", d.year, d.month, d.day);
    return;
}

// counts the number of occurence for a given zod sign in the file
// returns an array of size 12
int *zodCounter (FILE *fp){
    Date d;
    int *zodCtrArr = malloc(sizeof *zodCtrArr * 12);

    for (int i=0; i<12; i++)                        // initialize all value in array to 0
        zodCtrArr[i] = 0;

    char temp[10];

    while (fscanf(fp, "%s", &temp) != EOF){         // loops until file-position pointer is at end of file
        char *field = strtok(temp, "-");            // parses the line using the '-' delimeter. separates the year, month, and day

        // converts parsed string to int and stores the year, month, and day to Date d
        // field = strtok(NULL, "-"); is used to move to next field
        d.year = atoi(field);                       
        field = strtok(NULL, "-");

        d.month = atoi(field);
        field = strtok(NULL, "-");

        d.day = atoi(field);
        field = strtok(NULL, "-");

        zodCtrArr[getZodSign(d)]++;                 // increments the zodiac counter if a zodiac is already present in the file
    }

    return zodCtrArr;
}

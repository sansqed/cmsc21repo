/*
Author: Alwyn Dy
Date: 2021, Apr 12
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>

struct Student{
    char studNum[15];                // hyphenated
    char lastName[15], firstName[15];
    char course[15];
    int yrLevel;
    int age;
    char sex;                       // M or F
    int finalGrade;                 // (0 - 100, 60 passing)

    struct Student *next;
};
typedef struct Student Student;

struct SRecord{
    Student *head;
    Student *tail;
    int size;
};
typedef struct SRecord SRecord;

void menu ();
void printStudent (Student *s, int mode);

Student *initStudent ();
void initRecord (SRecord *record);
int enrolStudent (SRecord *record, Student *s);
void insertStudent(SRecord *record, Student *s, int index);
void dropStudent (SRecord *record, int index);
void editStudent (SRecord *record, int index, int fieldToEdit);
void displayAllStudents (SRecord record);
void filterStudents (SRecord *record, int mode, char *detailToMatch);
void sortRecord (SRecord *record, int mode);

int strCmpLower (char *str1, char *str2);
int isStrSimilar (char *str1, char *str2);
int getStudentIndex (SRecord record, char *studNum);
Student *getStudent (SRecord *record,int index);
int isValidStudNum (char *str);


int main(){
    SRecord record;
    Student *s;
    int index;
    char tempStr[15];

    initRecord(&record);

    int choice, choice2;
    while (1){
        system("cls");                                  // clears the screen of the terminal
        menu();
        printf("\nSelect an option: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:                                     // enroll student
                printf("\n");
                s = initStudent();

                // makes sure student number isn't duplicated
                if (getStudentIndex(record, s->studNum) == -1)
                    enrolStudent(&record, s);
                else 
                    printf("\nError! Student with the same student number already exists.\n Student not enrolled.\n\n");
                break;

            case 2:                                     // drop student
                printf("\nDrop\n");
                printf("Enter student number: ");
                scanf("%s", &tempStr);

                printf("Dropping student...\n");

                if (isValidStudNum(tempStr)){                       
                    index = getStudentIndex(record, tempStr);

                    if (index != -1){
                        dropStudent(&record, index);
                        printf("Student Dropped.\n\n");

                    }
                    else {
                        printf("Student not found.\n\n");
                    }
                }
                else 
                    printf("Student number not valid.\n\n");
                break;
            
            case 3:                                     // edit student
                printf("\nEdit\n");
                printf("Enter student number: ");
                scanf("%s", &tempStr);
                if (isValidStudNum(tempStr)){
                    index = getStudentIndex(record, tempStr);
                    if (index != -1){
                        s = getStudent(&record, index);

                        do {
                            printStudent(s, 1);

                            printf("Select an option: ");
                            scanf("%d", &choice2);
                            
                            printf("\n");
                            editStudent(&record, index, choice2);

                        }while (choice2 != 9);                         
                    }
                    else 
                        printf("Student not found.\n\n");
                }
                else    
                    printf("Student number not valid\n\n");            
                break;

            case 4:                                     // display all students
                if (record.size != 0)
                    displayAllStudents(record);
                else 
                    printf("No students in the record.\n");
                break;
            
            case 5:                                     // filter by last name
                printf("Enter a last name: ");
                scanf("%s", &tempStr);

                filterStudents(&record,0,tempStr);             
                break;

            case 6:                                     // filter by student number
                printf("Enter a student number: ");
                scanf("%s", &tempStr);

                if (isValidStudNum(tempStr))
                    filterStudents(&record,1,tempStr);
                
                else 
                    printf("\nStudent number not valid.\n");                
                break;

            case 7:                                     // filter by year level
                printf("Enter a year level: ");
                scanf("%d", &index);

                if (index >= 1 && index <= 5){
                    itoa(index, tempStr, 10);
                    filterStudents(&record, 2, tempStr);
                }
                else 
                    printf("\nYear level not valid.\n");
                break;

            case 8:                                     // filter by course
                printf("Enter a course: ");
                scanf("%s", &tempStr);

                filterStudents(&record, 3, tempStr);
                break;

            case 9:                                     // filter by sex
                printf("Enter a sex: ");
                scanf("%c", &tempStr[0]);
                scanf("%c", &tempStr[0]);
                tempStr[0] = toupper(tempStr[0]);

                filterStudents(&record, 4, tempStr);
                break;

            case 10:                                    // filter passing
                filterStudents(&record, 5, "");                
                break;

            case 11:                                    // filter failing
                filterStudents(&record, 6, "");                
                break;

            case 12:                                    // sort by last name
                if (record.size != 0){
                    sortRecord(&record, 0);
                    sortRecord(&record, 2);
                    displayAllStudents(record);
                }
                else 
                    printf("No students in the record.\n");
                break;

            case 13:                                    // sort by student number
                if (record.size != 0){
                    sortRecord(&record, 1);
                    displayAllStudents(record);
                }
                else 
                    printf("No students in the record.\n");
                break;
        
            case 14:                                    // exit
                return 0;
                break;
        }

        system("pause");    // prompts user to enter any key to continue, used to pause the program
        
    }
    return 0;
}

// display menu
void menu (){
    printf("STUDENT INFORMATION SYSTEM\n\n");
    printf("1. Enrol a student\n");
    printf("2. Drop a student\n");
    printf("3. Edit a student\n");
    printf("4. Display all students\n");
    printf("5. Filter students by last name\n");
    printf("6. Filter students by student number\n");
    printf("7. Filter students by year level\n");
    printf("8. Filter students by course\n");
    printf("9. Filter students by sex\n");
    printf("10. Filter students by passing\n");
    printf("11. Filter students by failing\n");
    printf("12. Sort students by last name\n");
    printf("13. Sort students by student number\n");
    printf("14. Exit\n");

    return;
}

// initializre record
// values will be zero
void initRecord (SRecord *record){
    record->head = 0;
    record->tail = 0;
    record->size = 0;
    return;
}

// prompts user to input student details
Student *initStudent (){
    Student *s = (Student*) malloc(sizeof(Student));        // creates a student in the heap
    char temp[15];

    printf("Enrol\n");

    do {                                            // ensures student number is valid (only contains numbers and hyphens)
        printf("Student number: ");
        scanf("%s", &temp);
    } while (!isValidStudNum(temp));
    strcpy(s->studNum, temp);

    do {                                            // ensures last name has at most 15 characters 
        printf("Last Name: ");
        scanf("%s", &temp);
    } while (strlen(temp) > 15);
    strcpy(s->lastName, temp);
    
    do {                                            // ensures first name has at most 15 characters
        printf("First Name: ");
        scanf("%s", &temp);
    } while (strlen(temp) > 15);
    strcpy(s->firstName, temp);

    do {                                            // ensures course has at most 15 characters
        printf("Course: ");
        scanf("%s", &temp);
    } while (strlen(temp) > 15);
    strcpy(s->course, temp);

    
    printf("Year level: ");                         // prompts the yr level
    scanf("%d", &s->yrLevel);
    

    do {                                            // ensures valid age
        printf("Age: ");
        scanf("%d", &s->age);
    } while (s->age < 0);
                           
    do {                                            // ensures sex is either M or F
        printf("Sex: ");
        scanf("%c", &s->sex);
        scanf("%c", &s->sex);
        s->sex = toupper(s->sex);
    } while (s->sex != 'M' && s->sex != 'F');

    do {                                            // ensures final grade is within [0,100]
        printf("Final Grade: ");
        scanf("%d", &s->finalGrade);
    } while (s->finalGrade < 0 || s->finalGrade > 100);

    s->next = 0;
    
    return s;
}

// places the student at the end of the record
int enrolStudent (SRecord *record, Student *s){
    insertStudent(record, s, record->size);
    record->size++;
    return record->size;
}

// inserts student in the record
void insertStudent(SRecord *record, Student *s, int index){
    if (index >= 0 && index <= record->size){                   // checks validity of index
        if (index == 0){                                        // insert at head
            s->next = record->head;
            record->head = s;
        }

        if (index == record->size){                             // insert at tail
            if (record->tail != 0)
                record->tail->next = s;
            record->tail = s;
        }

        if (index > 0 && index < record->size){                 // insert at !head and !tail
            Student *prev = getStudent(record, index-1);
            s->next = prev->next;
            prev->next = s;
        }
    }

    return;
}

// drops student from the record
// int index is the index of the student to be dropped
// adjusts the record to remove the student
// frees the memory allocated for that student
void dropStudent (SRecord *record, int index){
    Student *toDrop = record->head;

    if (index >= 0 && index < record->size){
        Student *toDrop;

        if (index==0){                                          // if student is found at the head of the record
            toDrop = record->head;
            record->head = toDrop->next;
        }
        else  {                                                 // if student is not in the head
            Student *previous = getStudent(record, index-1);
            toDrop = previous->next;
            previous->next = toDrop->next;

            if (index == record->size-1)
                record->tail = previous;
        }

        free(toDrop);
        record->size--;
    }
    
    return;
}

// edit student information
// fieldToEdit accepts an int 1-8, corresponding to student information
void editStudent (SRecord *record, int index, int fieldToEdit){

    Student *s = getStudent(record, index);
    char temp[15];
    int tempInt;
    char tempChar;

    switch(fieldToEdit){
        case 1:                                                     // student number
            printf("Student number (%s): ", s->studNum);
            scanf("%s", &temp);

            if (isValidStudNum(temp))
                strcpy(s->studNum, temp);
            else 
                printf("Error! Invalid student number.\n");
            break;
        case 2:                                                     // last name
            printf("Last name (%s): ", s->lastName);
            scanf("%s", &temp);

            if (strlen(temp) <= 15)
                strcpy(s->lastName, temp);
            else
                printf("Error! Invalid last name.\n");
            break;

        case 3:                                                     // first name
            printf("First name (%s): ", s->firstName);
            scanf("%s", &temp);

            if (strlen(temp) <= 15)
                strcpy(s->firstName, temp);
            else
                printf("Error! Invalid first name.\n");
            break;

        case 4:                                                     // course
            printf("Course (%s): ", s->course);
            scanf("%s", &temp);

            if (strlen(temp) <= 15)
                strcpy(s->course, temp);
            else
                printf("Error! Invalid course.\n");
            break;

        case 5:                                                     // year level
            printf("Year level (%d): ", s->yrLevel);
            scanf("%d", &s->yrLevel);
            
            // printf("Error! Invalid year level.\n");
            break;

        case 6:                                                     // age
            printf("Age (%d): ", s->age);
            scanf("%d", &s->age);
            break;

        case 7:                                                     // sex
            printf("Sex (%c): ", s->sex);
            scanf("%c", &tempChar);
            scanf("%c", &tempChar);
            tempChar = toupper(tempChar);

            if (tempChar == 'M' || tempChar == 'F')
                s->sex = tempChar;
            else 
                printf("Error! Invalid sex.\n");
            break;          
        case 8:                                                     // final grade
            printf("Final Grade (%d): ", s->finalGrade);
            scanf("%d", &tempInt);

            if (tempInt >= 0 && tempInt <= 100)
                s->finalGrade = tempInt;
            else
                printf("Error! Invalid final grade.\n");
            break;

    }


    return;
}

// display all students in the record
void displayAllStudents (SRecord record){
    Student *current = record.head;

    for (int i=0; i<record.size; i++){
        printf("\n----------\n\n");
        printStudent(current, 0);
        current = current->next;
    }
    printf("\n----------\n");

    return;
}

// filter students in the record depending on int mode
// int mode accepts 0-6
// detailToMatch is the detail needed for filtering
void filterStudents (SRecord *record, int mode, char *detailToMatch){
    int flag, flag2=0;
    Student *current = record->head;

    for (int i=0; i<record->size; i++){
        flag=0;
       
        switch (mode){
            case 0:                             // last name
                if (strCmpLower(current->lastName, detailToMatch) == 0)
                    flag=1;              
                break;

            case 1:                             // student number
                if (isStrSimilar(current->studNum, detailToMatch) == 1)
                    flag=1;
                break;

            case 2:                             // year level
                if (atoi(detailToMatch) == current->yrLevel)
                    flag=1;
                break;

            case 3:                             // course
                if (strCmpLower(current->course, detailToMatch) == 0)
                    flag=1;
                break;

            case 4:                             // sex
                if (detailToMatch[0] == current->sex)
                    flag=1;
                break;

            case 5:                             // passing
                if (current->finalGrade >= 60)
                    flag=1;
                break;

            case 6:                             // failing
                if (current->finalGrade < 60)
                    flag=1;
                break;
        }
        
        if (flag == 1){
            printf("\n----------\n\n");
            printStudent(current,0);
            flag2 = 1;
        }

        current = current->next;
    }
        if (flag2 == 1)
            printf("\n----------\n");
        else 
            printf("\nNo student found.\n");
    return;

}

// sorts the record depending on mode
// mode accepts 0-3
void sortRecord (SRecord *record, int mode){
    Student *prev;
    Student *current;
    Student *toChange;
    int j, flag;

    for (int i=1; i< record->size; i++){

        prev = getStudent(record, i-1);
        current = prev->next;

        flag = -1;

        switch(mode){
            // last name
            case 0:
                if (strCmpLower(prev->lastName, current->lastName) == 1){            // detect unsorted
                    toChange = record->head;

                    // find insert index to make list more sorted
                    for (j=0; j<=i; j++){
                        // if 'current' should be inserted in head
                        if (strCmpLower(toChange->lastName, current->lastName) == 1){
                            flag=0;
                            break;
                        }

                        // otherwise
                        else if (strCmpLower(toChange->next->lastName, current->lastName) == 1){
                            flag=1;
                            break;
                        }

                        
                        toChange = toChange->next;
                    }                    
                }
                

                break;

            // student number
            case 1:
                if (strcmp(prev->studNum, current->studNum) == 1){            // detect unsorted
                    toChange = record->head;

                    // find insert index to make list more sorted
                    for (j=0; j<=i; j++){
                        // if 'current' should be inserted in head
                        if (strcmp(toChange->studNum, current->studNum) == 1){
                            flag=0;
                            break;
                        }

                        // otherwise
                        else if (strcmp(toChange->next->studNum, current->studNum) == 1){
                            flag=1;
                            break;
                        }

                        toChange = toChange->next;
                    }                    
                }

                break;

            // sorts by first name of multiple last name exists
            case 2:
                if (strCmpLower(prev->lastName, current->lastName) == 0){            // detect unsorted
                    toChange = record->head;

                    // find insert index to make list more sorted
                    for (j=0; j<i; j++){
                        // if 'current' should be inserted in head
                        if (strCmpLower(toChange->lastName, current->lastName) == 0 && strCmpLower(toChange->firstName, current->firstName) == 1){
                            flag=0;
                            break;
                        }

                        // otherwise
                        else if (strCmpLower(toChange->next->lastName, current->lastName) == 0 && strCmpLower(toChange->next->firstName, current->firstName) == 1){
                            flag=1;
                            break;
                        }

                        if (toChange->next != 0)
                            toChange = toChange->next;
                    }                    

                    // printf("|%d|\n", flag);
                }
                break;

        }

        if (flag==1 || flag==0){
            // temporarily remove current from list
            if (current == record->tail){
                record->tail = prev;
                prev->next = 0;
            }
            else 
                prev->next = current->next;

            // insert item to proper location
            if (flag==0){
                current->next = toChange;
                record->head = current;
            }
            else if (flag==1){
                current->next = toChange->next;
                toChange->next = current;
            }
        }


        prev = current;
        current = current->next;
    }


    return;
}

// returns student index based on student number
// returns -1 if student not in record
int getStudentIndex (SRecord record, char *studNum){
    Student *current = record.head;

    if (isValidStudNum(studNum) == 1){
        int i;
        for (i=0; i<record.size; i++){
            if (isStrSimilar(studNum, current->studNum))
                return i;
            current = current->next;
        }

        return -1;
    }
}

// gets student based on index in the record
Student *getStudent (SRecord *record,int index){
    Student *current = record->head;
    if (index >= 0 && index < record->size){
        for (int i=0; i < index; i++){
            current = current->next;
        }
        return current;
    }
}

// valid student number must contain only numbers and hyphen
int isValidStudNum (char *str){
    int flag=0;

    for (int i=0; str[i]!='\0'; i++){
        if (str[i] == 45)
            flag = 1;
        if ((str[i]<48 || str[i]>57) && str[i]!= 45)
            return 0;
    }

    return 1*flag;
}

// compares if str1 and str1 are similar
int isStrSimilar (char *str1, char *str2){
    if (strlen(str1) == strlen(str2)){
        int len = strlen(str1);
        for (int i=0; i<len; i++){
            if (str1[i] != str2[i])
                return 0;
        }
        return 1;
    }
    return 0;
}

// compares the lowercase version of str1 and str2
// similar to strcmp
// returns 1 if str1 > str2
// returns -1 if str1 < str2
// returns 0 if str1 == str2
int strCmpLower (char *str1, char *str2){

    for (int i=0; str1[i] != '\0' || str2[i]!='\0'; i++){
        if (tolower(str1[i]) > tolower(str2[i]))
            return 1;
        else if (tolower(str1[i]) < tolower(str2[i]))
            return -1;
    }

    return 0;   
}

// prints student info
// 2 modes: 
//      mode 0 -> print specific student info
//      mode 1 -> prints editable student info
void printStudent (Student *s, int mode){
    switch(mode){
        case 0:
            printf("Student number: %s\n", s->studNum);
            printf("Last name: %s\n", s->lastName);
            printf("First name: %s\n", s->firstName);
            printf("Course: %s\n", s->course);
            printf("Year level: %d\n", s->yrLevel);
            printf("Age: %d\n", s->age);
            printf("Sex: %c\n", s->sex);
            printf("Final Grade: %d\n", s->finalGrade);
            break;
        case 1: 
            printf("\nEdit %s \n", s->studNum); 
            printf("1. Student number: \n");
            printf("2. Last name: \n");
            printf("3. First name: \n");
            printf("4. Course: \n");
            printf("5. Year level: \n");
            printf("6. Age: \n");
            printf("7. Sex: \n");
            printf("8. Final Grade: \n");
            printf("9. Back \n");
            break;
    }
    return;
}
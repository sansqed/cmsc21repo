/*
Author: Alwyn Dy
Date: 2021, May 14
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>

struct Student{
    int studNum;                // 1-300
    char lastName[15], firstName[15];
    char course[15];
    int yrLevel;
    int age;
    char sex;                       // M or F
    int finalGrade;                 // (0 - 100, 60 passing)
};
typedef struct Student Student;


void menu ();
void printStudent (Student s, int mode);

Student initStudent ();
void enrolStudent (FILE *fp, Student s);
void dropStudent (FILE *fp, int index);
void editStudent (FILE *fp, Student *s, int fieldToEdit);
void filterStudents (FILE *fp, int mode, char *detailToMatch);
void sortRecord(FILE *fp, int mode);

int strCmpLower (char *str1, char *str2);
void updateFile ();
void copyFromFile (FILE *source, FILE *dest, int from, int to);
int getStudentIndex(FILE *fp, int studNum);
void insert(FILE *fp, int index, int mode);
void displayAllStudents (FILE *fp);

int main(){
    Student s;
    int index, temp, i;
    char tempStr[15];
    FILE *recordfp;
    FILE *recordTempfp;

    int choice, choice2;
    while (1){
        system("cls");                                  // clears the screen of the terminal
        menu();
        printf("\nSelect an option: ");
        scanf("%d", &choice);
        printf("\n");
        switch(choice){
            case 1:                                                                 // enroll student
                recordfp = fopen("record.bin", "a+b");

                s = initStudent();

                // makes sure student number isn't duplicated
                if (getStudentIndex(recordfp, s.studNum) == -1)
                    enrolStudent(recordfp, s);
                else 
                    printf("\nError. Student already exist.\nEnrollment failed.\n\n");

                fclose(recordfp);
                break;

            case 2:                                                                 // drop student
                recordfp = fopen("record.bin", "r+b");

                printf("Drop\n");
                printf("Enter student number: ");
                scanf("%d", &temp);

                if (temp < 1 || temp > 300){
                    printf("Error! Student number not valid\n");
                    fclose(recordfp);
                    break;
                }

                index = getStudentIndex(recordfp, temp);

                if (index == -1){
                    printf("Error! Student does not exist.\n");
                    fclose(recordfp);
                    break;
                }
                
                dropStudent(recordfp, index);
                printf("Student dropped successfully\n");


                break;

            case 3:                                                                 // edit student
                recordfp = fopen("record.bin", "r+b");

                printf("Edit\n");
                printf("Enter student number: ");
                scanf("%d", &temp);

                if (temp < 1 || temp > 300){                                // check if entered studNum is valid
                    printf("Error! Student number not valid\n");
                    break;
                }


                index = getStudentIndex(recordfp, temp);                    // get student index in record
                if (index == -1){                                           // check if student exist
                    printf("Error! Student does not exist.\n");
                    break;
                }
                
                
                fseek(recordfp, sizeof(Student)*index, SEEK_SET);
                fread(&s, sizeof(Student), 1, recordfp);                    // get student

                do {
                    printStudent(s, 1);
                    printf("Select an option: ");
                    scanf("%d", &choice2);

                    printf("\n");
                    editStudent(recordfp, &s, choice2);

                } while (choice2 != 9);

                fseek(recordfp, sizeof(Student)*index, SEEK_SET);
                fwrite(&s, sizeof(Student), 1, recordfp);
                fclose(recordfp);
                break;

            case 4:                                                                 // display all students
                recordfp = fopen("record.bin", "rb");
                displayAllStudents(recordfp);
                fclose(recordfp);
                break;

            case 5:                                                                 // filter by last name
                recordfp = fopen("record.bin", "rb");
                printf("Enter a last name: ");
                scanf("%s", &tempStr);

                printf("Students with the last name of: %s\n", tempStr);
                filterStudents(recordfp,0,tempStr);  
                fclose(recordfp);
                break;

            case 6:                                                                 // filter by student number
                recordfp = fopen("record.bin", "rb");
                printf("Enter a student number: ");
                scanf("%d", &temp);

                if (temp >= 1 && temp <= 300){
                    printf("Students with a student number of: %d\n", temp);
                    itoa(temp, tempStr, 10);
                    filterStudents(recordfp,1,tempStr);  
                }
                else 
                    printf("Error! Invalid student number.\n");

                fclose(recordfp);
                break;

            case 7:                                                                 // filter by yr level
                recordfp = fopen("record.bin", "rb");
                printf("Enter a year level: ");
                scanf("%d", &temp);

                printf("Students with a year level of: %d\n", temp);
                itoa(temp, tempStr, 10);
                filterStudents(recordfp,2,tempStr);  

                fclose(recordfp);
                break;

            case 8:                                                                 // filter by course
                recordfp = fopen("record.bin", "rb");
                scanf("%s", &tempStr);

                printf("Students with a course of: %s\n", tempStr);
                filterStudents(recordfp, 3, tempStr);
                fclose(recordfp);
                break;

            case 9:                                                                 // filter by sex
                recordfp = fopen("record.bin", "rb");
                printf("Enter a sex: ");
                scanf(" %c", &tempStr[0]);
                tempStr[0] = toupper(tempStr[0]);
                
                printf("Students with a sex of: %c\n", tempStr[0]);
                filterStudents(recordfp, 4, tempStr);
                fclose(recordfp);
                break;

            case 10:                                                                // filter passing
                recordfp = fopen("record.bin", "rb");
                printf("Students with passing grades:\n");
                filterStudents(recordfp, 5, "");                
                fclose(recordfp);
                break;

            case 11:                                                                // filter failing
                recordfp = fopen("record.bin", "rb");
                printf("Students with failing grades:\n");
                filterStudents(recordfp, 6, "");                
                fclose(recordfp);
                break;

            case 12:                                                                // sort by last name
                recordfp = fopen("record.bin", "r+b");
                printf("Sorting students by last name...\n");
                sortRecord(recordfp, 0);
                sortRecord(recordfp, 2);
                displayAllStudents(recordfp);
                fclose(recordfp);
                break;

            case 13:                                                                // sort by student number
                recordfp = fopen("record.bin", "r+b");
                printf("Sorting students by student number...\n");
                sortRecord(recordfp, 1);
                displayAllStudents(recordfp);
                fclose(recordfp);
                break;

            case 14:                                                                // exit
                exit(1);
                break;

            case 15:                                                                // special code for clearing record.bin
                recordfp = fopen("record.bin", "wb");
                fprintf(recordfp, "\0");
                fclose(recordfp);
                break;
        }

        system("pause");    // prompts user to enter any key to continue, used to pause the program
        
    }
    return 0;
}

// display menu
void menu (){
    printf("STUDENT INFORMATION SYSTEM 2\n\n");
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

// prompts user to input student details
Student initStudent (){
    Student s;        // creates a student in the heap
    char temp[15];

    printf("Enrol\n");

    do {                                            // ensures student number is valid 
        printf("Student number: ");
        scanf("%i", &s.studNum);
    } while (s.studNum < 1 || s.studNum > 300);

    do {                                            // ensures last name has at most 15 characters 
        printf("Last Name: ");
        scanf("%s", &temp);
    } while (strlen(temp) > 15);
    strcpy(s.lastName, temp);
    
    do {                                            // ensures first name has at most 15 characters
        printf("First Name: ");
        scanf("%s", &temp);
    } while (strlen(temp) > 15);
    strcpy(s.firstName, temp);

    do {                                            // ensures course has at most 15 characters
        printf("Course: ");
        scanf("%s", &temp);
    } while (strlen(temp) > 15);
    strcpy(s.course, temp);

    
    printf("Year level: ");                         // prompts the yr level
    scanf("%d", &s.yrLevel);
    

    do {                                            // ensures valid age
        printf("Age: ");
        scanf("%d", &s.age);
    } while (s.age < 0);
                           
    do {                                            // ensures sex is either M or F
        printf("Sex: ");
        scanf("%c", &s.sex);
        scanf("%c", &s.sex);
        s.sex = toupper(s.sex);
    } while (s.sex != 'M' && s.sex != 'F');

    do {                                            // ensures final grade is within [0,100]
        printf("Final Grade: ");
        scanf("%d", &s.finalGrade);
    } while (s.finalGrade < 0 || s.finalGrade > 100);
    
    return s;
}

// places the student at the end of the record
void enrolStudent (FILE *fp, Student s){
    fseek(fp, 0, SEEK_END);
    fwrite(&s, sizeof(Student), 1, fp);
    return;
}

// removes student from record
void dropStudent (FILE *fp, int index){
    rewind(fp);

    FILE *newRecord = fopen("recordtemp.bin", "wb");        // create a temporary file to store students not dropped

    copyFromFile(fp, newRecord, 0, index);                  // copy all students BEFORE studentToDrop

    copyFromFile(fp, newRecord, index+1, -1);               // copy all students AFTER studentToDrop
    
    fclose(newRecord);                                      // updates the file
    fclose(fp);
    updateFile();
    return;
}

// edit student information
// fieldToEdit accepts an int 1-8, corresponding to student information
void editStudent (FILE *fp, Student *s, int fieldToEdit){
    int tempInt;
    char tempStr[15], tempChar;

    switch(fieldToEdit){
        case 1:                                                     // student number
            printf("Student number (%d): ", s->studNum);
            scanf("%d", &tempInt);

            if (tempInt >= 1 && tempInt <= 300)
                if (getStudentIndex(fp, tempInt) == -1)
                    s->studNum = tempInt;
                else 
                    printf("Error! Student number already taken.\n");
            else 
                printf("Error! Invalid student number.\n");
            break;

        case 2:                                                     // last name
            printf("Last name (%s): ", s->lastName);
            scanf("%s", &tempStr);

            if (strlen(tempStr) <= 15)
                strcpy(s->lastName, tempStr);
            else
                printf("Error! Invalid last name.\n");
            break;

        case 3:                                                     // first name
            printf("First name (%s): ", s->firstName);
            scanf("%s", &tempStr);

            if (strlen(tempStr) <= 15)
                strcpy(s->firstName, tempStr);
            else
                printf("Error! Invalid first name.\n");
            break;

        case 4:                                                     // course
            printf("Course (%s): ", s->course);
            scanf("%s", &tempStr);

            if (strlen(tempStr) <= 15)
                strcpy(s->course, tempStr);
            else
                printf("Error! Invalid course.\n");
            break;
        
        case 5:                                                     // year level
            printf("Year level (%d): ", s->yrLevel);
            scanf("%d", &s->yrLevel);
            break;

        case 6:                                                     // age
            printf("Age (%d): ", s->age);
            scanf("%d", &s->age);
            break;

        case 7:                                                     // sex
            printf("Sex (%c): ", s->sex);
            scanf(" %c", &tempChar);
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
void displayAllStudents (FILE *fp){
    Student s;
    rewind(fp);
    while (fread(&s, sizeof(Student), 1, fp) && !feof(fp)){
        // if (s.studNum !=0)
        printf("\n----------------------------\n\n");
        printStudent(s, 0);
    }

    printf("\n----------------------------\n");

    return;
}

// filter students in the record depending on int mode
// int mode accepts 0-6
// detailToMatch is the detail needed for filtering
void filterStudents (FILE *fp, int mode, char *detailToMatch){
    int flag, flag2=0;
    Student s;

    rewind(fp);
    while (fread(&s, sizeof(Student), 1, fp) && !feof(fp)){
        flag = 0;
        switch(mode){
            case 0:                             // last name
                if (strCmpLower(s.lastName, detailToMatch) == 0)
                    flag=1;              
                break;

            case 1:                             // year level
                if (atoi(detailToMatch) == s.studNum)
                    flag=1;
                break;

            case 2:
                if (atoi(detailToMatch) == s.yrLevel)
                    flag=1;
                break;
            
            case 3:                             // course
                if (strCmpLower(s.course, detailToMatch) == 0)
                    flag=1;
                break;
            
            case 4:                             // sex
                if (detailToMatch[0] == s.sex)
                    flag=1;
                break;

            case 5:                             // passing
                if (s.finalGrade >= 60)
                    flag=1;
                break;

            case 6:                             // failing
                if (s.finalGrade < 60)
                    flag=1;
                break;
        }

        if (flag == 1){
            printf("\n----------\n\n");
            printStudent(s,0);
            flag2 = 1;
        }
    }

    if (flag2 == 1)
        printf("\n----------\n");
    else 
        printf("\nNo student found.\n");
    return;

}

// sort record depending on int mode
// utilizies insertion sort algorithm
//      mode 0: sort by last name
//      mode 1: sort by student number
//      mode 2: sort by first name if last name is similar
void sortRecord(FILE *fp, int mode){
    Student sPrev, sCur;
    fseek(fp, 0, SEEK_END);
    int numberOfStudents = ftell(fp) / sizeof(Student);                 // gets total number of students in the record.bin

    rewind(fp);
    for (int i=1; i<numberOfStudents; i++){
        // gets prev and current student
        fseek(fp, sizeof(Student)*(i-1), SEEK_SET);
        fread(&sPrev, sizeof(Student), 1, fp);
        fseek(fp, sizeof(Student)*i, SEEK_SET);
        fread(&sCur, sizeof(Student), 1, fp);

        // compares the current and previous student based on mode
        // if unordered, calls insert()
        if (mode == 0){
            if (strCmpLower(sCur.lastName, sPrev.lastName) == -1)
                insert(fp, i, mode);
        }
        else if (mode == 1){
            if (sCur.studNum < sPrev.studNum){
                insert(fp, i, mode);
            }
        }
        else if (mode == 2){
            if (strCmpLower(sCur.lastName, sPrev.lastName) == 0)
                if (strCmpLower(sCur.firstName, sPrev.firstName) == -1)
                    insert (fp, i, mode);
        }
    }

    return;
}

// returns the index (not file position) of the student with the student number
int getStudentIndex(FILE *fp, int studNum){
    Student temp;

    rewind(fp);

    int i=0;

    while (fread(&temp, sizeof(Student), 1, fp) && !feof(fp)){
        if (temp.studNum == studNum)
            return i;
        
        i++;
    }

    return -1;
}

// copies student from the source file with the boundary int from and int to (won't include int to) to the destination file
void copyFromFile (FILE *source, FILE *dest, int from, int to){
    Student temp;

    fseek(source, sizeof(Student)*from, SEEK_SET);

    int i=from;
    while (fread(&temp, sizeof(Student), 1, source) && !feof(source)){

        if (i == to)                // signifies end of copying
            return;

        fwrite(&temp, sizeof(Student), 1, dest);
        i++;

    }

    return;
}

// replaces record.bin
void updateFile (){
    remove("record.bin");
    rename("recordtemp.bin", "record.bin");
    return;
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


// insertion sort algorithm
void insert(FILE *fp, int index, int mode){

    Student s, probe;

    // gets the student to be moved
    fseek(fp, sizeof(Student)*index, SEEK_SET);
    fread(&s, sizeof(Student), 1, fp);

    rewind(fp);
    int i;

    // determines correct location to insert Student s
    for (i=0; !feof(fp); i++){

        // Student probe gets student and compares it to Student s
        fseek(fp, sizeof(Student)*i, SEEK_SET);
        fread(&probe, sizeof(Student), 1, fp);

        if (mode == 0){
            if (strCmpLower(s.lastName, probe.lastName) == -1)
                break;
        }
        else if (mode == 1){
            if (s.studNum < probe.studNum)
                break;
        }
        else if (mode == 2){
            if (strCmpLower(s.lastName, probe.lastName) == 0)
                if (strCmpLower(s.firstName, probe.firstName) == -1)
                    break;
        }
    }

    // moves all affected student records to make room for Student s
    for (int j=index-1; j >= i; j--){
        fseek(fp, sizeof(Student)*j, SEEK_SET);
        fread(&probe, sizeof(Student), 1, fp);
        fseek(fp, sizeof(Student)*(j+1), SEEK_SET);
        fwrite(&probe, sizeof(Student), 1, fp);
    }

    // writes Student s to proper location
    fseek(fp, sizeof(Student)*i, SEEK_SET);
    fwrite(&s, sizeof(Student), 1, fp);   

    return;
}

// prints student info
// 2 modes: 
//      mode 0 -> print specific student info
//      mode 1 -> prints editable student info
void printStudent (Student s, int mode){
    switch(mode){
        case 0:
            printf("Student number: %i\n", s.studNum);
            printf("Last name: %s\n", s.lastName);
            printf("First name: %s\n", s.firstName);
            printf("Course: %s\n", s.course);
            printf("Year level: %d\n", s.yrLevel);
            printf("Age: %d\n", s.age);
            printf("Sex: %c\n", s.sex);
            printf("Final Grade: %d\n", s.finalGrade);
            break;
        case 1: 
            printf("\nEdit [%d] \n", s.studNum); 
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
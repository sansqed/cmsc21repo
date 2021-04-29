/*
Author: Alwyn Dy
Date: 2021, Apr 3

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int size;
    int capacity;
    char *str;
} Vector;

void initString(Vector* vecString, char* string);               // accept string, insert string into Vector
void concatenate(Vector* combined, Vector* a, Vector* b);       // concat Vector a & b, put result in Vector combined
void slice(Vector* sliced, Vector* source, int start, int end); // takes a portion of source starting from start and ends at end - 1

void test(char *str);
void initVector(Vector *v);
void printVector (Vector *v);
int strLen (char *str);
void resize (Vector *v, int size);

int main (){

    Vector v, w, x;
    char str[15];
    int temp1, temp2;

    int choice;
    scanf("%d", &choice);

    switch(choice){
        case 1:
            scanf("%s", str);
            if (strLen(str) <= 15)
                initString(&v, str);
            else  break;

            scanf("%s", str);
            if (strLen(str) <= 15)
                initString(&w, str);
            else break;

            concatenate(&x, &v, &w);
            printVector(&x);
            break; 
        case 2:
            scanf("%s", str);
            if (strLen(str) <= 15)
                initString(&v, str);
            else break;

            scanf("%d %d", &temp1, &temp2);

            slice(&w, &v, temp1, temp2);
            printVector(&w);
            break;
    }


    return 0;    
}
void initString(Vector* vecString, char* string){
    initVector(vecString);
    int len = strLen(string);

    if (vecString->capacity < len)
        resize(vecString, len);

    for (int i=0; i < len; i++){
        vecString->str[i] = string[i];
        vecString->size++;
    }

    return;

}

void concatenate(Vector* combined, Vector* a, Vector* b){
    initVector(combined);

    if (combined->capacity < a->size + b->size)
        resize(combined, a->size + b->size);

    for (int i=0; i<a->size; i++){
        combined->str[i] = a->str[i];
        combined->size++;
    }

    for (int i=0; i<b->size; i++){
        combined->str[a->size+i] = b->str[i];
        combined->size++;
    }

    return;
}

void slice(Vector* sliced, Vector* source, int start, int end){
    initVector(sliced);

    if (start > end || start < 0 || end > source->size)
        return;

    if (sliced->capacity < end-start)
        resize(sliced, end-start);

    for (int i=start; i<end; i++){
        sliced->str[i-start] = source->str[i];
        sliced->size++;
    }
    return;
}

void initVector(Vector *v){

    v->size = 0;
    v->capacity = 10;
    v->str = (char*) malloc(sizeof(char) * v->capacity);

    return;
}

void printVector (Vector *v){
    for (int i=0; i<v->size; i++)
        printf("%c", v->str[i]);
    return;
}

// accepts Vector v and size >= -1
// if size == -1, double the size of v
// else, make size of v = size
void resize (Vector *v, int size){
    int newCapacity;

    if (size == -1)
        newCapacity = 2 * v->size;
    else 
        newCapacity = size;    
    

    char *newStr = (char*) malloc (sizeof(char) * newCapacity);

    for (int i=0; i < v->size; i++){
        newStr[i] = v->str[i];
    }

    v->capacity = newCapacity;
    free(v->str);
    v->str = newStr;

    return;
}

int strLen (char *str){
    int i;
    for (i=0; str[i]!='\0'; i++);
    return i;
}

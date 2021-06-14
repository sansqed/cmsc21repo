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

void insertItem (Vector *v, int index, char character);
char getItem (Vector *v, int index);

void initVector(Vector *v);
void printVector (Vector *v);
int strLen (char *str);
void resize (Vector *v);

int main (){

    Vector v, w, x;
    char str[15];
    int temp1, temp2;

    int choice;
    scanf("%d", &choice);

    switch(choice){
        case 1:
            scanf("%s", str);
            initString(&v, str);

            scanf("%s", str);
            initString(&w, str);

            concatenate(&x, &v, &w);
            printVector(&x);
            break; 
        case 2:
            scanf("%s", str);
            initString(&v, str);

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

    for (int i=0; i < len && i <= 15; i++)
        insertItem(vecString, i, string[i]);

    return;

}

void concatenate(Vector* combined, Vector* a, Vector* b){
    initVector(combined);
    int i;

    for (i=0; i<a->size; i++)
        insertItem(combined, i, getItem(a, i));
    

    for (; i < b->size + a->size; i++)
        insertItem(combined, i, getItem(b, i - a->size));

    return;
}

void slice(Vector* sliced, Vector* source, int start, int end){
    initVector(sliced);

    if (start > end || start < 0 || end > source->size)
        return;

    for (int i=start; i<end; i++)
        insertItem(sliced, i - start, getItem(source, i));
    
    return;
}

void insertItem (Vector *v, int index, char character){
    if (index >= 0 && index <= v->size){
        if (v->size == v->capacity)
            resize (v);
        
        for (int i=v->size; i > index; i++)
            v->str[i] = v->str[i-1];

        v->str[index] = character;
        v->size++;
    }
    return;
}

char getItem (Vector *v, int index){
    if (index >= 0 && index <= v->size){
        return v->str[index];
    }

    return '\0';
}

void initVector(Vector *v){

    v->size = 0;
    v->capacity = 10;
    v->str = (char*) malloc(sizeof(char) * v->capacity);

    return;
}

void printVector (Vector *v){
    for (int i=0; i<v->size; i++)
        printf("%c", getItem(v, i));
    return;
}

// doubles the size of Vector v
void resize (Vector *v){
    int newCapacity = v->capacity * 2;

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

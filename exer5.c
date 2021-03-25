/*
Author: Alwyn Dy
Date: 2021, March 19
*/


#include<stdio.h>

void insertionSort (int *arr, int size);
void insert (int *arr, int item);
void printArray(const int *arr, int size);

int main() {
    int size;

    scanf("%d", &size);
    int arr[size];

    for (int i=0; i<size; i++){
        scanf("%d", (arr+i));
    }

    insertionSort(arr, size);

    printArray(arr, size);

    return 0;

}

// loops entirety of array
// if unsorted, runs insert()
void insertionSort (int *arr, int size){
    for (int i=1; i<size; i++){
        if (*(arr+i) < *(arr+i-1))
           insert(arr, i);
    }

    return;
}

// inserts item to a certain index in the array to make it sorted
void insert (int *arr, int item){
    int i, j;
    int tempItem = *(arr + item);

    for (i=item-1; i>=0; i--){
        if (*(arr+i) < tempItem)
            break;
    }

    for (j=item; j>=i+1; j--)
        *(arr+j) = *(arr+j-1);
    
    *(arr+i+1) = tempItem;

    return;
}

// prints array
void printArray(const int *arr, int size){

    for (int i=0; i<size; i++)
        printf("%d ", *(arr+i));

    return;
}
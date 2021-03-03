/*
Author: Alwyn Dy
Date: 2021, Mar 2
*/

#include<stdio.h>

int divide(int a, int b);
int gcd(int a, int b);
int isSorted (int arr[], int size, int i);
int binarySearch (int arr[], int n, int l, int r);

int main(){
    int choice, temp1, temp2, i;

    scanf("%d", &choice);

    if (choice == 1){
        scanf("%d %d", &temp1, &temp2);

        if (temp2 != 0)
            printf("%d", divide(temp1, temp2));
    }

    else if (choice == 2){
        scanf("%d %d", &temp1, &temp2);

        // using euclidean algo: if gcd is 1, it is relatively prime
        // if other numbers, not relatively prime
        if (temp1 >=0 && temp2 >=0)
            printf("%d", gcd(temp1, temp2)==1? 1:0);
    }

    else if (choice == 3){

        // temp1 is for size of array
        scanf("%d", &temp1);
        int arr[temp1];

        for (i = 0; i < temp1; i++)
            scanf("%d", &arr[i]);

        // temp2 is the int to search in sorted array
        scanf("%d", &temp2);

        // error check if arr[] is sorted
        // runs binary search if sorted
        // -1 if not sorted
        if (isSorted(arr, temp1, 0) == 1)
            printf("%d", binarySearch(arr, temp2, 0, temp1-1));
        else 
            printf("-1");
    }

    return 0;   
}

// recursive division using subtraction
int divide(int a, int b){
    if (a<b)
        return 0;
    
    return 1+divide(a-b, b);
}

// euclidean algorithm for finding gcd
int gcd(int a, int b){
    if (b == 0)                        
        return a;
    else if ( a>=b && b>0)
        return gcd(b, a%b);
    else return gcd(b, a);
}

// recursive check sorted array
int isSorted (int arr[], int size, int i){
    if (i+1 == size)
        return 1;

    else if (arr[i] > arr[i+1])
        return 0*isSorted(arr, size, i+1);

    else
      return 1*isSorted(arr, size, i+1);
}

// recursive binary search
// second conditions in else if statements are for when n is not in arr[]
int binarySearch (int arr[], int n, int l, int r){
    int mid = (l+r)/2;

    if (arr[mid] == n)
        return 1;
    else if (arr[mid] < n && l != mid+1)
        binarySearch(arr, n, mid+1, r);

    else if (arr[mid] > n && r != mid-1)
        binarySearch(arr, n, l, mid-1);

    else return 0; 
}

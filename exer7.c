/*
Author: Alwyn Dy   
Date: 2021, March 29
*/

#include<stdio.h>

typedef struct {
    int nume, denom;
} Fraction;

Fraction add (Fraction a, Fraction b);
Fraction subtract (Fraction a, Fraction b);
Fraction multiply (Fraction a, Fraction b);
Fraction division (Fraction a, Fraction b);

Fraction getFraction ();
void printFraction (Fraction f);
int gcf(int a, int b);
void simplify (Fraction *f);
int absol (int n);

int main(){
    Fraction a, b;

    int choice;

    scanf("%d", &choice);

    switch (choice){
        case 1:                                     // addition
            a = getFraction();
            b = getFraction();

            printFraction(add(a, b));
            break;
        
        case 2:                                     // subtraction
            a = getFraction();
            b = getFraction();

            printFraction(subtract(a,b));
            break;

        case 3:                                     // multiplication
            a = getFraction();
            b = getFraction();

            printFraction(multiply(a,b));
            break;

        case 4:                                     // division
            a = getFraction();
            b = getFraction();

            printFraction(division(a,b));
            break;

        case 5:                                     // simplify fraction
            a = getFraction();

            simplify(&a);

            printFraction(a);
            break;
    }

    return 0;
}

// prints the fraction
// if denominator is 1, only print numerator
void printFraction (Fraction f){
    if (f.denom != 1)
        printf("%d/%d", f.nume, f.denom);
    else printf("%d", f.nume);

    return;
}

// prompts user input for the fraction values
// if player inputs '/', denominator is asked
// else, denominator is automatically 1
Fraction getFraction (){
    Fraction f;

    char temp;

    scanf("%d", &f.nume);
    scanf("%c", &temp);
    if (temp == '/')
        scanf("%d", &f.denom);
    else 
        f.denom = 1;  

    return f;

}

// addition of fractions
Fraction add (Fraction a, Fraction b){
    Fraction sum;

    // for same denominator
    if (a.denom == b.denom){
        sum.nume = a.nume + b.nume;
        sum.denom = a.denom;
    }

    else {
        sum.denom = a.denom * b.denom;
        sum.nume = (a.nume * (sum.denom / a.denom)) + (b.nume * (sum.denom / b.denom));
    }

    simplify(&sum);
    return sum;
}

// subtraction of fractions
Fraction subtract (Fraction a, Fraction b){
    Fraction diff;

    // for same denominator
    if (a.denom == b.denom){
        diff.nume = a.nume - b.nume;
        diff.denom = a.denom;
    }

    else {
        diff.denom = a.denom * b.denom;
        diff.nume = (a.nume * (diff.denom / a.denom)) - (b.nume * (diff.denom / b.denom));
    }

    simplify(&diff);
    return diff;
}

// multiplication of fractions
Fraction multiply (Fraction a, Fraction b){
    Fraction product;

    product.nume = a.nume * b.nume;
    product.denom = a.denom * b.denom;

    simplify(&product);

    return product;
}

// division of fraction
Fraction division (Fraction a, Fraction b){
    Fraction quotient;


    // prevents division by 0
    if (b.nume != 0){
        quotient.nume = a.nume * b.denom;
        quotient.denom = a.denom * b.nume;
    }

    simplify(&quotient);
    return quotient;
}

// simplify the fraction using gcf()
void simplify (Fraction *f){

    // for negative denominators
    // move negative sign to numerator
    if (f->denom < 0){
        f->denom *= -1;
        f->nume *= -1;
    }

    // finds gcf 
    int gcfInt = gcf(f->nume, f->denom);
    if (gcfInt != 1){
        f->nume /= gcfInt;
        f->denom /= gcfInt;
    }

    return;
}

// euclidean algorithm for finding gcf
int gcf(int a, int b){
    if (b == 0)                        
        return a;
    else if ( a>=b && b>0)
        return gcf(b, a%b);
    else return gcf(absol(b), absol(a));
}

// get absolute value of n
int absol (int n){

    if (n<0)
        return -n;
    else return n;
}
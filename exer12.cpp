/* 
Author: Alwyn R. Dy
Date: 2021, May 20
*/

#include<iostream>
using namespace std;

int gcf(int a, int b);
int absol (int n);

class Fraction{
    private:
        int nume;
        int denom;

    public:
        void setFraction (int a, int b){
            
            if (b != 0){
                this->nume = a;
                if (a==0)
                    this->denom = 1;
                else
                    this->denom = b;

                this->simplify();
            }
            else
                throw ("Invalid fraction (division by 0)");
        }

        void promptForFraction(){
            int a, b;
            char temp;

            cin >> a; 
            scanf("%c", &temp);
            if (temp == '/')
                cin >> b;
            else if (temp == ' ' || temp == '\n')   // temp is a space or new line
                b = 1;
            else {
                throw "Invalid fraction symbol";
            }

            setFraction(a, b);
        }

        void add (Fraction b){
            if (this->denom == b.denom)
                this->nume += b.nume;
            else {
                int tempDenom = this->denom * b.denom;
                int tempNume = (this->nume * b.denom) + (this->denom * b.nume);

                this->setFraction(tempNume, tempDenom);
            }

            this->simplify();
        }

        void subtract (Fraction b){
            if (this->denom == b.denom)
                this->nume -= b.nume;
            else {
                int tempDenom = this->denom * b.denom;
                int tempNume = (this->nume * b.denom) - (this->denom * b.nume);

                this->setFraction(tempNume, tempDenom);
            }

            this->simplify();
        }

        void multiply (Fraction b){
            this->nume *= b.nume;
            this->denom *= b.denom;
            this->simplify();
        }

        void divide (Fraction b){
            if (b.nume != 0 && b.denom != 0){
                this->nume *= b.denom;
                this->denom *= b.nume;
                this->simplify();
            }

            else
                throw ("Error: Divide by 0");
        }

        void simplify (){
            if (denom < 0){         // denom is negative
                denom *= -1;
                nume *= -1;
            }

            // finds gcf 
            int gcfInt = gcf(nume, denom);
            if (gcfInt != 1){
                nume /= gcfInt;
                denom /= gcfInt;
            }
        }

        string getFraction (){
            if (this->denom == 1)
                return to_string(this->nume);
            
            else if (this->nume == 0)
                return to_string(0);

            else {
                string frac = to_string(this->nume) + "/" + to_string(this->denom);
                return frac;
            }
        }
};


int main (){

    Fraction FracA;
    Fraction FracB;

    int choice, a, b;
    char temp;
    
    cin >> choice;

    switch (choice){
        case 1:
            try {
                FracA.promptForFraction();           
            } catch (const char* msg){
                cout << msg;
                break;
            }

            try {
                FracB.promptForFraction();
            } catch (const char* msg){
                cout << msg;
                break;
            }

            FracA.add(FracB);
            cout << FracA.getFraction();
            
            break;
        case 2:
            try {
                FracA.promptForFraction();           
                
            } catch (const char* msg){
                cout << msg;
                break;
            }

            try {
                FracB.promptForFraction();
            } catch (const char* msg){
                cout << msg;
                break;
            }

            FracA.subtract(FracB);
            cout << FracA.getFraction();
            break;
        case 3: 
            try {
                FracA.promptForFraction();           
            } catch (const char* msg){
                cout << msg;
                break;
            }

            try {
                FracB.promptForFraction();
            } catch (const char* msg){
                cout << msg;
                break;
            }

            FracA.multiply(FracB);
            cout << FracA.getFraction();
            break;
        case 4:
            try {
                FracA.promptForFraction();           
            } catch (const char* msg){
                cout << msg;
                break;
            }

            try {
                FracB.promptForFraction();
            } catch (const char* msg){
                cout << msg;
                break;
            }

            try {
                FracA.divide(FracB);
                cout << FracA.getFraction();
            } catch (const char* msg){
                cout << msg;
            }
            break;
        case 5: 
            try {
                FracA.promptForFraction();
                cout << FracA.getFraction();
            } catch (const char *msg){
                cout << msg;
            }
            break;
    }

    return 0;
}

int gcf(int a, int b){
    if (b == 0)                        
        return a;
    else if ( a>=b && b>0)
        return gcf(b, a%b);
    else return gcf(absol(b), absol(a));
}

int absol (int n){
    if (n<0)
        return -n;
    else return n;
}
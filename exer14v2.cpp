/* 
Author: Alwyn Dy
Date: 2021, May 28
*/

#include<iostream>
#include<iomanip>

using namespace std;

class Package {    
    public:
        static double weight, costPerKilo;

        Package(){
            weight;
            costPerKilo;
        }

        Package(double Weight, double CostPerKilo){
            weight = Weight;
            costPerKilo = CostPerKilo;
        }
        

        double calculateCost (){
            return weight*costPerKilo;
        }
};

class TwoDayPackage : public Package {
    protected:
        double flatFee;

    public:
        TwoDayPackage(double FlatFee) : Package(){
            this->flatFee = FlatFee;
        }

        double calculateCost (){
            return Package::calculateCost() + flatFee;
        }
                
};

class OverNightPackage : public Package {
    protected:
        double feePerKilo;

    public:
        OverNightPackage(double FeePerKilo) : Package(){
            this->feePerKilo = FeePerKilo;
        }

        double calculateCost (){
            return Package::calculateCost() + (this->weight * this->feePerKilo);
        }
};

double Package::weight = 0;
double Package::costPerKilo = 0;

int main (){

    double a, b, c, d;

    cin >> a >> b >> c >> d;

    Package x(a,b);
    TwoDayPackage y(c);
    OverNightPackage z(d);

    cout << fixed << setprecision(2) << x.calculateCost() << " " << y.calculateCost() << " " << z.calculateCost() << endl;

    return 0;
}
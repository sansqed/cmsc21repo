#include<iostream>
#include<iomanip>

using namespace std;

class Package {
    protected:
        double weight, costPerKilo;
    
    public:

        Package(){
            weight = 0;
            costPerKilo = 0;
        }

        Package(double Weight, double CostPerKilo){
            this->weight = Weight;
            this->costPerKilo = CostPerKilo;
        }
        

        double calculateCost(){
            return weight*costPerKilo;
        }
};

class TwoDayPackage : public Package {
    protected:
        double flatFee;

    public:
        TwoDayPackage(double Weight, double CostPerKilo, double FlatFee){
            Package();
            this->weight = Weight;
            this->costPerKilo = CostPerKilo;
            this->flatFee = FlatFee;
        }

        double calculateCost(){
            return Package::calculateCost() + flatFee;
        }
                
};

class OverNightPackage : public Package {
    protected:
        double feePerKilo;

    public:
        OverNightPackage(double Weight, double CostPerKilo, double FeePerKilo){
            Package();
            this->weight = Weight;
            this->costPerKilo = CostPerKilo;
            this->feePerKilo = FeePerKilo;
        }

        double calculateCost (){
            return Package::calculateCost() + (this->weight * this->feePerKilo);
        }
};

int main (){

    double a, b, c, d;

    cin >> a >> b >> c >> d;

    Package x(a,b);
    TwoDayPackage y(a,b,c);
    OverNightPackage z(a,b,d);


    cout << fixed << setprecision(2) << x.calculateCost() << " " << y.calculateCost() << " " << z.calculateCost() << endl;

    return 0;
}
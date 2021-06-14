/* 
Author: Alwyn R. Dy
Date: 2021, May 22
*/

#include<iostream>
#include<iomanip>

using namespace std;

class Point {
    private:
        float x, y;

    public:
        Point (){
            x = 0;
            y = 0;
        }

        void initPoint (float a, float b){
            x = a;
            y = b;
        }

        int getX(){
            return this->x;
        }

        int getY(){
            return this->y;
        }

        void printCoord(){
            cout << "(" << fixed << setprecision(2) << this->x << ", " << this->y << ")" << endl; 
        }
};

class Rectangle {
    private:
        Point topLeft, botRight;

    public:
        void initRectangle (Point tl, Point br){
            this->topLeft = tl;
            this->botRight = br;
        }

        void promptForRectangle (){
            int x, y;
            Point tl, br;

            cin >> x >> y;
            tl.initPoint(x, y);

            cin >> x >> y;
            br.initPoint(x, y);

            if (br.getX() <= tl.getX() || br.getY() <= tl.getY())
                throw "Error! Invalid coordinates.";

            initRectangle(tl, br);
        }

        void displayRectangle(){
            int i, j, flag=0, flag2=0;
            int TLX=this->topLeft.getX(), TLY=this->topLeft.getY();
            int BRX=this->botRight.getX(), BRY=this->botRight.getY();

            for (i=0; i<=BRY; i++){
                for (j=0; j<=BRX; j++){
                    if (j==TLX && i==TLY)                   // detects top left coord
                        flag=1;
                    if (j==TLX && i==BRY)                   // detects bottom left coord
                        flag2=1;
                    
                    if (i == TLY && flag == 1)              // top horizontal line
                        cout << "# ";
                    else if (i == BRY && flag2 == 1)        // bot horizontal line
                        cout << "# ";
                    else if (j == TLX && flag == 1)         // left vertical line
                        cout << "# ";
                    else if (j == BRX && flag == 1)         // right vertical line
                        cout << "# ";
                    else 
                        cout << "  ";
                }
                cout << endl;
            }
        }

        int getArea (){
            return (this->botRight.getX() - this->topLeft.getX()) * (this->botRight.getY() - this->topLeft.getY());
        }

        int getPerimeter (){
            return 2*(this->botRight.getX() - this->topLeft.getX()) + 2*(this->botRight.getY() - this->topLeft.getY());
        }

        Point getCenter(){
            float x = this->topLeft.getX() + ((float) (this->botRight.getX() - this->topLeft.getX()) / 2);
            float y = this->topLeft.getY() + ((float) (this->botRight.getY() - this->topLeft.getY()) / 2);

            Point c;
            c.initPoint(x, y);

            return c;
        }

        bool isSquare(){
            if (this->botRight.getX() - this->topLeft.getX() == this->botRight.getY() - this->topLeft.getY())
                return true;
            return false;
        }

};

int main (){

    Rectangle r;

    try {
        r.promptForRectangle();
    } catch (const char* msg){
        cout << msg;
        return -1;
    }

    cout << endl << "Area: " << r.getArea() << endl;
    cout << "Perimeter: " << r.getPerimeter() << endl;

    Point c;
    c = r.getCenter();
    cout << "Center: ";
    c.printCoord();

    cout << "Square: " << (r.isSquare()==1? "Yes":"No") << endl;

    r.displayRectangle();

    return 0;
}
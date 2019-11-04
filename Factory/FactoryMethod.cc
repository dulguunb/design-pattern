#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;
class Point {
    float x,y;
    explicit Point(float x,float y): x{x},y{y}{};
    class PointFactory{
    public:
        static Point NewCartessian(const float x, const float y){
            return Point{ x,y };
        }
        static Point NewPolar(const float r,const float theta){
            return Point{r*cos(theta), r*sin(theta)};
        }
    };
    public:
    friend ostream & operator<<(ostream &os, const Point &obj){
        return os << "x: " << obj.x << "y: " << obj.y << endl;
    }
    // reasoning: you cannot
    // instantiate Point and can't create PointFactory as well!
    static PointFactory Factory;
};



int main(){
    // Point p{1,2};
    // auto p = Point::PointFactory::NewCartessian(1,2);
    auto p = Point::Factory.NewCartessian(1,2);
    std::cout << p << std::endl;
    return 0;
}
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;
enum class PointType{
    cartessian,
    polar
};

class Point {
    float x,y;
    explicit Point(float x,float y): x{x},y{y}{};
    public:
    friend ostream & operator<<(ostream &os, const Point &obj){
        return os << "x: " << obj.x << "y: " << obj.y << endl;
    }
    friend class PointFactory;
};

class PointFactory{
    public:
        static Point NewCartessian(const float x, const float y){
            return Point{ x,y };
        }
        static Point NewPolar(const float r,const float theta){
            return Point{r*cos(theta), r*sin(theta)};
        }
};

int main(){
    // Point p{1,2};
    auto c = PointFactory::NewCartessian(1,2);
    std::cout << c << std::endl;
    auto p = PointFactory::NewPolar(5,M_PI_4);
    std::cout << p << std::endl;
    return 0;
}
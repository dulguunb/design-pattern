#include <iostream>
using namespace std;
class Rectangle{
    public:
    int width;
    int height;
    Rectangle(){

    }   
    int getHeight() {
        return this->height;
    }
    void setHeight(int height) {
        this->height = height;
    }
    int getWidth() {
        return this->width;
    }
    void setWidth(int width) {
        this->width = width;
    }
    int Area(){
        return width*height;
    }
};
class Square : Rectangle{
    public:
    Square(){
        
    }
};

int main(){

}
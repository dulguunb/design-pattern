# Design Pattern
   This is small study notes for OO design pattern 🔨

# SOLID Principle

## 1) Single Resonsibility Principle:

    A Class should do one thing only

Correct way:
```cpp
struct Journal{
    std::string title;
    std::vector<std::string> entries;
    explicit Journal(const std::string &title):title{title}{};
    void add(const std::string &entry){
        entries.push_back(entry);
    }

};
struct PersistanceManager{
    void save(const Journal &j, const std::string &filename){
        std::ofstream ofs(filename);
        for(auto &s: j.entries){
            ofs << s << std::endl;
        }
    }
};
```
Wrong way:
```cpp
struct Journal{
    std::string title;
    std::vector<std::string> entries;
    explicit Journal(const std::string &title):title{title}{};
    void add(const std::string &entry){
        entries.push_back(entry);
    }
    void save(const std::string &filename){
        std::ofstream ofs(filename);
        for(auto &s: entries){
            ofs << s << std::endl;
        }
    }
};
```
    Explanation: The reason why the second source code violates the Single Responsibility Principle is it's handling IO's which is not a part of Journal. To fix this, we need to introduce a new class that manages IO.

## 2) Open Closed Principle
    Class should open for extension and closed for modification

Problem:
```cpp
enum class Color {Red,Green,Blue};
enum class Size {Small,Medium,Large};
struct Product {
    std::string name;
    Color color;
    Size size;
};
struct ProductFilter {
    typedef std::vector<Product*> Items;
    static Items by_size(Items items, Size size){
        Items result;
        for(auto &i : items){
            if (i->size == size){
                result.push_back(i);
            }
        }
        return result;
    }
    static Items by_color(Items items, Color color){
        Items result;
        for(auto &i : items){
            if (i->color == color){
                result.push_back(i);
            }
        }
        return result;
    }
    static Items by_color_and_size(Items items, Color color,Size size){
        Items result;
        for(auto &i : items){
            if (i->color == color && i->size == size){
                result.push_back(i);
            }
        }
        return result;
    }
};
```
    Specification Pattern
```cpp
template <typename T> struct ISpecification
{
    virtual bool is_satisfied(T *item) = 0;
};

template <typename T> struct IFilter{
    virtual std::vector<T*> filter(std::vector<T*> items,ISpecification<T> &spec) = 0;
};

struct BetterFilter: IFilter<Product>{
    typedef std::vector<Product*> Items;
    virtual std::vector<Product*> filter(std::vector<Product*> items,ISpecification<Product> &spec) override {
        Items result;
        for(auto &p : items){
            if(spec.is_satisfied(p))
                result.push_back(p);
        }
        return result;
    }
};
struct ColorSpecification : ISpecification<Product> {
    Color color;
    explicit ColorSpecification(const Color color):color(color){};
    bool is_satisfied(Product *item) override {
        return item->color == color;
    }
};
template <typename T> struct AndSpecification : ISpecification<T>
{
    ISpecification<T> first;
    ISpecification<T> second;
    AndSpecification(ISpecification<T> first,ISpecification<T> second): first(first),second(second){}
    bool is_satisied(T *item) override{
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};
int main(){
    Product apple{"apple",Color::Green,Size::Small};
    Product tree{"tree",Color::Green,Size::Medium};
    Product house{"House",Color::Blue,Size::Large};
    std::vector<Product*> all {&apple,&tree,&house};
    BetterFilter bf;
    ColorSpecification green(Color::Green);
    auto green_things = bf.filter(all,green);
    for(auto &x : green_things){
        std::cout << x-> name << " is green" << std::endl; 
    }
    return 0;
}
```

## 3) Liskov Substitution Principle
    Object in a program should be replaceable with instances of their subtypes w/o altering
    the correctness of the program
## 4) Interface Segregation Principle
    No clients should be forced to depend on the methods it does not use.

    Wrong:
``` cpp
    struct Document;
    struct IMachine{
        virtual void print(std::vector<Document*> docs) = 0;
        virtual void scan(std::vector<Document*> docs) = 0;
        virtual void fax(std::vector<Document*> docs) = 0;
    };
    struct MFP : IMachine{
        virtual void print(std::vector<Document*> docs) override;
        virtual void scan(std::vector<Document*> docs) override;
        virtual void fax(std::vector<Document*> docs) override;
    };
```
    Correct:
``` cpp
    struct IPrinter {
        virtual void print(std::vector<Document*> docs) = 0;
    };
    struct IScanner{
        virtual void scan(std::vector<Document*> docs) = 0;
    };
    struct Printer : IPrinter{
        virtual void print(std::vector<Document*> docs) override;
    };
    struct Scanner : IScanner{
        virtual void scan(std::vector<Document*> docs) override;
    };

    struct IMachine : IPrinter, IScanner {};
    // Decorator Pattern
    struct Machine : IMachine {
        IPrinter &printer;
        IScanner &scanner;
        Machine(IPrinter &printer, IScanner &scanner) : printer(printer),scanner(scanner){};
        void print(std::vector<Document*> documents) override;
        void scan(std::vector<Document*> documents) override;
    }; 
```
    If the client needs to implement the member function then it must be broken down into smaller interfaces.
## 5) Dependency Inversion Principle
    1) High Level modules should not depend on the Low Level modules but both should depend on abstraction.
    E.g: High level module can be reporting component it should depend on ConsoleLogger but can depend on ILogger
    2) Abstraction should not depend upon details. Details should depend on the abstractions.
    Dependencies on interfaces and supertypes is better than the dependencies on concrete type.
    Inversion of Control (IOC):
    * the actual process of creating abstractions and getting them to replace dependencies.
    Dependency Injection:
    * use of software frameworks to ensure that a component dependencies are satisfied

# Creational Patterns

* Builder Pattern:
    When piecewise object construction is complicated, provide an API for doing it succintly
    E.g: Web server page rendering
    1) one way is just concatenate the strings.
    2) Represent OO structure and implement operator << on an object graph

```cpp
    #include <iostream>
    #include <string>
    #include <vector>
    #include <sstream>
    #include <memory>
    using namespace std;

    class HtmlBuilder;

    struct HtmlElement
    {
        string name;
        string text;
        vector<HtmlElement> elements;
        const size_t indent_size = 2;

        HtmlElement(){};
        HtmlElement(const string &name,const string &text):name{name},text{text}{}
        string str(int indent=0) const{
            ostringstream oss;
            string i(indent_size * indent, ' ');
            oss << i << "<" << name << ">" << endl;

            if(text.size() > 0){
                oss << string((indent_size * indent+1),' ');
            }
            for(const auto &e : elements){
                oss << e.str(indent+1);
            }
            oss << i << "</" << name << ">" <<  endl;
            return oss.str();
        }
        static HtmlBuilder build(string root_name);
        static unique_ptr<HtmlBuilder> create(string root);
    };

    struct HtmlBuilder 
    {
        HtmlElement root;
        HtmlBuilder(string root_name)
        {
            root.name = root_name;
        }
        HtmlBuilder& add_child(string child_name,string child_text){
            HtmlElement e{child_name,child_text};
            root.elements.emplace_back(e);
            return *this;
        }
        HtmlBuilder* add_child2(string child_name,string child_text){
            HtmlElement e{child_name,child_text};
            root.elements.emplace_back(e);
            return this;
        }
        operator HtmlElement(){
            return root;
        }
        string str() const { return root.str(); };
    };
    HtmlBuilder HtmlElement::build(string root_name){
            return HtmlBuilder{root_name};
    }
    static unique_ptr<HtmlBuilder> create(string root_name){
        return make_unique<HtmlBuilder>(root_name);
    }

    int main(){
        HtmlElement e = HtmlElement::build("ul").
            add_child("li","hello");
        HtmlElement ee = HtmlElement::create("ul")->add_child("","");
        cout << e.str() << endl;
        return 0;
    }
```
## Groovy pattern:
    Check GroovyBuilder.cc

# Factory Pattern
    Object creation logic becomes convulated
    Constructor is not descriptive
        - Name mandated by name of containing name
        - Cannot overload with the same sets of arguments with different names
        - Can turn into `optional parameter hell`
    Object Creation (non piecewise unlike Builder) can be outsourced to 
        - A seperate function (Factory Method)
        - That may exist n seperate class (Factory)
        - You can even have hierarchy of classes with Abstract Factory
Example of why we need Factory Pattern:
```cpp
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;
enum class PointType{
    cartessian,
    polar
};

class Point{
    float x,y;
    explicit Point(float x,float y): x{x},y{y}{};
    public:
    Point(const float a,const float b, PointType type = PointType::cartessian){
        if (type == PointType::cartessian){
            x = a;
            y = b;
        }
        else {
            /// convert
        }
    }
};
```
# Terminology:
    Factory:
    A factory construct used to construct object in hierarchies'
```cpp
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
```
    Factory Method:
    A function that helps to create objects. Like a constructor but more descriptive
# Prototype Design Pattern
    - Shallow vs Deep copy
    - Boost serialization

    + Compilicated objects (e.g cars) aren't designed from scratch
    - They reiterate the existing designs
    + An existing (partially constructed design) is Prototype
    + We make copy(clone) (prototype) and customize it
        - requires deep copy support
        - painful without metadata
    + We make cloning convenient (via Factory)
    Partially or fully initalized objects you copy (clone) and make use of

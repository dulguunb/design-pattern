#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"

int main(){
    Person::create()
        .lives().at("123 Road Island").with_postcodes("SW1 1GB").in("London");
    Person::create()
        .works().at("PragmaSoft").as_a("consultant").earning(10e6);
    
    getchar();
    return 0;
}

#pragma once
#include <string>
#include "PersonBuilder.h"
using namespace std;


class Person{
    string street_address,post_code,city;
    string company_name,position;
    public:
       Person(){};
    int annual_income = 0;
    public:
        static PersonBuilder create();
    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};



#pragma once
#include <string>
#include <iostream>
#include "PersonBuilder.h"

using namespace std;
class PersonJobBuilder : public PersonBuilder
{
    typedef PersonJobBuilder Self;
public:
    explicit PersonJobBuilder(Person &person): PersonBuilder{person}{};
    Self& at(string company_name){
        person.company_name = company_name;
        return *this;
    };
    Self& as_a(string position){
        person.position = position;
        return *this;
    };
    Self& earning(int annual_income){
        person.annual_income = annual_income;
        return *this;
    };
};
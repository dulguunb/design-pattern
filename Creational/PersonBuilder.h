#ifndef PERSONBUILDER_H
#define PERSONBUILDER_H
#include "Person.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"
class PersonBuilder{
    Person p;
    protected:
        Person &person;
    explicit PersonBuilder(Person &person):person{person}{}
    public:
    operator Person(){
        return move(person);
    }
    PersonBuilder():person{p}{};
    PersonAddressBuilder lives();
    PersonJobBuilder works();
};
#endif
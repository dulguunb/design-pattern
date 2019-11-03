#ifndef PERSONADDRESSBUILDER_H
#define PERSONADDRESSBUILDER_H
#include <string>
#include <iostream>
#include "PersonBuilder.h"
using namespace std;
class PersonAddressBuilder;
class PersonAddressBuilder : public PersonBuilder {
    typedef PersonAddressBuilder Self;
public:
    explicit PersonAddressBuilder(Person &person) :PersonBuilder{person}{};
    Self& at(string street_address){
        person.street_address = street_address;
        return *this;
    };
    Self& with_postcodes(string post_code){
        person.post_code = post_code;
        return *this;
    };
    Self& in(string city){
        person.city = city;
        return *this;
    };
    
};
#endif
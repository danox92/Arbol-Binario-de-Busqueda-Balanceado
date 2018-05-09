#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Counter.hpp"

using namespace std;


class DNI
{
private:
    int numDNI;
    char let;
public:
    static Counter counter;
    DNI() {
        numDNI = 30000000 + (rand() % 50000000);
        let ="TRWAGMYFPDXBNJZSQVHLCKE"[numDNI % 23];
    };

    DNI(int i,char l): numDNI(i),let(l){}

    DNI(int i): numDNI(i){
         let ="TRWAGMYFPDXBNJZSQVHLCKE"[numDNI % 23];
    }

    virtual ~DNI() {};
    operator int() const { return numDNI;};


    bool operator==(const DNI& dni) {
        counter++;
        return dni.numDNI == this->numDNI;
    }

    bool operator<(const DNI& dni) {
        counter++;
        return this->numDNI < dni.numDNI;
    }

    bool operator>(const DNI& dni) {
        counter++;
        return this->numDNI > dni.numDNI;
    }

    bool operator<=(const DNI& dni) {
        counter++;
        return this->numDNI <= dni.numDNI;
    }

    bool operator>=(const DNI& dni) {
        counter++;
        return this->numDNI >= dni.numDNI;
    }

    friend ostream& operator<<(ostream& os, const DNI& d);
};

ostream& operator<<(ostream& os, const DNI& d)
{
    os << d.numDNI << d.let;
    return os;
};

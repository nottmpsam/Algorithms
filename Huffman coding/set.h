#pragma once
#include <iostream>
#include "bvector.h"
class Set: public bVector
{

private:
    int power;
public:

    Set();
    Set(const char*);
    Set(const Set&);
    ~Set() {}

    Set& operator=(const Set& temp);
    
    bool isEmpty() const;
    bool isHere(char) const;
    char maxInSet() const;
    char minInSet() const;

    Set operator&(const Set&) const;
    Set& operator&=(const Set&);

    bool operator==(const Set&) const;
    bool operator!=(const Set&) const;

    Set operator|(const Set&) const;
    Set& operator|=(const Set&);

    Set operator/(const Set&) const;
    Set& operator/=(const Set&);

    Set operator+(char) const;
    Set& operator+=(char);

    Set operator-(char) const;
    Set& operator-=(char);

    Set operator~() const;

    int getPower() const {
        return power;
    }

    friend std::ostream& operator<<(std::ostream& os, const Set& temp);
    friend std::istream& operator>>(std::istream& is,  Set& temp);
};

#include <iostream>
#include "set.h"

bool Set::operator==(const Set& temp) const
{
    return !(*this != temp);
}

bool Set::operator!=(const Set& temp) const
{
    Set ted = *this / temp;
    if (power != temp.power || ted.power)
        return true;
    return false;
}

Set Set::operator~() const
{
      Set ted;
      ted.bVector::operator=(bVector::operator~());
      ted.power = WeightOfVector();
      return ted;
}

std::istream& operator>>(std::istream& is,  Set& temp)
{
    is >> static_cast<bVector&> (temp);
    temp.power = temp.WeightOfVector();
    return is;
}
std::ostream& operator<<(std::ostream& os, Set& temp)
{
    //can output values
   // os << static_cast<bVector&>(temp);
   // return os; 
   //
   // but for  save immutability of bVector:
   int i = 0;
   while (i < temp.UCHAR_SIZE) {
        if ((temp)[i]) {
            os << char(i);
        }
        ++i;
   }
   return os;

}
bool Set::isHere(char temp) const
{
    if (operator[](int(temp)))
       return true;
    return false;
}

Set& Set::operator=(const Set& temp)
{
    if (this != &temp)
    {
        bVector::operator=(temp);
        power = temp.power;
    }
    return *this;
}

Set::Set(const char* s) : bVector(UCHAR_SIZE)
{
    int i = 0;
    while (s[i]) {
        Set_1(int(s[i++]));
    }
    power = WeightOfVector();
}

bool Set::isEmpty() const
{
    return (power == 0 ? true : false);
}

Set::Set() : bVector(UCHAR_SIZE)
{
    power = 0;
}

Set::Set(const Set& temp) : bVector(temp)
{
    power = temp.power;
}

Set Set::operator&(const Set& temp) const
{
    Set ted = *this;
    ted &= temp;
    return ted;
}

Set& Set::operator&=(const Set& temp)
{
    bVector::operator&=(temp);
    power = WeightOfVector();
    return *this;
}

Set Set::operator|(const Set& temp) const
{
    Set ted = *this;
    ted |= temp;
    return ted;
}

Set& Set::operator|=(const Set& temp)
{
    bVector::operator|=(temp);
    power = WeightOfVector();
    return *this;
}

Set& Set::operator/=(const Set & temp)
{
   Set ted = *this;
   *this ^= temp;
   *this &= ted;
   return *this;
}

Set Set::operator/(const Set& temp) const
{
    Set ted = *this;
    ted /= temp;
    return ted;
}

Set Set::operator+(char temp) const
{
    Set ted = *this;
    ted += temp;
    return ted;
}

Set Set::operator-(char temp) const
{
    Set ted = *this;
    ted -= temp;
    return ted;
}

Set& Set::operator-=(char temp)
{
    if (isHere(temp)) {
        --power;
        Set_0((int)temp);
    }
    return *this;
}

Set& Set::operator+=(char temp)
{
    if (!isHere(temp)) {
        ++power;
        Set_1((int)temp);
    }
    return *this;
}

char Set::minInSet() const
{
    if (isEmpty()) {
        return ' ';
    }
    int i = 0;
    while (operator[](++i) == 0);
    return char(i);

}

char Set::maxInSet() const
{
    if (isEmpty()) {
        return ' ';
    }
    int i = UCHAR_SIZE;
    while (operator[](--i) == 0);
    return char(i);
}


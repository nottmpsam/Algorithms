#pragma once
#include <iostream>
#define uc unsigned char
class bVcomponent;
class bVector
{

    int lenV, charBytes;
    unsigned char* bv;
    public:
    enum {UCHAR_SIZE = 256, BITS = 8};
    explicit bVector(int nn = 0, int mm =1);
    explicit bVector(const char *,int length = 0, bool flag = false);
    ~bVector() { delete [] bv; }
    bool Set_1(int index);
    bVector(const bVector& tempVector);

    friend class bVcomponent;
    int CreateVector(const char* str, int cChar, int current_len, int current_i);
    bool Set_0(int index);
    bool InverstionSet(int index);
    void SetAll_1();
    void SetAll_0();
    int WeightOfVector() const;
    bool SetWithRange_1(int bits, int  index);
    bool SetWithRange_0(int bits, int  index);

    bVector& operator=(const bVector& tempV);
    bVector operator&(const bVector& tempV) const;
    bVector& operator&=(const bVector& tempV);

    bVector operator^(const bVector& tempV) const;
    bVector& operator^=(const bVector & tempV);

    bVector operator|(const bVector & tempV) const;
    bVector& operator|=(const bVector & tempV);
    bVector operator~() const;
    bVector operator>>(int integer) const;
    bVector operator<<(int integer) const;
    bVector& operator<<=(int integer);
    bVector& operator>>=(int integer);
    int Size() const;
    bVcomponent operator[](int index) const;
    friend std::ostream&
        operator<<(std::ostream& out, bVector& tempV);
    friend std::istream&
        operator>>(std::istream& in, bVector& tempV);
    bool operator==(int) const;
    bool operator!=(int) const;
    bool operator<(int) const;
    bool operator>(int) const;
    bool operator>= (int) const;
    bool operator<=(int) const;
    operator int() const;
    bool InverstionWithRange(int bits, int index);
    long Result() const;

};
class bVcomponent
{
private:
    unsigned char mask = 1;
    unsigned char * cpy;
public:
    bVcomponent() = default;
    bVcomponent(unsigned char* cpy_, int index_);
    void operator=(bool integer) const;
    operator int() const;
    friend std::ostream& operator<<(std::ostream& out, const bVcomponent& temp);
};

#include "bvector.h"
#include <cstring>

bVcomponent::operator int() const
{
    return (*cpy & mask);
}

void bVcomponent::operator=(bool integer) const
{
    if (integer)
        *cpy |=  mask;
    else
        *cpy &= ~mask;
}

bVcomponent::bVcomponent(uc* cpy_ , int index_)
{
    mask <<= index_ % bVector::BITS;
    cpy = cpy_;
}

bVcomponent bVector::operator[](int index) const
{
    if (index < lenV && index >= 0)
    {
        bVcomponent temp(&bv[charBytes - 1 - index / BITS], index);
		return temp;
    }
    bVcomponent teddy(&bv[charBytes-1], 0);
    return teddy;
}

std::ostream& operator<<(std::ostream& out, const bVcomponent& temp)
{
    out << (*(temp.cpy) & temp.mask); // output value bv[index];
    return out;
}

bVector::operator int() const
{
    int ted = Result();
    return ted;
}
long bVector::Result() const
{
    long result = 0;
    int eq = 0;
    for (int j = charBytes-1; j >= 0; --j)
        for (int i = 0; i < BITS; ++i, ++eq)
        {
            if (bv[j] & (1 << i ))
                result += (1 << eq);
        }
    return result;
}
bVector::bVector(int nn, int mm)
{
    charBytes = (mm == 0 ? 1 : (mm < 0 ? -mm : mm));
    lenV = (nn < 0 ? 0 : nn);
    if (nn > BITS*mm) {
        charBytes = (lenV + 7) / BITS;
    }
    bv = new uc [charBytes];
    SetAll_0();
}
std::ostream& operator<<(std::ostream& out, bVector& tempV)
{
    for (int j = 0; j < tempV.charBytes; ++j){
        for (int i = 0; i < tempV.BITS; ++i) {
         out << ((tempV.bv[j] & (1 << (tempV.BITS - 1 - i)) ? 1 : 0));
        }
    }
    return out;
}

int bVector::CreateVector(const char* str, int cChar, int current_len, int current_i)
{
    bv[cChar] = 0;
    for (int i = 0; i < current_len; ++i)
    {
        bv[cChar] <<= 1;
        if (str[current_i] == '1')
            ++bv[cChar];
        ++current_i;
    }
    return current_i;
}

std::istream& operator>>(std::istream& in, bVector& tempV)
{
    /*
    int Range;
    in >> Range;
    char* str = new char[Range];
    in >> str;
    bVector temp(str);
    delete [] str;
    tempV = temp;
    return in;*/
    int Range;
    in >> Range;
    char* str = new char[Range];
    in >> str;

    int i = 0;
    bool flag = false;
    while (str[i]) {
        if (str[i] != '1' &&  str[i] != '0') {
            flag = true;
            break;
        }
        ++i;
    }
    bVector temp(str, 0, flag);
    delete [] str;
    tempV = temp;
    return in;
}
bVector::bVector(const char* str, int length, bool flag)
{
    /*
    int lenStr = strlen(str);
    lenV = (length == 0) ? lenStr : (length > lenStr ? lenStr : length);
    charBytes = (lenV + 7) / BITS;
    bv = new uc[charBytes];
    int cChar = 0;
    int current_i = 0;
    if (lenV % BITS)
    {
        current_i = CreateVector(str, cChar, lenV % BITS, current_i);
        ++cChar;
    }
    while(current_i < lenV)
    {
        current_i = CreateVector(str, cChar, BITS, current_i);
        ++cChar;
    }*/
    if (flag) {
       lenV = UCHAR_SIZE;
       charBytes = (lenV+7) / BITS;
       bv = new uc[charBytes];
       for (int i = 0; str[i]; ++i)
           Set_1(int(str[i]));
    } else {
        int lenStr = strlen(str);
        lenV = (length == 0) ? lenStr : (length > lenStr ? lenStr : length);
        charBytes = (lenV + 7) / BITS;
        bv = new uc[charBytes];
        int cChar = 0;
        int current_i = 0;
        if (lenV % BITS)
        {
            current_i = CreateVector(str, cChar, lenV % BITS, current_i);
            ++cChar;
        }
        while(current_i < lenV)
        {
            current_i = CreateVector(str, cChar, BITS, current_i);
            ++cChar;
        }
    }
}
bVector::bVector(const bVector& tempVector)
{
    lenV = tempVector.lenV;
    charBytes = tempVector.charBytes;
    bv = new unsigned char [charBytes];
    for (int i = 0; i < charBytes; ++i)
        bv[i] = tempVector.bv[i];
}

bVector bVector::operator&(const bVector& tempV) const
{
    bVector ted = *this;
    ted &= tempV;
    return ted;
}

bVector bVector::operator^(const bVector& tempV) const
{
    bVector ted = *this;
    ted ^= tempV;
    return ted;
}

bVector bVector::operator|(const bVector& tempV) const
{
    bVector ted = *this;
    ted |= tempV;
    return ted;
}

bVector& bVector::operator&=(const bVector& tempV)
{
     int length = lenV > tempV.lenV ? lenV : tempV.lenV;
     bVector ted (length);
     int i, j, z;
     for (i = charBytes - 1, j = tempV.charBytes - 1, z = ted.charBytes - 1;
             i >= 0 && j >= 0; --i, --j, --z)
         ted.bv[z] = bv[i] & tempV.bv[j];
     *this = ted;
     return *this;
}

bVector& bVector::operator^=(const bVector& tempV)
{
    int length = lenV > tempV.lenV ? lenV : tempV.lenV;
    bVector ted ( length );
    int i, j, z;
    for (i = charBytes - 1, j = tempV.charBytes - 1, z = ted.charBytes - 1;
            i >= 0 && j >= 0; --i, --j, --z)
        ted.bv[z] = bv[i] ^ tempV.bv[j];

    while (z >= 0 && i >= 0)
    {
        ted.bv[z] ^= bv[z];
        --z;
    }
    while (z >= 0 && j >= 0 )
    {
        ted.bv[z] ^= tempV.bv[z];
        --z;
    }
    *this = ted;
    return *this;
}

bVector&bVector::operator|=(const bVector& tempV)
{
    int length = lenV > tempV.lenV ? lenV : tempV.lenV;
    bVector ted (length);
    int i, j, z;
    for (i = charBytes - 1, j = tempV.charBytes - 1, z = ted.charBytes - 1;
            i >= 0 && j >= 0; --i, --j, --z)
        ted.bv[z] = bv[i] | tempV.bv[j];

    while (z >= 0 && i >= 0)
    {
        ted.bv[z] |= bv[z];
        --z;
    }
    while (z >= 0 && j >= 0 )
    {
        ted.bv[z] |= tempV.bv[z];
        --z;
    }
    *this = ted;
    return *this;

}

bool bVector::InverstionWithRange(int bits, int index)
{
     if (bits < 0 || index < 0 || lenV < bits+index)
         return false;
     for (int i = 0; i < bits; ++i)
         InverstionSet(index++);
     return true;
}

bVector& bVector::operator=(const bVector & tempV)
{
    if (this != & tempV)
    {
        delete [] bv;
        charBytes = tempV.charBytes;
        lenV = tempV.lenV;
        bv = new uc[charBytes];
        for (int i = 0; i < lenV; ++i)
            bv[i] = tempV.bv[i];
    }
    return *this;
}

bool bVector::SetWithRange_0(int bits, int index)
{

    if (bits < 0 || index < 0 || lenV < bits+index)
        return false;
    for (int i = 0; i < bits; ++i)
        Set_0(index++);
    return true;
}
bool bVector::SetWithRange_1(int bits, int  index)
{
    if (bits < 0 || index < 0 || lenV < bits+index)
        return false;
    for (int i = 0; i < bits; ++i)
        Set_1(index++);
    return true;
}
int bVector::WeightOfVector() const
{
    int count = 0;
    uc mask;
    for (int j = 0; j < charBytes; ++j)
    {
        mask = 1;
        do
        {
            if (mask & bv[j])
                ++count;
        } while(mask <<= 1);
    }
    return count;
}
void bVector::SetAll_0()
{
    for(int j = 0; j < charBytes; ++j)
            bv[j] = 0;
}
void bVector::SetAll_1()
{
     for (int j = 0; j < charBytes; ++j)
        bv[j] = 255;

}
bVector bVector::operator~() const
{
    bVector ted (lenV);
    for (int j = 0; j < charBytes; ++j)
        ted.bv[j] = ~bv[j];
    return ted;
}
bool bVector::Set_0(int index)
{
    if (index < charBytes*BITS && index >= 0)
    {
        int cChar = charBytes - 1 - index / BITS;
        bv[cChar] &= ~(1 << index % BITS);
        return true;
    }
    return false;
}
bool bVector::Set_1(int index)
{
    if (index < charBytes*BITS && index >= 0)
    {
        int cChar = charBytes - 1 - index / BITS;
        bv[cChar] |= (1 << index % BITS);
        return true;
    }
    return false;
}
bool  bVector::InverstionSet(int index)
{
    if (index < charBytes*BITS && index >= 0)
    {
        int cChar = charBytes - 1 - index / BITS;
        bv[cChar] ^= (1 << index % BITS);
        return true;
    }
    return false;
}
bVector bVector::operator<<(int integer) const
{
    bVector temp(*this);
    temp <<= integer;
    return temp;
}
bVector bVector::operator>>(int integer) const
{
    bVector temp(*this);
    temp >>= integer;
    return temp;
}
bVector& bVector::operator>>=(int integer)
{
    for (int i = 0; i < integer; ++i) {
        for (int j = 0; j < charBytes*BITS-1; ++j)
        {
            if (operator[](j+1))
                Set_1(j);
            else
                Set_0(j);
            Set_0(j+1);
        }
    }
    return *this;
}
bVector& bVector::operator<<=(int integer)
{
    for (int i = 0; i < integer; ++i) {
        for (int j = charBytes*BITS -1; j >= 0; --j)
        {
            if (operator[](j-1))
                Set_1(j);
            else
                Set_0(j);
            Set_0(j-1);
        }
    }
    std::cout << std::endl;
    return *this;
}
bool bVector::operator<=(int key) const
{
    if (Result() <= key)
        return true;
    return false;
}
bool bVector::operator<(int key) const
{
    if (Result() < key)
        return true;
    return false;
}
bool bVector::operator>=(int key) const
{
    if (Result() >= key)
        return true;
    return false;
}
bool bVector::operator>(int key) const
{
    if (Result() > key)
        return true;
    return false;
}
bool bVector::operator!=(int key) const
{
    if (Result() != key)
        return true;
    return false;
}
bool bVector::operator==(int key) const
{
    if (Result() == key)
        return true;
    return false;
}
int bVector::Size() const
{
    std::cout << charBytes << " " << lenV << std::endl;
    return charBytes * sizeof(char);
}

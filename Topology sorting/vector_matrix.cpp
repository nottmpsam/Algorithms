#include <iostream>
#include "vector_matrix.h"
bVector bMatrix::Disjunction_M() const
{
    bVector temp = bm[0];
    for (int i = 1; i < rows; ++i)
        temp |= bm[i];
    return temp;
}

bVector bMatrix::Conjuction_M() const
{
    bVector temp = bm[0];
    for (int i = 1; i < rows; ++i)
        temp &= bm[i];
    return temp;
}

bVector bMatrix::operator[](int line) const
{
    if (0 < line && line < lines) {
        return bm[line];
    }
    return bm[0];
}
bVector& bMatrix::operator [] (int line)
{
    if (0 < line && line < lines)
        return bm[line];
    return bm[0];
}

bMatrix& bMatrix::operator=(const bMatrix& temp)
{
    if (this == &temp)
        return *this;
    delete [] bm;
    rows = temp.rows;
    lines = temp.lines;
    bm = new bVector[rows];
    for (int i = 0; i < rows; ++i)
        bm[i] = temp.bm[i];
    return *this;
}

std::istream& operator>>(std::istream& in, bMatrix& temp)
{
    int rows_, lines_;
    std::cin >> rows_ >> lines_;

    temp.rows = (rows_ == 0) ? 1 : (rows_ < 0 ? -rows_ : rows_ );
    temp.lines = (lines_ < 0) ? 0 : lines_;

    delete [] temp.bm;
    temp.bm = new bVector[temp.rows];
    char* str = new char[temp.lines];

    for (int i = 0; i < temp.rows; ++i)
    {
        in >> str;
        bVector teddy(str, temp.lines);
        temp.bm[i] = teddy;
    }
    delete [] str;

    return in;
}

std::ostream& operator<<(std::ostream& out, const bMatrix& temp)
{
    int i;
    for (i = 0; i < temp.rows - 1; ++i)
        out << temp.bm[i] << std::endl;
    out << temp.bm[i];
    return out;
}

bMatrix bMatrix::operator~() const
{
    bMatrix temp = *this;
    for (int i = 0; i < temp.rows; ++i)
        temp.bm[i] = ~temp.bm[i];
    return temp;
}

bMatrix bMatrix::operator|(const bMatrix& temp) const
{
    bMatrix teddy = *this;
    teddy |= temp;
    return teddy;
}

bMatrix& bMatrix::operator|=(const bMatrix& temp)
{
    if (rows != temp.rows)
        return *this;
    int length = (lines > temp.lines) ? lines : temp.lines;
    bMatrix teddy(rows, length);
    for (int i = 0; i < teddy.rows; ++i)
        teddy.bm[i] = bm[i] | temp.bm[i];
    *this = teddy;
    return *this;
}

bMatrix bMatrix::operator^(const bMatrix& temp) const
{
    bMatrix teddy = *this;
    teddy ^= temp;
    return teddy;
}

bMatrix& bMatrix::operator^=(const bMatrix& temp)
{
    if (rows != temp.rows)
        return *this;
    int length = (lines > temp.lines) ? lines : temp.lines;
    bMatrix teddy(rows, length);
    for (int i = 0; i < teddy.rows; ++i)
        teddy.bm[i] = bm[i] ^ temp.bm[i];
    *this = teddy;
    return *this;
}

bMatrix bMatrix::operator&(const bMatrix& temp) const
{
    bMatrix teddy = *this;
    teddy &= temp;
    return teddy;
}

bMatrix& bMatrix::operator&=(const bMatrix& temp)
{
    if (rows != temp.rows)
        return *this;
    int length = (lines > temp.lines) ? lines : temp.lines;
    bMatrix teddy(rows, length);
    for (int i = 0; i < teddy.rows; ++i)
        teddy.bm[i] = bm[i] & temp.bm[i];
    *this = teddy;
    return *this;
}

bool bMatrix::SetWithRange_0_M(int bits, int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].SetWithRange_0(bits, index)))
         return true;
    return false;
}

bool bMatrix::SetWithRange_1_M(int bits, int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].SetWithRange_1(bits, index)))
        return true;
    return false;
}

bool bMatrix::Set_0_M(int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].Set_0(index)))
        return true;
    return false;
}

bool bMatrix::Set_1_M(int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].Set_1(index)))
            return true;
    return false;
}

bool bMatrix::InverstionWithRange_M(int bits, int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].InverstionWithRange(bits, index)))
            return true;
    return false;
}

bool bMatrix::InverstionSet_M(int index, int line)
{
    if ((0 <= line && line < lines) && (bm[index].InverstionSet(line)))
               return true;
    return false;
}

int bMatrix::WeightOfLine(int line) const
{
    if (0 <= line && line < lines)
        return bm[line].WeightOfVector();
    return -1;
}

int bMatrix::WeightOfMatrix() const
{
    int weight = 0;
    for (int i = 0; i < rows; ++i)
        weight += bm[i].WeightOfVector();
    return weight;
}

bMatrix::bMatrix(const bMatrix& temp)
{
    rows = temp.rows;
    lines = temp.lines;
    bm = new bVector[rows];
    for (int i = 0; i < rows; ++i)
        bm[i] = temp.bm[i];
}

bMatrix:: bMatrix(char ** str, int rows_, int lines_)
{
    rows = (rows_ == 0) ? 1 : (rows_ < 0) ? -rows_ : rows_ ;
    lines = (lines_ < 0) ? 0 : lines_;
    bm = new bVector[rows];
    for (int i = 0; i < rows; ++i)
    {
        bVector temp(str[i], lines);
        bm[i] = temp;
    }
}

bMatrix:: bMatrix(int rows_, int lines_)
{
    rows = (rows_ == 0) ? 1 : (rows_ < 0) ? -rows_ : rows_ ;
    lines = (lines_ < 0) ? 0 : lines_;
    bm = new bVector[rows];
    bVector temp(lines);
    for (int i = 0; i < rows; ++i)
        bm[i] = temp;

}


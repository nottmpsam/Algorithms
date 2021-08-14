#pragma once
#include <iostream>
#include <vector>
#include "bvector.h"
class bMatrix
{
    bVector * bm;
    int rows, lines;
public:
    explicit bMatrix(int rows_ = 1, int lines_ = 0);
    bMatrix(char ** str, int rows_, int lines_);
    bMatrix(const bMatrix& temp);
    ~bMatrix () { delete [] bm; }

    int WeightOfMatrix() const;
    int WeightOfLine(int line) const;
    bVector Conjuction_M() const;
    bVector Disjunction_M() const;
    bool InverstionSet_M(int index, int line);
    bool InverstionWithRange_M(int bits, int index, int line);
    bool Set_1_M(int index, int line);
    bool Set_0_M(int index, int line);
    bool SetWithRange_1_M(int bits, int index, int line);
    bool SetWithRange_0_M(int bits, int index, int line);

    bMatrix& operator=(const bMatrix& temp);
    bVector operator[](int line) const;
    bVector& operator[](int line);
    bMatrix operator&(const bMatrix& temp) const;
    bMatrix& operator&=(const bMatrix & temp);
    bMatrix operator|(const bMatrix& temp) const;
    bMatrix& operator|=(const bMatrix& temp);
    bMatrix operator^(const bMatrix& temp) const;
    bMatrix& operator^=(const bMatrix& temp);
    bMatrix operator~() const;
    friend std::ostream& operator<<(std::ostream& out, const bMatrix& temp);
    friend std::istream& operator>>(std::istream& in, bMatrix& temp);
    //for topology sort methods
    void SupportSort(std::vector<int>&, bMatrix&, bVector&);
    std::vector<int> SortGraph();
};


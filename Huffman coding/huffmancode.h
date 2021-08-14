#pragma once
#include <string>
#include <vector>
#include "node.h"
class HuffmanCode
{
    enum {BITS = 8, UCHAR_SIZE = 256};
public:
    bool HuffmanAlgorithm(const std::string& nameFile, std::string nameFile1 = {""});
    bool decodingText(const std::string& NameFile, std::string NameFile1 = {""});
private:
    Node* createNodes(const std::vector<int>&a);
    Node* createTree(Node*n);
    int encodingText(Node* q, const std::string& NameFile, const std::string& outPutFile, std::vector<int> &a);
    int countSymbols(std::string, std::vector<int>&a);
    void displayTree(Node*q, int level) const;
    void deleteTree(Node*q);
};

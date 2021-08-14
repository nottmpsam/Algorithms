#include <iostream>
#include <fstream>
#include <bitset>
#include "huffmancode.h"
#include "node.h"

bool HuffmanCode::HuffmanAlgorithm(const std::string& nameFile, std::string nameFile1)
{
    std::ifstream inputFile(nameFile);
    if (!inputFile.is_open()) {
        std::cerr << "Input file did not open" << std::endl;
        return false;
    }
    if (nameFile1.empty()) {
        nameFile1 += "decodedText.txt";
    }
    std::ofstream outFile(nameFile1);
    std::vector <int> a(UCHAR_SIZE,0);
    int allSymbols = countSymbols(nameFile, a);
    Node* node = createNodes(a);
    node = createTree(node);
    int allCodedSymbols = encodingText(node, nameFile, nameFile1, a);
    allSymbols = BITS*allSymbols;
    std::cout << "Bits in text: " << allSymbols << " | " << "H. code: " << allCodedSymbols << std::endl; 
    std::cout << "Bytes: " << allSymbols / BITS << " | H.code: " << allCodedSymbols / BITS << std::endl;
    double res = (double) allCodedSymbols/ allSymbols;
    res = 100 - res*100;
    std::cout << res << "%" << std::endl;
    deleteTree(node);
    return true;
}
bool HuffmanCode::decodingText(const std::string& nameFile, std::string nameFile1)
{
    std::ifstream inputFile(nameFile, std::ios_base::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Input file did not open" << std::endl;
        return false;
    }
    if (nameFile1.empty()) {
        nameFile1 += "encodedText.txt";
    }
    std::ofstream outputFile (nameFile1);
    unsigned char realSymbols = 0; 
    inputFile.read(reinterpret_cast<char*>(&realSymbols), sizeof realSymbols);

    unsigned char buf;
    int buf1 = 0;
    std::vector<int> a(UCHAR_SIZE, 0);
    for (int i = 0; i < realSymbols; ++i) {
        inputFile.read(reinterpret_cast<char*>(&buf), sizeof buf);
        inputFile.read(reinterpret_cast<char*>(&buf1), sizeof buf1);
        a[buf] = buf1;
    }

    int byteCount = 0;
    unsigned char mod = 0;
    inputFile.read(reinterpret_cast<char*>(&byteCount), sizeof byteCount);
    inputFile.read(reinterpret_cast<char*>(&mod), sizeof mod);

    int i = 0; 
    std::string str {""};

    while (i < byteCount) {
        inputFile.read(reinterpret_cast<char*>(&buf), 1);
        std::bitset <BITS> b(buf);
        str += b.to_string();
        ++i;
    }
    if (mod > 0) {
        inputFile.read(reinterpret_cast<char*>(&buf), 1);
        std::bitset<BITS> b(buf);
        std::string t = b.to_string();
        str += t.substr(0, mod);
    }

    Node* node = createNodes(a);
    node = createTree(node);
    displayTree(node, 1);
    Node* q = node;
    std::string outstr;
    for (int i = 0; i < str.size(); ++i) {
        buf = str[i];
        if (buf == '0') {
            if (q->left) {
                q = q->left;
            }
        } else {
            if (q->right) {
                q = q->right;
            }
        }
        if (!q->left && !q->right) {
            outstr += (unsigned char) q->str;
            outputFile << (unsigned char) q->str;
            q = node;
        }
    }
    deleteTree(node);
    return true;
}

int HuffmanCode::encodingText(Node*q, const std::string& nameFile, const std::string& oNameFile, std::vector<int>&a)
{

    std::ifstream file(nameFile);
    std::ofstream outFile(oNameFile, std::ostream::binary);
    char c;
    std::string outPut {""};
    while (file.get(c)) {
        Node* t = q;
        while (t->left || t->right) {
                if (t->left->str.isHere(c)) {
                    t = t->left;
                    outPut += "0";
                } else {
                    t = t->right;
                    outPut += "1";
                }
        }
    }

    unsigned char realSymbols = q->str.WeightOfVector();

    outFile.write(reinterpret_cast<char*> (&realSymbols), sizeof (realSymbols));
    for (int i = 0; i < UCHAR_SIZE; ++i) {
        if (a[i] != 0) {
            outFile.write(reinterpret_cast<char*> (&i), sizeof((unsigned char)i));
            outFile.write(reinterpret_cast<char*> (&a[i]), sizeof(a[i]));
        }
    }

    int byteCount = outPut.size() / BITS;
    unsigned char mod = outPut.size() % BITS;
    outFile.write(reinterpret_cast<char*> (&byteCount), sizeof byteCount);
    outFile.write(reinterpret_cast<char*> (&mod), sizeof mod);

    int i = 0;
    while (i < byteCount) {
        std::bitset<BITS> b(outPut.substr(i*BITS, BITS));
        outFile.write(reinterpret_cast<char* > (&b), sizeof (char));
        ++i;
    }
    if (mod > 0) {
        std::bitset<BITS> b(outPut.substr(i*BITS, mod));
        b <<= BITS - (int) mod;
        outFile.write(reinterpret_cast<char* > (&b), sizeof (char));
    }

    file.close();
    outFile.close();
    return outPut.size();
}

Node* HuffmanCode::createTree(Node*q)
{
    while (true) {
        Node* first = q;
        Node* sec = q->next;
        int c = sec->count + first -> count;
        Node* temp = new Node(sec->count + first->count);
        temp->str = first->str | sec->str;
        temp->left = first;
        temp -> right = sec;
        if (sec->next) {
            q = sec->next;
        } else {
            temp->left = first;
            temp->right = sec;
            q = temp;
            break;
        }
        Node* t = q;
        if (c <= t->count) {
            temp->next = q;
            q = temp;
        } else {
            while (t) {
                if (t->next) {
                    if(t->next->count >= c) {
                        temp->next = t->next;
                        t->next = temp;
                        break;
                    }
                } else {
                    t->next = temp;
                    temp->next = nullptr;
                    break;
                }
                t = t->next;
            }
        }
    }
    return q;
}
Node* HuffmanCode::createNodes(const std::vector<int> &a)
{
    Node* head = nullptr;
    Node* temp = nullptr;
    int c = 0;
    for (int i = 0; i < UCHAR_SIZE; ++i)
    {
        c = a[i];
        if (c != 0){
            if (!head && c != 0){
                head = new Node(c);
                head->str.Set_1(i);
                temp = head;
            } else if (c >= temp->count) {
                Node* nx = new Node(a[i]);
                nx->str.Set_1(i);
                temp->next = nx;
                temp = nx;
            } else {
                if (c < head->count) {
                    Node* cur = head;
                    head = new Node (c, cur);
                    head->next = cur;
                    head->str.Set_1(i);
                } else {
                    Node* t = head;
                    while (t) {
                        if (t->next->count > c)
                        {
                            Node* nx = new Node(a[i]);
                            if (t->next) {
                                nx->next = t->next;
                                t->next = nx;
                            }
                            nx->str.Set_1(i);
                            break;
                        }
                        t = t->next;   
                    }
                }
            }
        }
    }
    return head;
}
int HuffmanCode::countSymbols(std::string nameFile, std::vector<int> &a)
{
    std::ifstream file(nameFile);
    int _symbols = 0;
    char temp;
    while (file.get(temp)) 
    {
//        if (temp == '\n') {
  //          continue;
    //    }
        ++a[(unsigned char)temp];
        ++_symbols;
    }
    file.close();
    std::cout << _symbols << std::endl;
    return _symbols;
}
void HuffmanCode::displayTree(Node*q, int level) const
{
    if (q) {
        displayTree(q->right, level+5);
        for (int i = 0; i < level; ++i) {
            std::cout << " ";
        }
        std::cout << "[" << q->str << "]" << q->count;  
        std::cout << std::endl;
        displayTree(q->left, level+5);
    }
} 
void HuffmanCode::deleteTree(Node* node) 
{
    if (node) {
        if (node->left) {
            deleteTree(node->left);
        }
        if (node->right) {
            deleteTree(node->right);
        }
        delete node;
    }
}


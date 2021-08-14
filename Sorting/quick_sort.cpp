#include <iostream>
#include <fstream>
#include <chrono>
#include <iterator>

void FillArray(int* array, int Range);
void DisplayArray(int* array, int Range);
void swap(int&, int&);
void help_sort(int* a, int left, int right);
bool Is_sort(int* a, int Range);
int helpquick(int* a, int left, int right);
void quicksort(int* a, int left, int right);
double special_function(int* a, int Range);

int main()
{
    int Range;
    std::cin >> Range;
    int* a = new int [Range];
    FillArray(a, Range);
    DisplayArray(a, Range);
    quicksort(a,0, Range-1);
    DisplayArray(a, Range);
    return 0;
}
double special_function(int* array, int Range)
{
    auto t2 = std::chrono::high_resolution_clock::now();
    quicksort(array, 0, Range-1);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::micro> elapsed = t1 - t2;
    std::cout << elapsed.count() / 1000000 << " sec. " << std::endl;
    std::cout << "Sorted ? " << Is_sort(array, Range) << std::endl;
    std::cout << std::endl;
    return elapsed.count();
}

void swap(int& left, int& right)
{
    int temp = right;
    right = left;
    left = temp;
}

void quicksort(int* a, int left, int right)
{
    int i = 0; 
    if (left < right) {
        int index = helpquick(a, left, right);
        quicksort(a, left, index-1);
        quicksort(a, index, right);
    }
}

int helpquick(int* a, int left, int right)
{
    int i = left;
    int j = right;
    int pivot = a[(i + j)/2];
    while (i <= j) {
        while (a[i] < pivot)
            ++i;
        while (a[j] > pivot)
            --j;
        if (i <= j) {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    return i;
}

bool Is_sort(int* array, int Range)
{
    for (int i = 0; i < Range-1; ++i)
        if (array[i] > array[i + 1])
            return false;
    return true;
}

void FillArray(int* array, int Range)
{
    srand(time(NULL));
    for (int i = 0; i < Range; ++i)
        array[i] = rand() % 100 + 1;
}

void DisplayArray(int* array, int Range)
{
    for (int i = 0; i < Range; ++i)
        std::cout << array[i] << "  ";
    std::cout << std::endl;
}

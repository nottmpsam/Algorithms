#include "vector_matrix.h"
#include <vector>
void bMatrix::SupportSort(std::vector<int>& v, bMatrix& copyGraph, bVector& temp)
{
    uc mask;
    for (int j = 0; j < copyGraph.lines; ++j)
    {
        mask = 1;
        do
        {  if (mask & temp[j]) {
                copyGraph[j].SetAll_0(); //удаляем дуги, исходящие с истоков
               v.push_back(j+1);
            }
        } while (mask <<= 1);
    }
}
std::vector<int> bMatrix::SortGraph(){
//Топологическая сортировка - способ упорядочивания вершин ографа таким образом, 
//что каждое ребро ведёт из вершины с меньшим номером в вершину с большим номером
    std::vector<int> (v);
    bMatrix copyGraph = *this;
    bVector temp = copyGraph.Disjunction_M();
    temp = ~temp; //поиск истоков
    bVector forKeep = temp; //хранитель обработанных вершин
    bVector previousvertex;
    //std::cout <<"First Vector : "  <<temp << std::endl;
   // std::cout << "after ~:(forkeep too equal) = " << forKeep << std::endl;
   // Топологическая сортировка работает только для ациклических орграфов. Если
   // наткнёмся на цикл, то temp.WeightOfMatrix() == 0, т.к. истоков не будет
    while (temp.WeightOfVector()){ //пока имеются истоки
        SupportSort(v, copyGraph, temp); //очистка истоков + удаление исходящих дуг
        temp = copyGraph.Disjunction_M();// получение оставшихся вершин
     // std::cout <<"After SupportSort (1): "<<  temp << std::endl;
        previousvertex = ~temp; //для поиска истоков
       // std::cout <<"Previous vertex : " << previousvertex << std::endl;
         forKeep = ~forKeep; 
       // std::cout <<"After ~ forKeep : " << forKeep << std::endl;
        previousvertex &= forKeep; //пересечение вершин с необработанными вершинами 
        //std::cout << "Previous vertex: " << previousvertex << std::endl;
        forKeep = ~forKeep;// возвращаем хранитель
        forKeep|= previousvertex;//обновляем наш хранитель
        std::cout << forKeep << std::endl;
       // std::cout <<"After allforKeep : " << forKeep << std::endl;
        temp = previousvertex; //в темпе теперь хранятся нужные истоки
        std::cout << temp << std::endl;
    //    std::cout << "Position before delete str & rows "  << temp << std::endl;
    }
    if (v.size() !=  rows) { //кол-во истоков != исходному кол-ву вершин графа 
        std::cerr << "Loop in Graph. " << std::endl;
        v.clear();
        v.push_back(-1);
    }
    return v;
    //
 //  1 2 3 4 5   1 2 3 4 5  1 2 3 4 5  1 2 3 4 5  1 2 3 4 5 
 //1 0 1 1 1 1   0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  
 //2 0 0 0 0 0   0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  
 //3 0 1 0 0 0   0 1 0 0 0  0 1 0 0 0  0 1 0 0 0  0 0 0 0 0
 //4 0 0 1 0 0   0 0 1 0 0  0 0 1 0 0  0 0 0 0 0  0 0 0 0 0
 //5 0 1 0 1 0   0 1 0 1 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0
//  
//  1)Удалили вершину 1 и ее дуги.
//  2)Удалили вершину 5 и дуги.
//  3)Удалили вершину 4 и дугу.
//  4)Удалили вершину 3 и дугу.
//  5)Удалили вершину 2.
//  В итоге: 1 5 4 3 2
//  В графах могут быть несколько упорядоченных последовательностей.


}
int main()
{
    int Range;
    std::cin >> Range;
    bMatrix Graph(Range, Range);
    int from, to;
    while(std::cin >> from >> to) {
        if (( from <= 0|| from > Range) || (to <= 0|| to > Range)) {
            std::cout << "Reenter: " << std::endl;
            continue;
        }
        Graph[from-1][to-1] = 1;
    }
    std::vector<int> (v) = Graph.SortGraph();
    for (unsigned long i = 0; i < v.size(); ++i)
        std::cout << v[i] <<  " ";
    std::cout << std::endl;
    return 0;
}

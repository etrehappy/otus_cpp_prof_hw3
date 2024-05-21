#include "my_allocator.h"
#include "forward_list.h"
#include <map>
#include <iostream>

int Factorial(int a)
{
    if (a == 0)
        return 1;

    return a * Factorial(a - 1);
}

template <typename T>
void FillAndPrintMap(T& container, const int max_size)
{
    for (int i = 0; i < max_size; i++)
    {
        container.emplace(i, Factorial(i));
    }

    for (auto& pair : container)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

template <typename T>
void FillAndPrintMyList(T& container, const int max_size)
{
    for (int i = 0; i < max_size; i++)
    {
        container.emplase_back(std::move(i));
    }

    std::cout << container;
}

int main()
{  
    const int max_size{10};

    std::cout << "\n---\tstd::map<int>\t---\n";
    std::map<int, int> container1{};
    FillAndPrintMap(container1, max_size);

    std::cout << "\n---\tstd::map<int> + AssocioPoolAllocator\t---\n";
    std::map<int, int, std::less<int>,
        AssocioPoolAllocator<std::pair<const int, int>, max_size> > container2{};
    FillAndPrintMap(container2, max_size);

    std::cout << "\n---\tForwardList<int>\t---\n";
    ForwardList<int> container3{};
    FillAndPrintMyList(container3, max_size);        

    std::cout << "\n\n---\tForwardList<int> + AssocioPoolAllocator\t---\n";
    ForwardList<int, AssocioPoolAllocator<int, max_size>> container4{};
    FillAndPrintMyList(container4, max_size);        

    return 0;
}
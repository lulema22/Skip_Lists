#include <iostream>
#include "skip_lists.h"
#include "DynamicArrayNew.h"

int main() {
    SkipList<int> skip;
    skip.insert(10);
    skip.insert(20);
    skip.insert(30);
    skip.insert(40);
    skip.insert(50);
    skip.printLevels();

    std::cout << "есть 30: " << (skip.find(30) ? "Да" : "Нет") << std::endl;
    std::cout << "есть 25: " << (skip.find(25) ? "Да" : "Нет") << std::endl;

    std::cout << "\nУдаление" << std::endl;
    skip.delete_elem(30);
    skip.delete_elem(10);
    skip.printLevels();

    std::cout << "\nиз DynamicArray" << std::endl;
    int data[] = {5, 15, 25, 35, 45};
    DynamicArray<int> arr(data, 5);

    SkipList<int> fromArray;
    fromArray.buildFromArray(arr);
    fromArray.printLevels();

    return 0;
}

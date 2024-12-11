#include<iostream>
#include"BinaryTree.h"

int main()
{
    //пустое дерево
    BinaryTree<int> bt1;

    //добавляю элементы
    bt1.put(10);
    bt1.put(9);
    bt1.put(9);
    bt1.put(8);
    bt1.put(7);
    bt1.put(17);
    bt1.put(11);
    bt1.put(23);
    bt1.put(17);

    //вывод в отсортированном виде
    bt1.showSort("BT1");
    
    
    //Тест конструктора копирования
    BinaryTree<int> bt2{bt1};

    bt2.showSort("BT2");


    //Тест конструктора копирования
    BinaryTree<int> bt3;

    //тест присваивания
    bt3 = bt2;

    //несортированный показ
    bt3.show("BT3");

    const int *arr = bt3.toSortArray();

    std::cout << '\n';

    for(int i{0}; i < bt3.size(); ++i) {
        std::cout << arr[i] << " : ";
    }
    std::cout << '\n';

    return 0;
}
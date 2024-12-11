#include<iostream>
#include"BinaryTree.h"

int main()
{
    //������ ������
    BinaryTree<int> bt1;

    //�������� ��������
    bt1.put(10);
    bt1.put(9);
    bt1.put(9);
    bt1.put(8);
    bt1.put(7);
    bt1.put(17);
    bt1.put(11);
    bt1.put(23);
    bt1.put(17);

    //����� � ��������������� ����
    bt1.showSort("BT1");
    
    
    //���� ������������ �����������
    BinaryTree<int> bt2{bt1};

    bt2.showSort("BT2");


    //���� ������������ �����������
    BinaryTree<int> bt3;

    //���� ������������
    bt3 = bt2;

    //��������������� �����
    bt3.show("BT3");

    const int *arr = bt3.toSortArray();

    std::cout << '\n';

    for(int i{0}; i < bt3.size(); ++i) {
        std::cout << arr[i] << " : ";
    }
    std::cout << '\n';

    return 0;
}
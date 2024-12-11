#pragma once
#include<iostream>

template <typename T>
class BinaryTree
{
    private:
    
    
    struct Node
    {
        //��������
        T m_value;

        //���-�� ����������
        int m_count;
        
        //������� �������
        BinaryTree::Node *m_left;

        //������� �������
        BinaryTree::Node *m_right;
    };

    //������
    Node *m_root;
    
    //������ �� ����������(���������������)
    T *m_array;

    //������ �������
    int m_size;


    //���������� ���������� ���� (��������)
    BinaryTree<T>::Node *put(BinaryTree<T>::Node *node, T value);

    //���������� ������������ ������ (��������)
    void freeMem(Node *node);

    //���������� ����������� ������ (��������������� ��������)
    void showSort(Node *node) const;

    //���������� ����������� ������
    void show(Node *node);

    //���������� ����� �������� ������
    BinaryTree<T>::Node *get(Node *node, const T &value) const;

    //���������� ����������� � ������������� ������
    void toSortArray(Node *node, T &current);

    //���������� ���-�� �����
    const int size(Node *node) const;

    //���������� �����������
    void copy(Node **nodeCopy, Node *node);

    public:

    //������������
    //�� ��������� ������ ������
    BinaryTree();

    //����������� �����������
    BinaryTree(const BinaryTree &other)
    {
        copy(&m_root, other.m_root);
    }
    
    //����������
    ~BinaryTree();

    //�������� ������������ ������������
    BinaryTree<T> &operator=(const BinaryTree &right);

    //��������� �������� ����
    void put(const T &value);

    //��������� ����� �������� ������ (0 ���� �������� ���)
    int get(const T &value) const;

    //��������� ����������� ������ (����������������)
    void showSort(const std::string &msg) const;

    //��������� ����������� ������
    void show(const std::string &msg)
    {
        std::cout << msg << " => ";
        show(m_root);

        std::cout << '\n';
    }

    //��������� ����������� � ������������� ������
    const T* toSortArray();

    //��������� ���-�� �����
    const int size() const
    {
        return size(m_root);
    }
};

template <typename T>
BinaryTree<T>::BinaryTree()
{
    m_root = nullptr;
    m_array = nullptr;
    m_size = 0;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    //���������� ������
    freeMem(m_root);

    //����� ������, ���� �� ����
    if(m_size > 0) {
        delete[]m_array;
    }
}

template<typename T>
inline BinaryTree<T> &BinaryTree<T>::operator=(const BinaryTree &right)
{
    if(this != &right) {
        
        freeMem(m_root);

        copy(&m_root, right.m_root);
    }

    return *this;
}

template <typename T>
BinaryTree<T>::Node *BinaryTree<T>::put(BinaryTree<T>::Node *node, T value)
{
    //�������� �� ������ ������
    if(node == nullptr) {

        Node *tmpPtr = new Node;
        tmpPtr->m_value = value;
        tmpPtr->m_count = 1;
        tmpPtr->m_left = nullptr;
        tmpPtr->m_right = nullptr;

        return tmpPtr;
    }

    //���� ���� ������� � ����� ��������� ���������� ���-�� ����������
    if(node->m_value == value) {
        ++node->m_count;
        return node;
    }

    if(node->m_value > value) {
        node->m_left = put(node->m_left, value);
        return node;
    }

    if(node->m_value < value) {
        node->m_right = put(node->m_right, value);
        return node;
    }
}

template <typename T>
BinaryTree<T>::Node *BinaryTree<T>::get(BinaryTree<T>::Node *node, const T &value) const
{
    //������� ������
    if(node == nullptr)
        return nullptr;

    //����� �� ����� �����
    if(node->m_value > value)
        return get(node->m_left, value);

    else
        //����� �� ������ �����
        if(node->m_value < value)
            return get(node->m_right, value);
        else
            return node;
}

template <typename T>
void BinaryTree<T>::toSortArray(BinaryTree<T>::Node *node, T &current)
{
    if(node == nullptr)
        return;

    if(node->m_left != nullptr)
        toSortArray(node->m_left, current);

    for(int i{0}; i < node->m_count; ++i) {
        m_array[current] = node->m_value;
        ++current;
    }

    if(node->m_right != nullptr)
        toSortArray(node->m_right, current);
}

template <typename T>
const int BinaryTree<T>::size(BinaryTree<T>::Node *node) const
{
    if(node == nullptr)
        return 0;

    int tmpCount{0};
    
    if(node->m_left != nullptr)
        tmpCount += size(node->m_left);

    if(node->m_right != nullptr)
        tmpCount += size(node->m_right);

    return tmpCount + node->m_count;
}

template<typename T>
inline void BinaryTree<T>::copy(Node **nodeCopy, BinaryTree<T>::Node *node)
{
    if(node == nullptr)
        return;

    //����������� ������
    *nodeCopy = new Node;
    (*nodeCopy)->m_value = node->m_value;
    (*nodeCopy)->m_count = node->m_count;
    (*nodeCopy)->m_left = nullptr;
    (*nodeCopy)->m_right = nullptr;

    //�������� �� ��������� �������
    copy(&(*nodeCopy)->m_left, node->m_left);
    copy(&(*nodeCopy)->m_right, node->m_right);
}

template <typename T>
void BinaryTree<T>::put(const T &value) 
{
    //����� ���������� ���������� ����
    if(m_root == nullptr) {
        m_root = put(m_root, value);
    } else {
        put(m_root, value);
    }
}
template <typename T>
int BinaryTree<T>::get(const T &value) const
{
    //��� �������
    Node *tmpPtr = get(m_root, value);

    //���� ��� �� ��������� 0
    if(tmpPtr == nullptr)
        return 0;

    //���� ���� ���-�� ���������� ��������
    return tmpPtr->m_count;
}

template <typename T>
void BinaryTree<T>::freeMem(Node *node)
{
    if(node == nullptr)
        return;
    
    if(node->m_left != nullptr)
        freeMem(node->m_left);

    if(node->m_right != nullptr)
        freeMem(node->m_right);

    delete node;
}

template <typename T>
void BinaryTree<T>::showSort(Node *node) const
{
    if(node == nullptr)
        return;

    if(node->m_left != nullptr) {
        showSort(node->m_left);
    }

    std::cout << node->m_value << ':' << node->m_count << ' ';

    if(node->m_right != nullptr) {
        showSort(node->m_right);
    }
}

template<typename T>
inline void BinaryTree<T>::show(Node *node)
{
    if(node == nullptr)
        return;

    std::cout << node->m_value << ':' << node->m_count << ' ';

    show(node->m_left);
    show(node->m_right);
}

template <typename T>
void BinaryTree<T>::showSort(const std::string &msg) const
{
    std::cout << msg << " => ";
    showSort(m_root);
    std::cout << '\n';
}

template <typename T>
const T *BinaryTree<T>::toSortArray()
{
    m_size = size();
    m_array = new T[m_size];
    m_size = 0;

    toSortArray(m_root, m_size);

    return m_array;
}
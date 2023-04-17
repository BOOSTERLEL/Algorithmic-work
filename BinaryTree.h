//
// Created by pzd123 on 2023/4/8.
//

#ifndef TEST_BINARYTREE_H
#define TEST_BINARYTREE_H

#include <iostream>
#include <queue>
#include <deque>
#include <stack>
#include <string>

namespace ast {
#define INF 32767

    /**
     * �����﷨���Ľ��
     * @tparam T ��������
     */
    template<typename T>
    struct BinaryNode {
        T value;
        int cost[3] = {0, 1, 1};
        //�������ͣ�0-���浽�ڴ棬1-����Ĵ���R0��2-����Ĵ���R1��3-���������Ĵ���
        int usageType;
        std::string code;
        BinaryNode<T> *leftChild, *rightChild;

        BinaryNode() {}

        BinaryNode(T val) { this->value = val; }

        BinaryNode(T element, BinaryNode<T> *lt, BinaryNode<T> *rt) : value(element), leftChild(lt), rightChild(rt) {}
    };

    /**
     * �����﷨��
     * @tparam T ��������
     */
    template<typename T>
    class BinaryTree {
    public:
        BinaryTree();

        BinaryTree(BinaryNode<T> *binaryNode);

        ~BinaryTree();

        void LevelTravel() const;

        void LevelTravelBottom(std::vector<std::vector<T> > &result) const;

        void CostCalculate() const;

        void CodeGenerate() const;

    private:
        void CreatBinaryTree(BinaryNode<T> **pBinaryNode);

        void ReleaseBinaryTree(BinaryNode<T> **pBinaryNode);

        void LevelTravel(BinaryNode<T> *binaryNode) const;

        void LevelTravelBottom(std::vector<std::vector<T> > &result, BinaryNode<T> *binaryNode) const;

        void CostCalculate(BinaryNode<T> *binaryNode) const;

        void CodeGenerate(BinaryNode<T> *binaryNode) const;

        BinaryNode<T> *root;
    };
}

#endif //TEST_BINARYTREE_H

//
// Created by pzd123 on 2023/4/8.
//

#include <iostream>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include "BinaryTree.h"

using namespace std;

namespace ast {
    template<typename T>
    BinaryTree<T>::BinaryTree() {
        CreatBinaryTree(&root);
    }

    template<typename T>
    BinaryTree<T>::BinaryTree(BinaryNode<T> *binaryNode) {
        root = binaryNode;
    }

    template<typename T>
    void BinaryTree<T>::CreatBinaryTree(BinaryNode<T> **pBinaryNode) {
        T data;
        cin.clear();
        cin.sync();
        cin >> data;
        if (isalpha(data)) {
            *pBinaryNode = new BinaryNode<T>(data, nullptr, nullptr);
        } else {
            *pBinaryNode = new BinaryNode<T>(data, nullptr, nullptr);
            CreatBinaryTree(&((*pBinaryNode)->leftChild));
            CreatBinaryTree(&((*pBinaryNode)->rightChild));
        }
    }

    template<typename T>
    BinaryTree<T>::~BinaryTree() {
        ReleaseBinaryTree(&root);
    }

    /**
     * �ͷŽ��
     * @tparam T ��������
     * @param pBinaryNode ���
     */
    template<typename T>
    void BinaryTree<T>::ReleaseBinaryTree(BinaryNode<T> **pBinaryNode) {
        if (*pBinaryNode != NULL) {
            ReleaseBinaryTree(&(*pBinaryNode)->leftChild);
            ReleaseBinaryTree(&(*pBinaryNode)->rightChild);
            delete (*pBinaryNode);
        }
    }

    /**
     * �ֲ����������
     * @tparam T ��������
     */
    template<typename T>
    void BinaryTree<T>::LevelTravel() const {
        LevelTravel(root);
    }

    template<typename T>
    void BinaryTree<T>::LevelTravel(BinaryNode<T> *binaryNode) const {
        queue<BinaryNode<T>> q;
        if (binaryNode != nullptr) {
            q.push(*binaryNode);
        }
        while (!q.empty()) {
            BinaryNode<T> BinaryNode = q.front();

            cout << BinaryNode.value << " ";
            cout << "cost: ";
            for (int i = 0; i < 3; ++i) {
                cout << BinaryNode.cost[i] << " ";
            }
            cout << endl;

            cout << "register: " << BinaryNode.usageType;
            cout << endl;

            q.pop();
            if (BinaryNode.leftChild != nullptr) {
                q.push(*(BinaryNode.leftChild));
            }
            if (BinaryNode.rightChild != nullptr) {
                q.push(*(BinaryNode.rightChild));
            }
        }
    }

    /**
     * �Ե����Ϸֲ����������
     * @tparam T ��������
     * @param result �������
     */
    template<typename T>
    void BinaryTree<T>::LevelTravelBottom(std::vector<std::vector<T> > &result) const {
        LevelTravelBottom(result, root);
    }

    template<typename T>
    void BinaryTree<T>::LevelTravelBottom(std::vector<std::vector<T> > &result, BinaryNode<T> *binaryNode) const {
        queue<BinaryNode<T> *> q;
        stack<vector<T> > s;
        BinaryNode<T> *node;

        if (binaryNode) {
            q.push(binaryNode);
        }

        while (!q.empty()) {
            int size = q.size();
            vector<T> level;
            for (int i = 0; i < size; ++i) {
                node = q.front();
                q.pop();
                level.push_back(node->value);

                if (node->leftChild) {
                    q.push(node->leftChild);
                }
                if (node->rightChild) {
                    q.push(node->rightChild);
                }

            }
            s.push(level);
        }

        while (!s.empty()) {
            vector<T> temp = s.top();
            result.push_back(s.top());
            s.pop();
        }
    }

    /**
     * �����������
     * @tparam T ��������
     */
    template<typename T>
    void BinaryTree<T>::CostCalculate() const {
        CostCalculate(root);
    }

    template<typename T>
    void BinaryTree<T>::CostCalculate(BinaryNode<T> *binaryNode) const {
        if (binaryNode == nullptr) {
            return;
        }
        if (binaryNode->leftChild) {
            CostCalculate(binaryNode->leftChild);
        }
        if (binaryNode->rightChild) {
            CostCalculate(binaryNode->rightChild);
        }
        if (!isalpha(binaryNode->value)) {
            binaryNode->cost[1] = binaryNode->leftChild->cost[1] + binaryNode->rightChild->cost[0] + 1;

            set<int> values;
            values.insert(binaryNode->leftChild->cost[2] + binaryNode->rightChild->cost[1] + 1);
            values.insert(binaryNode->rightChild->cost[2] + binaryNode->leftChild->cost[1] + 1);
            values.insert(binaryNode->rightChild->cost[0] + binaryNode->leftChild->cost[2] + 1);

            binaryNode->cost[2] = *values.begin();
            binaryNode->cost[0] = min(binaryNode->cost[1], binaryNode->cost[2]) + 1;
        }
    }

    /**
     * ��������
     */
    template<typename T>
    void BinaryTree<T>::CodeGenerate() const {
        root->usageType = 3;
        return CodeGenerate(root);
    }

    template<typename T>
    void BinaryTree<T>::CodeGenerate(BinaryNode<T> *binaryNode) const {
        if (!isalpha(binaryNode->value)) {  // ��Ҷ�ӽ��

            if (binaryNode->usageType == 3) {   // �����Ĵ���
                if (binaryNode->cost[1] > binaryNode->cost[2]) {
                    binaryNode->rightChild->usageType = 3;
                    binaryNode->leftChild->usageType = 2;
                    CodeGenerate(binaryNode->rightChild);
                    CodeGenerate(binaryNode->leftChild);
                } else {
                    binaryNode->leftChild->usageType = 1;
                    binaryNode->rightChild->usageType = 0;
                    CodeGenerate(binaryNode->leftChild);
                    CodeGenerate(binaryNode->rightChild);
                }
            } else {    // һ���Ĵ���
                binaryNode->leftChild->usageType = 0;
                binaryNode->rightChild->usageType = binaryNode->usageType;
                CodeGenerate(binaryNode->leftChild);
                CodeGenerate(binaryNode->rightChild);
            }

            // ������
            switch (binaryNode->value) {
                case '+':
                    binaryNode->code = "ADD R";
                    break;
                case '-':
                    binaryNode->code = "SUB R";
                    break;
                case '*':
                    binaryNode->code = "MUL R";
                    break;
                case '/':
                    binaryNode->code = "DIV R";
                    break;
                default:
                    break;
            }

            int rUse = binaryNode->rightChild->usageType;
            int lUse = binaryNode->leftChild->usageType;
            if (binaryNode->usageType == 3) {   // �����Ĵ���������浽R0��
                binaryNode->code += "0,R" + to_string(lUse - 1) + ", ";
            } else {
                if (lUse == 0) {    // ������������ڴ�
                    binaryNode->code +=
                            to_string(rUse - 1) + ", R" +
                            to_string(rUse - 1) + ", ";
                } else {    // ����������ڼĴ���
                    binaryNode->code +=
                            to_string(lUse - 1) + ", R" +
                            to_string(lUse - 1) + ", ";
                }
            }

            if (rUse == 0 || lUse == 0) {   // ��һ��������ڴ�
                binaryNode->code += rUse > lUse ? binaryNode->leftChild->value : binaryNode->rightChild->value;
            } else {    // �Ҳ�����
                if (rUse == 3) {
                    binaryNode->code += "R0";
                } else {
                    binaryNode->code += "R" + to_string(rUse - 1);
                }
            }

        } else {    // Ҷ�ӽ��
            if (binaryNode->usageType == 3) {
                binaryNode->code = "LD R0, " + to_string(binaryNode->value);
            } else {
                if (binaryNode->usageType != 0) {
                    binaryNode->code = "LD R" + to_string(binaryNode->usageType - 1) + ", " + binaryNode->value;
                }
            }
        }

        // ������
        if (!binaryNode->code.empty()) {
            cout << binaryNode->code << endl;

            // �������ڴ�
            if (binaryNode->usageType == 0 && !isalpha(binaryNode->value)) {
                cout << "ST m, " << to_string(binaryNode->usageType - 1);
                binaryNode->value = 'm';
            }
        }
    }
}
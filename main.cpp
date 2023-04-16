#include <bits/stdc++.h>

using namespace std;

#include "BinaryTree.h"
#include "BinaryTree.cpp"

int main() {
    BinaryTree<char> *binaryTreePtr=new BinaryTree<char>;

    binaryTreePtr->CostCalculate();
    binaryTreePtr->CodeGenerate();
    binaryTreePtr->LevelTravel();
    return 0;
}
#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// complete binary tree
struct tNode { 
    int digit; // значение
    tNode* left; // указатель на левый узел
    tNode* right; // указатель на правый узел
    int height; // высота поддерева с корнем в данном узле

    tNode(int dig) : digit(dig), left(nullptr), right(nullptr), height(1) {} // конструктор для создания нового узла с заданным значением
};

struct avl {
    int getHeight(tNode* currentNode) { // получение высоты узла
        if (!currentNode) { // если узла не существует
            return 0;
        }
        return currentNode->height;
    }

    int getBalance(tNode* currentNode) { // вычисление разницы высот
        if (!currentNode) { // если узла не существует
            return 0;
        }
        return getHeight(currentNode->left) - getHeight(currentNode->right); // высота левого поддерева минус высота правого
    }

    tNode* rightRotate(tNode* currentNode) { // правый поворот
        tNode* nodeLeft = currentNode->left; // левый потомок заданного узла
        tNode* nodeLeftR = nodeLeft->right; // правый потомок левого потомка заданного узла
        nodeLeft->right = currentNode; // заданный узел становится правым потомком его изначального левого потомка
        currentNode->left = nodeLeftR; // правый потомок становится левым потомком заданного узла
        currentNode->height = max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1; //обновляем высоту для заданного узла
        nodeLeft->height = max(getHeight(nodeLeft->left), getHeight(nodeLeft->right)) + 1; // обновляем высоту для его изначального левого потомка
        return nodeLeft; // теперь старый левый потомок - корень поддерева
    }

    tNode* leftRotate(tNode* currentNode) { // левый поворот
        tNode* nodeRight = currentNode->right; // правый потомок заданного узла
        tNode* nodeRightL = nodeRight->left; // левый потомок правого потомка заданного узла
        nodeRight->left = currentNode; // корень теперь становится левым потомков его старого правого потомка
        currentNode->right = nodeRightL; // старый правый потомок становится левым потомком старого корня
        currentNode->height = max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1; // обновляем высоту дла нового левого потомка корня
        nodeRight->height = max(getHeight(nodeRight->left), getHeight(nodeRight->right)) + 1; // обновляем высоту нового корня
        return nodeRight; // новый корень поддерева
    }
    
    tNode* insert(tNode* currentNode, int digit) { // функция вставки
        if (!currentNode) { // создаём новый узел с заданным значением
            return new tNode(digit);
        }
        if (digit < currentNode->digit) { // если новое число меньше числа в узле
            currentNode->left = insert(currentNode->left, digit); // будем вставлять его слева
        }
        else if (digit > currentNode->digit) { // если новое число больше числа в узле
            currentNode->right = insert(currentNode->right, digit); // будем вставлять его справа
        }
        else { // игнорируем дубликаты
            return currentNode;
        }
        currentNode->height = max(getHeight(currentNode->left), getHeight(currentNode->right)) + 1; // обновляем высоту
        int balance = getBalance(currentNode); // получаем информацию о балансе дерева
        if (balance > 1 && digit < currentNode->left->digit) { // если число меньше числа левого дочернего узла
            return rightRotate(currentNode); 
        }
        if (balance > 1 && digit > currentNode->left->digit) { // если число больше числа левого дочернего узла
            currentNode->left = leftRotate(currentNode->left);
            return rightRotate(currentNode);
        }
        if (balance < -1 && digit > currentNode->right->digit) { // если число больше числа правого дочернего узла
            return leftRotate(currentNode);
        }
        if (balance < -1 && digit < currentNode->right->digit) { // если число меньше числа правого дочернего узла
            currentNode->right = rightRotate(currentNode->right);
            return leftRotate(currentNode);
        }
        return currentNode;
    }

    void printAvl(tNode* currentNode, int level) { // вывод дерева
        if (currentNode) { // пока текущий указатель не указывает на nullptr
            printAvl(currentNode->right, level + 1); // начинаем с правого узла
            for (int i = 0; i < level; i++) {
                cout << "   "; // вывод нужного количества табуляции
            }
            cout << currentNode->digit << endl; 
            printAvl(currentNode->left, level + 1); // обработка левых узлов
        }
    }
};
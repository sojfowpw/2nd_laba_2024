#pragma once
#include <iostream>
#include <string>

using namespace std;
// односвязный список
struct Node { // узел связного списка
    string item; // значение узла
    Node* next; // указатель на следующий узел

    Node(string _item) : item(_item), next(nullptr) {} // конструктор для создания нового узла с заданным значением
};

struct singlyList {
    Node* first; // указатель на 1 узел
    Node* last; // указатель на последний узел
    singlyList() : first(nullptr), last(nullptr) {} // конструктор для создания пустого списка

    ~singlyList() { 
        while (first) {
            Node* newNode = first; // указатель на текущий узел
            first = first->next; // перемещаем указатель на следующий узел
            delete newNode; // освобождаем память текущего узла
        }
    }

    bool is_empty() { // проверка, пустой ли список
        return first == nullptr; // если 1 узел пустой - список пустой
    }

    void addToEnd(string _item) { // добавление нового узла в конец списка
        Node* newNode = new Node(_item); // создаём новый узел с заданным значением
        if (is_empty()) { // если список пустой
            first = newNode; // новый узел становится первым
            last = newNode; // и последним
            return;
        } // если список не пустой:
        last->next = newNode; // новый узел добавляется в конец
        last = newNode; // и становится последним (указатель на новый узел)
    }

    void addToHead(string _item) { // добавление нового узла в начало списка
        Node* newNode = new Node(_item); // создаём новый узел с заданным значением
        if (is_empty()) { // если список пустой
            first = newNode; //новый узел становится первым
            last = newNode; // и последним
            return;
        }
        newNode->next = first; // новый узел привязывается к старому первому элементу
        first = newNode; // новый узел становится первым
    }

    void delFromHead() { // удаление первого узла
        if (is_empty()) { // проверка на пустоту 
            cout << "Список пуст.\n";
            return;
        }
        Node* newNode = first; // новый узел становится первым
        first = newNode->next; // голова теперь указывает на второй узел
        delete newNode; // удаляем старый первый узел
    }

    void printList() { // вывод всех элементов списка
        if(is_empty()) { // если список пуст
            cout << "Список пуст.\n";
            return;
        }
        Node* newNode = first; // начинаем с первого узла
        while (newNode) { // пока указатель не равен nullptr
            cout << newNode->item << " "; // выводим значения
            newNode = newNode->next; // переходим к следующему узлу
        }
        cout << endl;
    }

    int countSize() { // количество узлов в списке
        int size = 0;
        Node* newNode = first;
        while (newNode) {
            size++;
            newNode = newNode->next;
        }
        return size;
    }
};
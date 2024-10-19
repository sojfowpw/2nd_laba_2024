#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int tableSize = 100;

struct hNode { // структура таблицы
    string key;   // ключ
    string item; // значение 
    hNode* next;  // указатель на следующий элемент
};

struct hashTable {
    hNode** table; // массив указателей на узлы
    int currentIndex; // текущий индекс для добавления элементов

    hashTable() : currentIndex(0) {
        table = new hNode * [tableSize]; // выделение памяти под массив указателей
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr; // инициализируем каждый элемент nullptr
        }
    }

    bool isEmpty() {
        return currentIndex == 0;
    }

    void insert(hashTable& ht, const string& key, const string& item) { // добавление элемента
        if (get(ht, key) != "") {
            cout << "Такой ключ уже есть.\n";
            return;
        }
        hNode* newNode = new hNode{ key, item, table[currentIndex] }; // создаём новый первый узел для индекса
        table[currentIndex] = newNode; // новый узел становится первым
        currentIndex++;
    }

    string get(hashTable& ht, const string& key) { // получение значения элемента по ключу
        for (int i = 0; i < ht.currentIndex; i++) {
            hNode* current = ht.table[i];   // указатель на первый элемент цепочки
            while (current) { // ищем узел
                if (current->key == key) {
                    return current->item; // возвращаем значение узла
                }
                current = current->next;
            }
        }
        return ""; // если ключ не найден, возвращаем пустую строку
    }

    void del(hashTable& ht, const string& key) { // удаление элемента по ключу
        for (int i = 0; i < ht.currentIndex; i++) {
            hNode* current = ht.table[i]; // указатель на первый элемент цепочки
            hNode* prev = nullptr; // новый указатель
            while (current && current->key != key) { // поиск нужного узла
                prev = current;         // новый указатель указывает на предыдущий узел
                current = current->next;
            }
            if (current == nullptr) { // узел не найден
                continue;
            }
            if (prev) {
                prev->next = current->next; // связываем предыдущий узел с последующим
            }
            else {
                ht.table[i] = current->next; // если удаляемый узел был первым, обновляем начало цепочки
            }
            delete current;
            return;
        }
    }

    void printHashTable(const hashTable& ht) { // вывод таблицы
        for (int i = 0; i < tableSize; i++) {
            hNode* current = ht.table[i]; // указатель на первый элемент
            if (current) { 
                cout << i << ": ";
                while (current) {
                    cout << "{" << current->key << ", " << current->item << "} ";
                    current = current->next;
                }
                cout << endl;
            }
        }
    }

    void clear(hashTable& ht) { // очистка и освобождение памяти
        for (int i = 0; i < tableSize; i++) {
            hNode* current = ht.table[i]; // указатель на первый элемент
            while (current != nullptr) {
                hNode* newNode = current; // указатель на текущий узел
                current = current->next; 
                delete newNode; // освобождаем память
            }
            ht.table[i] = nullptr;
        }
        if (ht.table != nullptr) { // проверка на nullptr
            delete[] ht.table; // освобождаем память, выделенную под массив указателей
            ht.table = nullptr; // устанавливаем указатель на nullptr, чтобы избежать двойного удаления
        }
    }

    string traverseTable(hashTable& ht) {
        string currentKey = ht.table[0]->key;
        string currentValue;
        string delKey = currentKey;
        while (true) {
            currentValue = ht.get(ht, currentKey);
            if (currentValue.empty()) {
                del(ht, delKey);
                return currentKey;
            }
            delKey = currentKey;
            currentKey = currentValue;
        }
    }
};
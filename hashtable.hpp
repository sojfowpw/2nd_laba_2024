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

    hashTable() {
        table = new hNode * [tableSize]; // выделение памяти под массив указателей
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr; // инициализируем каждый элемент nullptr
        }
    }

    int func(const string& key) { // хэш-функция djb2
        int hash = 5381;
        for (auto ch : key) {
            hash = (((hash << 5) + hash) + ch) % tableSize; // hash * 33 + ch
        }
        return hash;
    }

    void insert(hashTable& ht, const string& key, const string& item) { // вставка
        int index = func(key);
        hNode* newNode = new hNode{ key, item, table[index] }; // создаём новый узел
        table[index] = newNode; // новый узел становится первым в цепочке
    }

    void update(hashTable& ht, const string& key, const string& newValue) { // обновление элемента по ключу
        unsigned index = func(key);
        hNode* current = table[index]; // указатель на первый элемент цепочки
        while (current) { // ищем узел
            if (current->key == key) {
                current->item = newValue; // обновляем значение узла
                return;
            }
            current = current->next;
        }
    }

    string get(const string& key) { // получение элемента по ключу
        int index = func(key);
        hNode* current = table[index]; // указатель на первый элемент цепочки
        while (current) { // ищем узел
            if (current->key == key) {
                return current->item; // возвращаем значение узла
            }
            current = current->next;
        }
        return "-1"; // если ключ не найден, возвращаем -1
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
};
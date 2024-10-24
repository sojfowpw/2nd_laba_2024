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

    void initialisation(hashTable& ht) { // инициализация и выделение памяти
    ht.table = new hNode * [tableSize]; // выделение памяти под массив указателей
    for (int i = 0; i < tableSize; i++) {
        ht.table[i] = nullptr; // инициализируем каждый элемент nullptr
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
        if (get(key) != "-1") {
        return;
    }
        hNode* newNode = new hNode{ key, item, table[index] }; // создаём новый узел
        table[index] = newNode; // новый узел становится первым в цепочке
    }

    void del(hashTable& ht, const string& key) { // удаление элемента по ключу
    unsigned index = func(key); // индекс через хэш-функцию
    hNode* current = ht.table[index]; // указатель на первый элемент цепочки
    hNode* newNode = nullptr; // новый указатель
    while (current && current->key != key) { // поиск нужного узла
        newNode = current;         // новый указатель указывает на предыдущий узел
        current = current->next;
    }
    if (current == nullptr) { // узел не найден
        cout << "Узел не найден.\n";
        return;
    }
    if (newNode) {
        newNode->next = current->next; // связываем предыдущий узел с последующим
    }
    else {
        ht.table[index] = current->next; // если удаляемый узел был первым, обновляем начало цепочки
    }
    delete current;
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

    int getSet(const string& key) { // получение элемента по ключу
        if (get(key) == "-1") {
            return -1;
        }
        int index = func(key);
        return index;
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

    void saveToFile(hashTable& ht, const string& file) { // запись в файл
        ofstream save(file);
        if (!save) {
            cout << "Не удалось открыть файл.\n";
            return;
        }
        for (int i = 0; i < tableSize; i++) {
            hNode* current = ht.table[i]; // указатель на первый элемент
            while (current) {
                save << current->key << endl;
                current = current->next;
            }
        }
        save.close();
        clear(ht); // очистка таблицы
        initialisation(ht);
    }

    void loadFromFile(hashTable& ht, const string& file) { // запись из файла
        clear(ht); // очистка таблицы
        initialisation(ht);
        ifstream load(file);
        if (!load) { 
            cout << "Не удалось открыть файл.\n";
            return;
        }
        string str;
        while (getline(load, str)) { // читаем файл построчно
            if (str.empty()) { // проверка на пустоту
                continue;
            }
        string key = str; // записываем ключ
        insert(ht, key, "0");
        }
        load.close();
    }
};
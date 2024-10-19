#include <iostream>
#include <sstream>
#include "hashtable.hpp"
#include "singly linked list.hpp"

using namespace std;

int main() {
    string command;
    singlyList tasks;
    hashTable ht = hashTable();
    getline(cin, command);
    istringstream iss(command);
    string word;
    iss >> word; // "вставка"
    if (word != "вставка") {
        cerr << "Некорректная команда.\n";
        return 0;
    }
    iss >> word; // "="
    if (word != "=") {
        cerr << "Некорректная команда.\n";
        return 0;
    }
    string values; // вытаскиваем значения задач
    while (word[word.size() - 2] != ']') { 
        iss >> word;
        values += word;
    }
    string v; // текущая задача
    for (size_t i = 0; i < values.size(); i++) {
        if (values[i] == '\'') {
            i++;
            while (values[i] != '\'') {
                v += values[i];
                i++;
            }
            tasks.addToEnd(v); // добавляем в лист задач
            v = "";
        }
    }
    iss >> word; // "зависимости"
    if (word != "зависимости") {
        cerr << "Некорректная команда.\n";
        return 0;
    }
    iss >> word; // "="
    if (word != "=") {
        cerr << "Некорректная команда.\n";
        return 0;
    }
    values = "";
    while (word[word.size() - 1] != ']') { // вытаскиваем зависимости
        iss >> word;
        values += word;
    }
    string key, item; // первое значение ключ, второе элемент
    size_t pos = 0;
    if (values[pos] == '[') {
        pos++;
    }
    while (pos < values.size()) {
        if (values[pos] == ']') {
            break;
        }
        if (values[pos] == '(') {
            pos++;
        }
        while (pos < values.size() && values[pos] != ',' && values[pos] != ')') {
            if (values[pos] != ' ' && values[pos] != '\'') {
                key += values[pos];
            }
            pos++;
        }
        while (pos < values.size() && (values[pos] == ',' || values[pos] == ' ')) {
            pos++;
        }
        while (pos < values.size() && values[pos] != ',' && values[pos] != ')') {
            if (values[pos] != ' ' && values[pos] != '\'') {
                item += values[pos];
            }
            pos++;
        }
        ht.insert(ht, key, item);
        key = "";
        item = "";
        while (pos < values.size() && (values[pos] == ')' || values[pos] == ',' || values[pos] == ' ')) {
            pos++;
        }
    }
    ht.printHashTable(ht);
    singlyList stack;
    stack.addToHead(ht.traverseTable(ht));
    stack.printList();
    ht.printHashTable(ht);
    stack.addToHead(ht.traverseTable(ht));
    stack.printList();
    ht.printHashTable(ht);
    return 0;
}
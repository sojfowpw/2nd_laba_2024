#include <iostream>
#include <sstream>
#include "hashtable.hpp"
#include "singly linked list.hpp"

using namespace std;

struct ArrayOfLinkedLists { // массив связных списков, где индекс - хэш-функция ключа, связный список - зависимости элемента
    singlyList* lists; // указатель на массив
    int size;

    ArrayOfLinkedLists(int size) : size(size) { // выделение памяти (конструктор)
        lists = new singlyList[size];
    }

    ~ArrayOfLinkedLists() { // освобождение памяти (деструктор)
        delete[] lists;
    }

    singlyList& operator[](int index) { // перегрузка оператора индексации для доступа к элементам массива по индексу
        return lists[index];
    }
};

bool topologicalSort(singlyList& tasks, hashTable& ht) { // топологическая сортировка
    hashTable inDegree = hashTable(); // хэш-таблица для входящих степеней каждой задачи
    hashTable graph = hashTable(); // граф
    ArrayOfLinkedLists adjacencyList(tableSize); // массив связных списков

    Node* newNode = tasks.first;
    while (newNode) { // заполняем граф и таблицу со степенями задачами и нулями 
        inDegree.insert(inDegree, newNode->item, "0");
        graph.insert(graph, newNode->item, "0");
        newNode = newNode->next;
    }

    for (size_t i = 0; i < tableSize; i++) { 
        hNode* current = ht.table[i];
        if (current) {
            string from = current->key;
            string to = current->item;
            int index = graph.func(from);
            adjacencyList[index].addToHead(to); // заполняем массив
            inDegree.update(inDegree, to, to_string(stoi(inDegree.get(to)) + 1)); // изменяем степень вхождения задач
        }
    }

    singlyList stack; // стэк задач
    Node* currentTask = tasks.first; 
    while (currentTask) {
        if (inDegree.get(currentTask->item) == "0") { // ищем задачу, у которой степень вхождения 0
            stack.addToHead(currentTask->item);
        }
        currentTask = currentTask->next;
    }

    int count = 0; // счетчик задач, которые возможно выполнить
    while (!stack.is_empty()) {
        string current = stack.first->item; // обрабатываем первое значение из стэка
        stack.delFromHead();
        count++;

        int index = graph.func(current);
        Node* arrNode = adjacencyList[index].first; // проходимся по массиву
        while (arrNode) {
            string newKey = arrNode->item; // ключ равен предыдущему обрабатываемому значению
            string currentDegree = inDegree.get(newKey); // получаем степень вхождения
            if (currentDegree.empty()) {
                currentDegree = "0";
            }
            inDegree.update(inDegree, newKey, to_string(stoi(currentDegree) - 1)); // уменьшаем степень вхождения
            if (inDegree.get(newKey) == "0") { // если степень вхождения 0 - задачу можно выполнить
                stack.addToHead(newKey);
            }
            arrNode = arrNode->next;
        }
    }
    return count == tasks.countSize(); // сравниваем количество задач в листе и счетчик
}

int main() {
    string command;
    singlyList tasks; // лист со всеми задачами
    hashTable ht = hashTable(); // хэш-таблица с зависимостями
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
        ht.insert(ht, key, item); // заполняем хэш-таблицу
        key = "";
        item = "";
        while (pos < values.size() && (values[pos] == ')' || values[pos] == ',' || values[pos] == ' ')) {
            pos++;
        }
    }
    if (topologicalSort(tasks, ht)) { // если количество задач в списке = количеству выполненных задач
        cout << "Возможно.\n";
    }
    else {
        cout << "Невозможно.\n";
    }
    return 0;
}
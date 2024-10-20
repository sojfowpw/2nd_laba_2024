#include "set.hpp"

set mySet; // инициализация сета

void commands (const string& query) {
    istringstream iss(query); // поток ввода для обработки строки команды
    string cmd;
    iss >> cmd; // "--file"
    if (cmd != "--file") {
        cerr << "Некорректная команда.\n";
        return;
    }
    string fileName;
    iss >> fileName; // имя файла
    iss >> cmd; // "--query"
    if (cmd != "--query") {
        cerr << "Некорректная команда.\n";
        return;
    }
    iss >> cmd;

    if (cmd == "SETADD") { // добавление
        mySet.loadFromFile(fileName);
        int value;
        iss >> value;
        mySet.addToEnd(value);
        mySet.quickSort(0, mySet.size - 1);
        mySet.saveToFile(fileName);
    }
    else if (cmd == "SETDEL") { // удаление по индексу
        mySet.loadFromFile(fileName);
        int index;
        iss >> index;
        mySet.delByIndex(index);
        mySet.saveToFile(fileName);
    }
    else if (cmd == "SET_AT") { // поиск по значению
        mySet.loadFromFile(fileName);
        int value;
        iss >> value;
        mySet.findByItem(value);
    }
    else {
        cout << "Неизвестная команда.\n";
    }
}

int main() {
    string query;
    getline(cin, query);
    commands(query);
}
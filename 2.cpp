#include "set.hpp"
#include "hashtable.hpp"

hashTable ht; // инициализация сета

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
        ht.loadFromFile(ht, fileName);
        int value;
        iss >> value;
        ht.insert(ht, to_string(value), "0");
        ht.saveToFile(ht, fileName);
    }
    else if (cmd == "SETDEL") { // удаление по значению
        ht.loadFromFile(ht, fileName);
        int value;
        iss >> value;
        ht.del(ht, to_string(value));
        ht.saveToFile(ht, fileName);
    }
    else if (cmd == "SET_AT") { // поиск по значению
        ht.loadFromFile(ht, fileName);
        int value;
        iss >> value;
        int ind = ht.getSet(to_string(value));
        if (ind >= 0 && ind <= 100) {
            cout << "Элемент " << value << " есть в множестве.\n";
        }
        else {
            cout << "Элемента " << value << " нет во множестве.\n";
        }
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
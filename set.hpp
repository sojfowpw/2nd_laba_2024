#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct set { // динамический массив строк
    int* arr; // указатель на массив
    size_t size; // текущий размер
    size_t capacity; // максимальный размер

    set(size_t cap = 15) : size(0), capacity(cap) {
        arr = new int[capacity];
    }

    ~set() {
        delete[] arr;
    }

    void resize() { // расширение
        capacity *= 2; // увеличиваем максимальный размер в 2 раза
        int* newArr = new int[capacity]; // выделяем память для нового массива
        for (size_t i = 0; i < size; ++i) {
            newArr[i] = arr[i]; // копируем элементы в новый массив
        }
        delete[] arr; // удаляем старый массив
        arr = newArr;
    }

    void addToEnd(int item) { // добавление элемента в конец
        if (isExist(item) == true) { // элемент не может дублироваться
            return;
        }
        if (size >= capacity) { // если текущий размер больше максимального, увеличиваем размер массива
            resize();
        }
        arr[size++] = item; // добавляем элемент в конец
    }

    void delByIndex(size_t index) { // удаление элемента по индексу
        if (size == 0) { // проверка на пустоту
            cout << "Массив пуст.\n";
            return;
        }
        if (index >= size) { // проверка на недопустимый индекс
            cout << "Недопустимый индекс.\n";
            return;
        }
        for (size_t i = index; i < size - 1; ++i) { // сдвигаем элементы влево на один
            arr[i] = arr[i + 1];
        }
        --size; // уменьшаем текущий размер
    }

    void findByItem(int item) { // чтение (поиск элемента по значению)
        if (size == 0) { // проверка на пустоту
            cout << "Массив пуст.\n";
            return;
        }
        for (size_t i = 0; i < size; i++) { // проходимся по массиву
            if (arr[i] == item) {
                cout << "Индекс элемента: " << i << endl;
                return;
            }
        }
        cout << "Элемент не найден.\n";
    }

    bool isExist(int item) { // чтение (поиск элемента по значению)
        if (size == 0) { // проверка на пустоту
            return false;
        }
        for (size_t i = 0; i < size; i++) { // проходимся по массиву
            if (arr[i] == item) {
                return true;
            }
        }
        return false;
    }

    void quickSort(int left, int right) { // быстрая сортировка
        if (left >= right) { // подмассив не требует сортировки
            return;
        }
        int mid = arr[left + (right - left) / 2]; // опорный элемент (середина)
        int i = left, j = right; // индексы
        while (i <= j) {
            while (arr[i] < mid) {
                i++; // двигаемся вправо до середины
            }
            while (arr[j] > mid) {
                j--; // двигаемся влево до середины
            }
            if (i <= j) {
                swap(arr[i], arr[j]); // меняем местами элементы
                i++;
                j--;
            }
        }
        if (left < j) {
            quickSort(left, j); // сортируем левую часть подмассива
        }
        if (i < right) {
            quickSort(i, right); // сортируем правую часть подмассива
        }
    }

    void printArray() { // вывод элементов массива
        if (size == 0) { // проверка на пустоту
            cout << "Массив пуст.\n";
            return;
        }
        for (size_t i = 0; i < size; i++) { // проходимся по элементам массива
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void loadFromFile(const string& file) { // загрузка данных из файла
        size = 0; // очищаем массив
        ifstream load(file);
        if (!load.is_open()) { // проверка
            cout << "Не удалось открыть файл.\n";
            return;
        }
        int str; // текущая строка данных
        while (load >> str) {
            addToEnd(str); // добавляем в конец массива
        }
        load.close();
    }

    void saveToFile(const string& file) { // загрузка данных в файл
        ofstream save(file);
        if (!save.is_open()) { // проверка
            cout << "Не удалось открыть файл.\n";
            return;
        }
        for (size_t i = 0; i < size; ++i) { // запись в файл
            save << arr[i] << endl;
        }
        save.close();
    }
};
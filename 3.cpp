#include "set.hpp"

int findInd(set& S, int item) { // поиск элемента по значению
    for (size_t i = 0; i < S.size; i++) { // проходимся по массиву
        if (S.arr[i] == item) {
            return i;
        }
    }
    return -1;
}

void subArrays(set& S, int target) { // поиск подмассивов
    set subS; // множество для подмассива
    int amountSub = 1 << S.size; // количество возможных комбинаций
    for (size_t i = 0; i < amountSub; i++) {
        int currentSum = 0; // текущая сумма
        subS.size = 0; // сбрасываем размер подмассива для каждой комбинации
        for (size_t j = 0; j < S.size; ++j) {
            if (i & (1 << j)) {
                currentSum += S.arr[j]; 
                subS.addToEnd(S.arr[j]);
            }
        }
        if (currentSum == target) { // если сумма равна искомой
            subS.printArray();
            for (size_t s = 0; s < subS.size; s++) {
                int index = findInd(S, subS.arr[s]);
                if (index != -1) {
                    S.delByIndex(index); // удаляем элементы из исходного массива
                }
            }
        }
    }
}

int main () {
    set S;
    S.addToEnd(4);
    S.addToEnd(10);
    S.addToEnd(5);
    S.addToEnd(1);
    S.addToEnd(3);
    S.addToEnd(7);
    S.printArray();
    int target = 5;
    cout << "Сумма: " << target << endl;
    subArrays(S, target);
    if (S.size != 0) {
        cout << "Множество не может быть поделено.\n";
    }
}
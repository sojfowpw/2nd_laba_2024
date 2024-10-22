#include <bitset>
#include "array.hpp"

void subarrays(Array& symbols) { // поиск подмассивов
	int amountSub = 1 << symbols.size; // подсчет общего количества подмассивов (2^size)
	for (size_t i = 0; i < amountSub; i++) { // проходимся по всем значениям
		cout << "{";
		for (size_t j = 0; j < symbols.size; ++j) {
			if (i & (1 << j)) { // проверка: установлен ли j бит в числе i
				cout << symbols.arr[j] << " ";
			}
		}
		cout << "}" << endl;
	}
}

/* i = 0: 000 {}
* i = 1: 001 {x}
* i = 2: 010 {y}
* i = 3: 100 {z}*/

int main() {
	Array symbols; // массив с символами
	symbols.addToEnd("x");
	symbols.addToEnd("y");
	symbols.addToEnd("z");
	subarrays(symbols);
	return 0;
}
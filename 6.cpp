#include <iostream>
#include <cstring> // для memset

using namespace std;

struct BitArray { // битовый массив
    unsigned char* arr; // указатель на массив байтов
    size_t size; // текущий размер (в битах)
    size_t capacity; // максимальный размер (в битах)

    BitArray(size_t cap = 15) : size(0), capacity(cap) { // вычисляем количество байтов, необходимых для хранения capacity в битах
        size_t numBytes = (cap + 7) / 8; // округляем вверх до ближайшего байта
        arr = new unsigned char[numBytes];
        memset(arr, 0, numBytes); // заполнение первых numBytes байтов массива нулями
    }

    ~BitArray() {
        delete[] arr; // освобождение памяти
    }

    void setBit(size_t index) { // установка бита в массиве по индексу
        if (index >= capacity) {
            cerr << "Недопустимый индекс.\n";
            return;
        }
        size_t byteIndex = index / 8; // индекс байта, в котором хранится нужный бит
        size_t bitIndex = index % 8; // индекс внутри байта
        arr[byteIndex] |= (1 << bitIndex); // побитовое или с присваиванием, сдвиг на bitIndex позиций влево
    }

    bool testBit(size_t index) const { // установлен ли бит в массиве по индексу
        if (index >= capacity) {
            cerr << "Недопустимый индекс.\n";
            return false;
        }
        size_t byteIndex = index / 8;
        size_t bitIndex = index % 8;
        return (arr[byteIndex] & (1 << bitIndex)) != 0;
    }
};

struct BloomFilter {
    size_t m_size; // размер 
    size_t m_numHashes; // количество хэш-функций
    BitArray m_bits; // битовый массив

    BloomFilter(size_t size, size_t numHashes) : m_size(size), m_numHashes(numHashes), m_bits(size) {}

    void add(const string& item) { // добавление элемента
        for (size_t i = 0; i < m_numHashes; ++i) {
            size_t hash = hashFunction(item, i) % m_size; // хэширование
            m_bits.setBit(hash);
        }
    }

    bool contains(const string& item) { // проверка: есть ли такой элемент
        for (size_t i = 0; i < m_numHashes; ++i) {
            size_t hash = hashFunction(item, i) % m_size; // хэширование
            if (!m_bits.testBit(hash)) {
                return false;
            }
        }
        return true;
    }

    size_t hashFunction(const string& item, size_t seed) { // прогон по трём хэш функциям
        switch (seed % 3) {
            case 0:
                return hashFunction1(item);
            case 1:
                return hashFunction2(item);
            case 2:
                return hashFunction3(item);
            default:
                return 0;
        }
    }

    size_t hashFunction1(const string& item) {
        size_t hash = 0;
        for (char c : item) {
            hash = (hash * 31) + c;
        }
        return hash;
    }

    size_t hashFunction2(const string& item) {
        size_t hash = 0;
        for (char c : item) {
            hash = (hash << 5) + (hash >> 27) + c;
        }
        return hash;
    }

    size_t hashFunction3(const string& item) {
        size_t hash = 0;
        for (char c : item) {
            hash = (hash * 17) + c;
        }
        return hash;
    }
};

int main() {
    BloomFilter bloomFilter(100, 3);

    bloomFilter.add("car");
    bloomFilter.add("apple");
    bloomFilter.add("shop");
    cout << boolalpha;
    cout << "car: " << bloomFilter.contains("car") << endl;
    cout << "apple: " << bloomFilter.contains("apple") << endl;
    cout << "shop: " << bloomFilter.contains("shop") << endl;
    cout << "pen " << bloomFilter.contains("pen") << endl;

    return 0;
}
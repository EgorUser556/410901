#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

const int TABLE_SIZE = 2000;
string* hashTable[TABLE_SIZE] = { nullptr }; // массив указателей на строк

int customHash(const string& key) {
    long long total = 0;

    for (int i = 0; i < key.length(); ++i) {
        int code = key[i]; 
        int modifier = code / (3 * (i + 1)); // порядковый номер начинается с 1
        total += code * modifier;
    }

    // Возводим сумму в квадрат
    long long squared = total * total;

    // Преобразуем в строку, чтобы вырезать цифры
    string squaredStr = to_string(squared);

    // Удаляем первые и последние два символа, если это возможно
    string middle;
    if (squaredStr.length() > 4) {
        middle = squaredStr.substr(2, squaredStr.length() - 4);
    }
    else {
        middle = squaredStr;
    }

    // Преобразуем обратно в число
    int middleNumber = stoi(middle);

    // Приводим к диапазону от 0 до 1999
    int address = middleNumber % 2000;

    while (address > 1999) {
        address %= 2000;
    }

    return address;
}

void find_elem() {
    system("cls");
    string key;
    cout << "Введите строку для поиска: ";
    cin.ignore();
    getline(cin, key);

    int hashValue = customHash(key);

    if (hashTable[hashValue] != nullptr && *hashTable[hashValue] == key) {
        cout << "Строка найдена по адресу " << hashValue << ": " << *hashTable[hashValue] << endl;
    }
    else {
        cout << "Строка не найдена в таблице.\n";
    }

    system("pause");
    system("cls");
}


void delete_elem() {
    system("cls");
    string key;
    cout << "Введите строку для удаления: ";
    cin.ignore();
    getline(cin, key);

    int hashValue = customHash(key);

    if (hashTable[hashValue] != nullptr && *hashTable[hashValue] == key) {
        delete hashTable[hashValue];
        hashTable[hashValue] = nullptr;
        cout << "Строка удалена из таблицы.\n";
    }
    else {
        cout << "Такой строки нет в таблице.\n";
    }

    system("pause");
    system("cls");
}


void display_hash() {
    system("cls");
    cout << "Содержимое хэш-таблицы:\n";
    bool empty = true;

    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (hashTable[i] != nullptr) {
            cout << i << ": " << *hashTable[i] << endl;
            empty = false;
        }
    }

    if (empty) {
        cout << "Хэш-таблица пуста.\n\n\n";
    }
    system("pause");
    system("cls");
}


void add_elem() {
    system("cls");
    string key;
    cout << "\nВведите строку для хэширования (или пустую строку для выхода): ";
    cin.ignore();
    getline(cin, key);
    while(key.empty()){
        cout << "Некорректный запрос\n";
        cin.ignore();
        getline(cin, key);
    }

    int hashValue = customHash(key);

    if (hashTable[hashValue] != nullptr) {
        cout << "Коллизия! Ячейка " << hashValue << " уже содержит: \"" << *hashTable[hashValue] << "\"\n";
    }
    else {
        hashTable[hashValue] = new string(key);
        cout << "Строка сохранена по адресу " << hashValue << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choise;
    SetConsoleCP(1251);
    system("cls");
    while (true) {
        cout << "1 - Добавить элемент в хэш-таблицу\n"
             << "2 - Просмотреть хэш-таблицу\n"
             << "3 - Искать элемент в хэш-таблице\n"
             << "4 - Удалить элемент из хэш-таблицы\n"
             << "5 - Выход\n";
        cin >> choise;

        while (choise < 1 && choise > 5) {
            cout << "\nНекорректный запрос\n";
            cin >> choise;
        }
    
        switch (choise) {
        case 1:
            add_elem();
            break;
        case 2:
            display_hash();
            break;
        case 3:
            find_elem();
            break;
        case 4:
            delete_elem();
            break;
        case 5:
            return 0;
            break;
        }
    }
    return 0;
}

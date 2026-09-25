#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h> 
#pragma execution_character_set("utf-8")
using namespace std;

// это у нас "Угадай число"
void secretNomer() {
    srand(time(0));
    int secret = rand() % 101; // число от 0 до 100
    int ugadai;

    cout << "ИГРА УГАДАЙ ЧИСЛО \nЯ загадала число от 0 до 100. Давай отгадвать." << endl;

    do {
        cout << "Твой вариант: ";
        cin >> ugadai;

        if (ugadai > secret) cout << "Точно меньше:)" << endl;
        else if (ugadai < secret) cout << "Побольшше." << endl;
        else cout << "В точку. Твоя победа." << secret << endl;
    } while (ugadai != secret);
}
void multTable() {     // таблица умножения.
    int table[10][10];

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {                // тут заполняем массив     
            table[i][j] = (i + 1) * (j + 1);
        }
    }

    // Выводим таблицу
    cout << "\n *ТАБЛИЦА УМНОЖЕНИЯ*" << endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << table[i][j] << "\t";
        }
        cout << endl;
    }
}
void deliteli() {            // Вывод делителей числа
    int n;
    cout << "\n *ДЕЛИТЕЛИ ЧИСЛА*" << endl;
    cout << "Введите число: ";
    cin >> n;

    cout << "Делители числа " << n << ": ";
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    SetConsoleCP(65001); // устанавливаем кодировку входящего потока данных на UTF-8 
    SetConsoleOutputCP(65001); // устанавливаем кодировку исходящего потока данных на UTF-8
    cout << "*МЕНЮ*\n1 - Угадай число (игра)\n2 - Таблица умножения\n3 - Делители числа\n4 - Выходим" << endl;
    int choice = 0;

    while (choice != 4) {
        cout << "Выберите программу: ";
        cin >> choice;

        if (choice == 1) secretNomer();
        else if (choice == 2) multTable();
        else if (choice == 3) deliteli();
        else if (choice == 4) cout << "Гудбай" << endl;
        else cout << "Але такого нету" << endl;
    }

    return 0;
}
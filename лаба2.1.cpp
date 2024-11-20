// лаба2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string> 
#include <limits>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    string filename; // Имя файла
    char userinput;
    int i;
    int wr = 0;
    int loss = 0;
    string input;
    int namberfile=0;
    word w; // Создаем экземпляр класса
    gameresult gr;
    answers answer;
    cout << "Выберите категорию слов:" << endl;
    cout << "1 - животные" << endl;
    cout << "2 - страны" << endl;
    cout << "3 - общая тема" << endl;
    cout << "4 - растения" << endl;
    while (namberfile < 1 || namberfile > 4) {
        cin >> input;
        try {
            namberfile = stoi(input);
            if (namberfile >= 1 && namberfile <= 4) {
            }
            else {
                cout << "Число должно быть от 1 до 4." << endl;
            }
        }
        catch (const invalid_argument& e) {
            cout << "Неверный ввод. Пожалуйста, введите целое число." << endl;
        }
        catch (const out_of_range& e) {
            cout << "Введенное число находится вне допустимого диапазона." << endl;
        }
        // Очистка потока cin от ошибок
        cin.clear();
    }

    if (namberfile == 1) filename = "animals.txt";
    else if (namberfile == 2) filename = "countries.txt";
    else if (namberfile == 3) filename = "words.txt";
    else if (namberfile == 4) filename = "plants.txt";
    try {
        checkFileExists(filename);
    }
    catch (const FileException& e) {
        std::cerr << "Ошибка: " << e.what() << "  Файл: " << e.getFilename() << std::endl;
    }

    initializeGame(gr, filename);
    const string& word = gr.getCurrentWord();
    int length = word.length();

    // Массив для использованных букв и массив для открытых букв
    string usedletters = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    string anspeople(length, '_'); // Заполняем символами '_'

    while (gr.getRightAnswers() < length && gr.getWrongAnswers() < 6)
    {
        int count = 0;
        cout << "Слово из " << length << " букв, введите букву - ";
        cin >> userinput;
        gr.setAnswer(userinput);
        // Проверка введенной буквы
        gr.check(userinput, length, usedletters, anspeople);
        for (i = 0; i < length; i++)
        {
            if (anspeople[i] != '_')
            {
                count += 1;
            }
        }
        if (count == length)//при выигрыше, когда в слове не останется не отгаданных букв
        {
            gr.getWinResult(&wr);
            cout << "Вы отгадали слово - " << word << " за " << wr << " попыток." << endl;
            gr.displayLetters();
            gr.kolwin();
            break;
        }
        if (gr.getWrongAnswers() == 6)//при проигыше, когда закончатся 6 попыток
        {
            gr.getLoss(&loss);
            cout << "Вы проиграли! Слово - " << word << endl;
            gr.displayLetters();
            gr.kolloss();
            break;
        }
    }
    gr.displayStats();
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

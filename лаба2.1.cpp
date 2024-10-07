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
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    const std::string filename = "words.txt"; // Имя файла
    char userInput;
    int i;
    int wr = 0;
    char* ansPeople(nullptr);
    word w; // Создаем экземпляр класса
    gameresult gr;
    answers answer;

    w.selectRandomWord(filename); // Выбираем случайное слово
    const char* word = w.getRandomWord(); // Получаем слово
    int length = w.getLength(); // Получаем длину слова
    answer.setCurrentWord(word); // Передача случайного слова

    // Массив для использованных букв и массив для открытых букв
    char usedLetters[67] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    ansPeople = new char[length + 1]; // +1 для '\0'
    std::fill(ansPeople, ansPeople + length, '_'); // Заполняем символами '_'
    ansPeople[length] = '\0'; // Завершаем строку нулем

    while (answer.getRightAnswers() < length && answer.getWrongAnswers() < 6)
    {
        int count = 0;
        std::cout << "Слово из " << length << " букв, введите букву - ";
        std::cin >> userInput;
        answer.setAnswer(userInput); // Установка буквы пользователя
        // Проверка введенной буквы
        answer.check(length, usedLetters, ansPeople);
        for (i = 0; i < length; i++)
        {
            if (ansPeople[i] != '_')
            {
                count += 1;
            }
        }
        if (count == length)//при выигрыше, когда в слове не останется не отгаданных букв
        {
            wr = gr.getWinResult();
            std::cout << "Вы отгадали слово - " << word << " за " << wr << " попыток." << std::endl;
            answer.displayLetters();
            gr.kolwin();
            break;
        }
        if (answer.getWrongAnswers() == 6)//при проигыше, когда закончатся 6 попыток
        {
            std::cout << "Вы проиграли! Слово - " << word << std::endl;
            answer.displayLetters();
            gr.kolloss();
            break;
        }
    }
    delete[] ansPeople;
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

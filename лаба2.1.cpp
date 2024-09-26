// лаба2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <stdlib.h>
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    struct word word1;
    struct pictures pic;
    struct answers ans;
    struct result res;
    struct letters let;
    struct attempts att;
    FILE* file;
    int i;
    int winans = 0;
    char* anspeople = (char*)malloc((word1.number + 1) * sizeof(char)); // +1 для символа '\0'
    if (!anspeople) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    file = fopen("words.txt", "r");
    if (file == NULL) { printf("Ошибка"); return 1; }
    randomword(file, word1.word, &word1.number);
    memset(anspeople, '_', sizeof(anspeople)); // Заполняем anspeople символами '_'
    anspeople[word1.number] = '\0';
    while (ans.rightanswer < word1.number && ans.wronganswer < 6)
    {
        int count = 0;
        printf("Слово из %d букв, ввведите букву - ", word1.number);
        scanf(" %c", &ans.answer);
        check(ans.answer, word1.word, &ans.wronganswer, &ans.rightanswer, let.alphabet, anspeople, &att.tries);
        for (i = 0; i < strlen(anspeople); i++)
        {
            if (anspeople[i] != '_')
            {
                count += 1;
            }
        }
        if (count == word1.number)
        {
            winans = ans.rightanswer + ans.wronganswer;
            printf("Вы отгадали слово - %s за %d попыток\n", word1.word, winans);
            endwin(&res.win, &res.winresult, winans);
            break;
        }
        if (ans.wronganswer == 6)
        {
            printf("Вы проиграли! Слово - %s\n", word1.word);
            lossend(&res.loss);
            break;
        }
    }
    fclose(file);
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

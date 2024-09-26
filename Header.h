//файл заголовков
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <stdlib.h>
//структура для слова от компьютера
struct word
{
    char word[50];
    int number = 0;
};
//структура для рисунка
struct pictures
{
    int numpicture;
};
//структура для ответа от пользователя
struct answers
{
    char answer;
    int wronganswer = 0;
    int rightanswer = 0;
};
//структура для результата игры
struct result
{
    int win;
    int loss;
    int winresult;
};
//структура для алфавита, проверки
struct letters
{
    char alphabet[67] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
};
//структура для счетчика результата
struct attempts
{
    int tries;
};
//функция для проверки буквы от пользователя в загаданном слове
void check(char ans, char word[50], int* wa, int* ra, char* al, char* alf, char* anspeople, int* tries)
{
    int i;
    int kol = 0;
    int kol1 = 0;
    for (i = 0; i < strlen(word); i++)
    {
        if (ans == word[i])
        {
            kol += 1;
            anspeople[i] = ans;
        }
    }
    for (i = 0; i < strlen(al); i++)
    {
        if (ans == al[i])
        {
            kol1 += 1;
            al[i] = '.';
        }
    }
    if (kol > 0 && kol1 > 0)
    {
        *ra += 1;
        printf("Вы угадали букву - %s\n", anspeople);
    }
    else
    {
        *wa += 1;
        printf("вы не угадали букву или уже использовали ее - %s\n", anspeople);
        *tries = 6 - *wa;
        printf("У вас осталось %d попыток.\n", *tries);
    }
}
//функция для рандомного выбора слова из файла
void randomword(FILE* file, char word[50], int* number)
{
    char word1[50][50];
    int c = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, " \n"); // Разделяем по пробелу и новой строке
        while (token != NULL) {
            if (c < 50) { // Проверяем, чтобы не выйти за пределы массива
                strcpy(word1[c], token);
                c++;
            }
            token = strtok(NULL, " \n");
        }
    }
    if (c > 0)
    {
        srand(time(NULL));
        int randomindex = rand() % c;
        strcpy(word, word1[randomindex]);
        *number = strlen(word);
    }
}
//функция для записи результата в случае выигрыша
void endwin(int* win, int* winres, int count)
{
    *win += 1;
    *winres = count;
}
//функция для счетчика проигрышей
void lossend(int* loss)
{
    *loss += 1;
}
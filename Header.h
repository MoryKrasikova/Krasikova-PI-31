//файл заголовков
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
//класс для слова от компьютера
class word {
private:
    char* randomWord; // Указатель для хранения случайного слова
    int length; // Длина слова

public:
    // Конструктор
    word() : randomWord(nullptr), length(0) {}

    // Деструктор для освобождения памяти
    ~word() {
        delete[] randomWord;
    }

    // Метод для выбора случайного слова
    void selectRandomWord(const std::string& filename) {
        std::ifstream file(filename); // Открываем файл
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла" << std::endl;
            return;
        }

        std::vector<std::string> words; // Вектор для хранения слов
        std::string word;

        // Читаем все слова из файла
        while (file >> word) {
            words.push_back(word); // Добавляем каждый считанный токен в вектор
        }

        if (!words.empty()) {
            srand(static_cast<unsigned int>(time(nullptr))); // Инициализация генератора случайных чисел
            int randomIndex = rand() % words.size(); // Генерация случайного индекса

            length = words[randomIndex].length(); // Узнаем длину случайного слова
            randomWord = new char[length + 1]; // Выделяем память для массива (длина + 1 для '\0')

            strncpy(randomWord, words[randomIndex].c_str(), length); // Копируем слово в массив символов
            randomWord[length] = '\0'; // Обеспечиваем завершение строки нулем
        }
    }

    // Метод для получения слова
    const char* getRandomWord() const {
        return randomWord;
    }

    // Метод для получения длины слова
    int getLength() const {
        return length;
    }
};
//класс для запонимания букв
class Letter {
private:
    char let;

public:
    // Конструктор
    Letter(char letter) : let(letter) {}

    // Метод для получения буквы
    char getValue() const {
        return let;
    }
};
//класс для ответа от пользователя
class answers
{
protected:
    int wronganswers;//кол-во неерных ответов
    int rightanswers;//кол-во верных
private:
    int tries; // Количество попыток
    const char* currentWord; // Текущее слово
    Letter** letters;
    int letterCount; // Количество введённых букв
    int capacity; // Вместимость массива
public:
    // Конструктор
    answers() : wronganswers(0), rightanswers(0), tries(6), currentWord(nullptr), letterCount(0), capacity(22) {
        letters = new Letter * [capacity]; // Выделяем память для массива указателей
    }

    // Деструктор для освобождения памяти
    ~answers() {
        for (int i = 0; i < letterCount; ++i) {
            delete letters[i]; // Освобождаем память для каждого объекта Letter
        }
        delete[] letters; // Освобождаем массив указателей
    }
    // Метод для установки слова
    void setCurrentWord(const char* word) {
        currentWord = word;
    }
    void setAnswer(char ans) {
        addLetter(ans); // Записываем букву в массив
    }
    void addLetter(char letter)
    {
        letters[letterCount++] = new Letter(letter); // Создаем новый объект и добавляем в массив
    }
    void check(char answer, int wordLength, char* usedLetters, char* ansPeople) {
        int kol = 0; // Количество совпадений
        int kol1 = 0; // Количество использованных букв

        for (int i = 0; i < wordLength; i++) {
            if (answer == currentWord[i]) { // Сравнение без учета регистра
                kol += 1;
                ansPeople[i] = currentWord[i]; // Открываем букву в ansPeople
            }
        }
        for (int i = 0; i < strlen(usedLetters); i++) {
            if (answer == usedLetters[i]) { // Сравнение без учета регистра
                kol1 += 1;
                usedLetters[i] = '.'; // Убираем использованную букву
            }
        }
        // Проверка на правильный или неверный ответ
        if (kol > 0 && kol1 > 0) { // Верный ответ
            rightanswers += 1;
            std::cout << "Вы угадали букву: " << ansPeople << std::endl;
        }
        else { // Неверный ответ
            wronganswers += 1;
            std::cout << "Вы не угадали букву или уже использовали её: " << ansPeople << std::endl;
            tries = 6 - wronganswers; // Обновление количества оставшихся попыток
            std::cout << "У вас осталось " << tries << " попыток." << std::endl;
        }
    }
    int getRightAnswers() {
        return rightanswers;
    }

    // Метод для получения количества неверных ответов
    int getWrongAnswers() {
        return wronganswers;
    }
    void displayLetters() const {
        std::cout << "Введенные буквы: ";
        for (int i = 0; i < letterCount; ++i) {
            std::cout << letters[i]->getValue() << " "; // Получаем значения букв
        }
        std::cout << std::endl;
    }
};
//класс для результата игры
class gameresult: public answers
{
private:
    int win;//кол-во выигрышей
    int loss;//кол-во проигрышей
    int winresult;//баллы при выигрыше
public:
    // Конструктор
    gameresult() : win(0), loss(0), winresult(0){

    }

    // Деструктор для освобождения памяти
    ~gameresult() {
    }
    void kolwin()
    {
       win += 1;
    }
    int getWin() const
    {
        return win;
    }

    void kolloss()
    {
        loss += 1;
    }
    int getLoss() const {
        return loss;
    }

    int getWinResult() {
        winresult = rightanswers + wronganswers;
        return winresult;
    }
};

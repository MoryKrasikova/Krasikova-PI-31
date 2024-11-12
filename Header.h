//файл заголовков
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;
//класс для слова от компьютера
class word {
private:
    string randomword; // Указатель для хранения случайного слова
    int length; // Длина слова

public:
    // Конструктор
    word() : length(0) {}

    // Деструктор для освобождения памяти
    ~word() {
    }

    // Метод для выбора случайного слова
    void selectRandomWord(const string& filename) {
        ifstream file(filename); // Открываем файл
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла" << endl;
            return;
        }

        vector<string> words; // Вектор для хранения слов
        string word;

        // Читаем все слова из файла
        while (file >> word) {
            words.push_back(word); // Добавляем каждый считанный токен в вектор
        }

        if (!words.empty()) {
            srand(static_cast<unsigned int>(time(nullptr))); // Инициализация генератора случайных чисел
            int randomindex = rand() % words.size(); // Генерация случайного индекса

            length = words[randomindex].length(); // Узнаем длину случайного слова

            randomword = words[randomindex];
        }
    }

    // Метод для получения слова
    const string& getRandomWord() const {
        return randomword;
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
    string currentword; // Текущее слово
    Letter** letters;
    int lettercount; // Количество введённых букв
    int capacity; // Вместимость массива

    friend void initializeGame(answers& game, const string& wordFilename);
public:
    // Конструктор
    answers() : wronganswers(0), rightanswers(0), tries(6), lettercount(0), capacity(22) {
        letters = new Letter * [capacity]; // Выделяем память для массива указателей
    }

    // Деструктор для освобождения памяти
    ~answers() {
        for (int i = 0; i < lettercount; ++i) {
            delete letters[i]; // Освобождаем память для каждого объекта Letter
        }
        delete[] letters; // Освобождаем массив указателей
    }
    // Метод для установки слова
private:
    void setCurrentWord(const string& word) {
        currentword = word;
    }

public:
    void setAnswer(char ans) {
        addLetter(ans); // Записываем букву в массив
    }
    const string& getCurrentWord() const { return currentword; }

    void addLetter(char letter)
    {
        letters[lettercount++] = new Letter(letter); // Создаем новый объект и добавляем в массив
    }
    void check(char answer, int wordlength, string& usedletters, string& anspeople) {
        int kol = 0; // Количество совпадений
        int kol1 = 0; // Количество использованных букв

        for (int i = 0; i < wordlength; i++) {
            if (answer == currentword[i]) { // Сравнение без учета регистра
                kol += 1;
                anspeople[i] = currentword[i]; // Открываем букву в ansPeople
            }
        }
        for (int i = 0; i < usedletters.length(); i++) {
            if (answer == usedletters[i]) { // Сравнение без учета регистра
                kol1 += 1;
                usedletters[i] = '.'; // Убираем использованную букву
            }
        }
        // Проверка на правильный или неверный ответ
        if (kol > 0 && kol1 > 0) { // Верный ответ
            rightanswers += 1;
            cout << "Вы угадали букву: " << anspeople << endl;
        }
        else { // Неверный ответ
            wronganswers += 1;
            cout << "Вы не угадали букву или уже использовали её: " << anspeople << endl;
            tries = 6 - wronganswers; // Обновление количества оставшихся попыток
            cout << "У вас осталось " << tries << " попыток." << endl;
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
        cout << "Введенные буквы: ";
        for (int i = 0; i < lettercount; ++i) {
            cout << letters[i]->getValue() << " "; // Получаем значения букв
        }
        cout << endl;
    }
   
};
//дружественная функция
void initializeGame(answers& game, const string& wordFilename) {
    word selectedword;
    selectedword.selectRandomWord(wordFilename);
    game.setCurrentWord(selectedword.getRandomWord()); // Доступ к private методу
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

    void getWinResult(int &winresult) {
        winresult = rightanswers + wronganswers;
    }
    //перегрузка 
    gameresult& operator=(const gameresult& other) {
        if (this != &other) { // Проверка самоприсваивания
            this->win = other.win;
            this->loss = other.loss;
            this->winresult = other.winresult;  //  В данном случае winresult -  не используется напрямую, но все равно его копируем
            this->rightanswers = other.rightanswers; // Копируем данные из базового класса answers
            this->wronganswers = other.wronganswers; // Копируем данные из базового класса answers
            // ... Копируем другие поля из answers, если они есть ...
        }
        return *this;
    }
};

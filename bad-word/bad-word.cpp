#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
const vector<string> WORDS = { "programming", "hangman", "computer", "developer", "language", "software" };

void displayWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.size(); i++) {
        if (guessed[i]) {
            cout << word[i] << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

char getUserGuess() {
    setlocale(LC_ALL, "Russian");
    char guess;
    cout << "Введите букву: ";
    cin >> guess;
    return tolower(guess);
}

bool updateGuessed(const string& word, vector<bool>& guessed, char guess) {
    bool found = false;
    for (size_t i = 0; i < word.size(); i++) {
        if (word[i] == guess) {
            guessed[i] = true;
            found = true;
        }
    }
    return found;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    string word = WORDS[rand() % WORDS.size()];
    vector<bool> guessed(word.size(), false);
    int attempts = 6;
    vector<char> wrongGuesses;

    cout << "Добро пожаловать в игру Виселица!" << endl;

    while (attempts > 0) {
        displayWord(word, guessed);
        cout << "Ошибки: ";
        for (char ch : wrongGuesses) {
            cout << ch << " ";
        }
        cout << endl;
        cout << "Осталось попыток: " << attempts << endl;

        char guess = getUserGuess();

        if (find(wrongGuesses.begin(), wrongGuesses.end(), guess) != wrongGuesses.end()) {
            cout << "Вы уже вводили эту букву! Попробуйте снова." << endl;
            continue;
        }

        if (!updateGuessed(word, guessed, guess)) {
            wrongGuesses.push_back(guess);
            attempts--;
        }

        if (all_of(guessed.begin(), guessed.end(), [](bool val) { return val; })) {
            cout << "Поздравляем! Вы угадали слово: " << word << endl;
            break;
        }
    }

    if (attempts == 0) {
        cout << "Вы проиграли! Загаданное слово было: " << word << endl;
    }

    return 0;
}

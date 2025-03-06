#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Hangman {
private:
    std::vector<std::string> words{ "programming", "computer", "developer", "hangman", "cplusplus" };
    std::string word;
    std::string guessedWord;
    int attempts;
    std::vector<char> wrongGuesses;

public:
    Hangman() {
        srand(time(0));
        word = words[rand() % words.size()];
        guessedWord = std::string(word.length(), '_');
        attempts = 6;
    }

    void display() {
        std::cout << "\nWord: " << guessedWord << "\n";
        std::cout << "Attempts left: " << attempts << "\n";
        std::cout << "Wrong guesses: ";
        for (char c : wrongGuesses) std::cout << c << ' ';
        std::cout << "\n";
    }

    void guess(char letter) {
        if (word.find(letter) != std::string::npos) {
            for (size_t i = 0; i < word.length(); ++i) {
                if (word[i] == letter) guessedWord[i] = letter;
            }
        }
        else {
            wrongGuesses.push_back(letter);
            --attempts;
        }
    }

    bool isWon() { return guessedWord == word; }
    bool isLost() { return attempts <= 0; }

    
    std::string getWord() { return word; }
};

int main() {
    Hangman game;
    char letter;

    while (!game.isWon() && !game.isLost()) {
        game.display();
        std::cout << "Enter a letter: ";
        std::cin >> letter;
        game.guess(letter);
    }

    game.display();
    if (game.isWon())
        std::cout << "Congratulations! You guessed the word!\n";
    else
        std::cout << "Game over! The word was: " << game.getWord() << "\n";

    return 0;
}

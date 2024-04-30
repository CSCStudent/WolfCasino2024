#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "S02849570.h"

//defined namespace for project
namespace CSC2034
{
    //Constructor
    S02849570::S02849570()
    = default;

    S02849570* S02849570::makeGame() {
        return new S02849570;
    }

    //The game!
    void S02849570::start() {
        string response;
        do {
            word = pickWord();
            triesLeft = 6;
            guess = '\0';
            guesses.clear();
            cout << word << endl;
            do {
                printHangedMan(6 - triesLeft);
                cout << "LIVES: " << triesLeft << endl;
                cout << "The word so far: " << getWordWithGuesses();
                cout << endl << endl;
                bool alreadyGuessed;
                do {
                    cout << "Enter a letter to guess: ";
                    cin >> guess;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    alreadyGuessed = std::find(guesses.begin(), guesses.end(),guess) != guesses.end();
                    if(alreadyGuessed) {
                        cout << endl << "You've already guessed that letter. Pick a different one!" << endl;
                        continue;
                    }
                    guesses.push_back(guess);
                } while(alreadyGuessed);
                guess = tolower(guess);
                if (isCharInWord(guess)) {
                    cout << endl << "Good guess! That letter is in the word." << endl;
                } else {
                    cout << endl << "Bad guess! That letter is not in the word :( -1 Life" << endl;
                    triesLeft--;
                }
            } while (getWordWithGuesses() != word && triesLeft > 0);
            if (triesLeft == 0) {
                printHangedMan(1001);
                cout << "Too bad! You lose. The word was: " << word << ". Play again? (Y/N): " << endl;
                cin >> response;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                printHangedMan(1002);
                cout << "You got the word! It was: " << word << ". Play again? (Y/N): " << endl;
                cin >> response;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            std::transform(response.begin(), response.end(), response.begin(),
                           [](unsigned char c) { return std::tolower(c); });
        } while(response == "y");
        if(response != "y") {
            cout << endl << "Thanks for playing!" << endl;
        }
    }

    string S02849570::pickWord() {

        ifstream file("./words_alpha.txt", ios::binary | ios::ate);
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            throw ios_base::failure("File not found");
        }

        file.seekg(0, ios::end);
        long long fileSize = file.tellg();
        file.seekg(0);

        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); // Seed using current time
        uniform_int_distribution<long long> dist(0, fileSize - 1); // Uniform distribution over file positions

        char ch;
        string line;
        do {
            long long randomPos = dist(rng);
            file.seekg(randomPos);
            file.get(ch);
            if (ch == '\n' || ch == '\r' || ch == '\t' || ch == '\0') {
                continue;
            }
            while (randomPos > 0 && ch != '\n' && ch != '\r') {
                randomPos--;
                file.seekg(randomPos);
                file.get(ch);
            }
            if (randomPos != 0) {
                file.seekg(randomPos + 1); // Move to the beginning of the line
            }
            getline(file, line);
            if (!line.empty() && line[line.length() - 1] == '\r') {
                line = line.substr(0, line.length() - 1);
            }
            file.close();
            return line;
        } while(true);
    }

    bool S02849570::isCharInWord(char c) {
        return word.find(c) != string::npos;
    }

    string S02849570::getWordWithGuesses() {
        string s;
        for(int i = 0; i < word.length(); i++) {
            if(std::find(guesses.begin(), guesses.end(), word.at(i)) != guesses.end()){
                s.push_back(word.at(i));
            } else {
                s.push_back('_');
            }
        }
        return s;
    }

    void S02849570::printHangedMan(int x){
        /* Thanks @vmoudy for the ascii art */
        switch(x){
            case 0: cout << "_________" << endl
                         << " |     | " << endl
                         << " | " << endl
                         << " | " << endl
                         << " | " << endl
                         << " | " << endl
                         << "``````````" << endl;
                break;
            case 1: cout << "_________" << endl
                         << " |     | " << endl
                         << " |   (   )" << endl
                         << " | " << endl
                         << " | " << endl
                         << " | " << endl
                         << "``````````" << endl;
                break;
            case 2: cout << "_________" << endl
                         << " |     | " << endl
                         << " |   (   )" << endl
                         << " |     | " << endl
                         << " |     |" << endl
                         << " | " << endl
                         << "``````````" << endl;
                break;
            case 3: cout << "_________" << endl
                         << " |     | " << endl
                         << " |   (   )" << endl
                         << " |    _| " << endl
                         << " |     |" << endl
                         << " | " << endl
                         << "``````````" << endl;
                break;
            case 4: cout << "_________" << endl
                         << " |     | " << endl
                         << " |   (   )" << endl
                         << " |    _|_ " << endl
                         << " |     |" << endl
                         << " |     " << endl
                         << "``````````" << endl;
                break;
            case 5: cout << "_________" << endl
                         << " |     | " << endl
                         << " |   (   )" << endl
                         << " |    _|_ " << endl
                         << " |     |" << endl
                         << " |    / " << endl
                         << "``````````" << endl;
                break;
            case 6: cout << "_________" << endl
                         << " |     | " << endl
                         << " |   (   )" << endl
                         << " |    \\|/ " << endl
                         << " |     |" << endl
                         << " |    / \\" << endl
                         << "``````````" << endl;
                break;
            case 1001: cout << "_________" << endl
                         << " |     | " << endl
                         << " |   (x_x)" << endl
                         << " |     | " << endl
                         << " |    /|\\" << endl
                         << " |    / \\" << endl
                         << " ````\\" << endl
                         << "      \\" << endl;
                break;
            case 1002: cout << endl
                         << "    (^_^)" << endl
                         << "     \\|/ " << endl
                         << "      |" << endl
                         << "     / \\" << endl;
                break;
        }
    }

} // end of namespace
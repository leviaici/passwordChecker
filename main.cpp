#include <iostream>
#include <vector>
#include "rlutil.h"

bool checkSymbols(const std::string& password) {
    std::vector<char> symbols = {'@', '_', ',', '!', '.', '-', ';', '+', '/', '?', '|', ']', '[', '=', '(', ')', '*', '&', '^', '%', '$', '#', '\\', '`', '~', '<', '>'};
    return std::any_of(symbols.begin(), symbols.end(),
                       [&password](const auto& s){ return password.find(s) != std::string::npos; });
}

bool checkNumbers(const std::string& password) {
    std::vector<char> numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    return std::any_of(numbers.begin(), numbers.end(),
                       [&password](const auto& s){ return password.find(s) != std::string::npos; });
}

bool checkUppercaseLetters(const std::string& password) {
    std::vector<char> uppercaseLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    return std::any_of(uppercaseLetters.begin(), uppercaseLetters.end(),
                       [&password](const auto& s){ return password.find(s) != std::string::npos; });
}

bool checkLowercaseLetters(const std::string& password) {
    std::vector<char> uppercaseLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    return std::any_of(uppercaseLetters.begin(), uppercaseLetters.end(),
                       [&password](const auto& s){ return password.find(s + 32) != std::string::npos; });
}

float checkPasswordComplexity(const std::string& password) {
    float complexity = 5;

    bool symbolsFound = checkSymbols(password);

    bool numbersFound = checkNumbers(password);

    bool uppercaseLettersFound = checkUppercaseLetters(password);
    bool lowercaseLettersFound = checkLowercaseLetters(password);

    if(symbolsFound)
        complexity += 1.25;
    else complexity -= 1.25;

    if(numbersFound)
        complexity += 1.25;
    else complexity -= 1.25;

    if(uppercaseLettersFound)
        complexity += 1.25;
    else complexity -= 1.25;

    if(lowercaseLettersFound)
        complexity += 1.25;
    else complexity -= 1.25;

    return complexity;
}

std::string getPassword(const bool& mode) { // true - password, false - verify password
    int counter = 0;
    int x, y;
    std::string password;

    while (true) {
        rlutil::cls();
        float complexity = checkPasswordComplexity(password);

        if(mode) {
            std::cout << "Complexity of password: " << complexity << "\n";
            x = 11;
            y = 2;
            rlutil::locate(1, 2);
            std::cout << "Password: ";
        } else {
            std::cout << "Complexity of password: " << complexity << "\n";
            x = 18;
            y = 2;
            rlutil::locate(1, 2);
            std::cout << "Verify password: ";
        }
        rlutil::locate(x, y);
        for(int i = 0; i < counter; i++) {
            std::cout << "*";
            ++x;
        }
        rlutil::locate(x, y);
        unsigned char ch = getch();
        if (ch == 127 || ch == 8) {
            if(password.length() > 0) {
                --x;
                --counter;
                rlutil::locate(x,y);
                std::cout << " ";
                password.erase(password.length() - 1);
            }
        }
        else if (ch == '\n') break;
        else {
            counter++;
            std::cout << '*';
            password += ch;
            ++x;
        }
    }
    return password;
}

int main() {
    std::string password = getPassword(true);
    std::cout << "\nread: " << password << "\n";
    return 0;
}

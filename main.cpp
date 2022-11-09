#include <iostream>
#include <vector>
#include "rlutil.h"
#include <thread>

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
    float complexity = 50;

    bool symbolsFound = checkSymbols(password);

    bool numbersFound = checkNumbers(password);

    bool uppercaseLettersFound = checkUppercaseLetters(password);
    bool lowercaseLettersFound = checkLowercaseLetters(password);

    if(symbolsFound)
        complexity += 12.5;
    else complexity -= 12.5;

    if(numbersFound)
        complexity += 12.5;
    else complexity -= 12.5;

    if(uppercaseLettersFound)
        complexity += 12.5;
    else complexity -= 12.5;

    if(lowercaseLettersFound)
        complexity += 12.5;
    else complexity -= 12.5;

    return complexity;
}

void initialPrintForPassword(const int& complexity, const std::string& password) {
    rlutil::setColor(7);
    std::cout << "Minimum number of characters of the password: 10";
    if(password.size() >= 10) {
        rlutil::setColor(10);
        std::cout << " ✔\n";
    } else std::cout << "\n";
    rlutil::setColor(7);
    std::cout << "Minimum complexity of password: ";
    rlutil::setColor(14);
    std::cout << "[■■■■■■■■■■■■■■■■                ]";
    if(complexity >= 50) {
        rlutil::setColor(10);
        std::cout << " ✔\n";
    } else std::cout << "\n";
    rlutil::setColor(7);
    std::cout << "Complexity of your password:    ";
    rlutil::setColor(12);
    std::cout << "[                                ]";
}

void printComplexity(const int& complexity, const std::string& password) {
    initialPrintForPassword(complexity, password);

    rlutil::locate(33, 3);
    switch(complexity) {
        case 25:
            rlutil::setColor(13);
            std::cout << "[■■■■■■■■                        ]\n";
            rlutil::setColor(12);
            rlutil::locate(1, 5);
            std::cout << "Password too weak.\n";
            break;
        case 50:
            rlutil::setColor(14);
            std::cout << "[■■■■■■■■■■■■■■■■                ]\n";
            rlutil::locate(1, 5);
            std::cout << "Unsafe password.\n";
            break;
        case 75:
            rlutil::setColor(10);
            std::cout << "[■■■■■■■■■■■■■■■■■■■■■■■■        ]\n";
            rlutil::locate(1, 5);
            std::cout << "Decent password.\n";
            break;
        case 100:
            rlutil::setColor(11);
            std::cout << "[■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■]\n";
            rlutil::locate(1, 5);
            std::cout << "Great password.\n";
            break;
        default:
            break;
    }

    rlutil::setColor(7);
}

std::string getPassword(const bool& mode) { // true - password, false - verify password
    int counter = 0;
    int x, y;
    std::string password;

    while (true) {
        rlutil::cls();
        float complexity = checkPasswordComplexity(password);

        if(mode) {
            printComplexity(int(complexity), password);
            x = 11;
            y = 4;
            rlutil::locate(1, 4);
            std::cout << "Password: ";
        } else {
            std::cout << "Complexity of password: " << complexity << "\n";
            x = 18;
            y = 4;
            rlutil::locate(1, 4);
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
        else if (ch == '\n') {
            if(complexity >= 50 && password.size() >= 10)
                break;
            else continue;
        }
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

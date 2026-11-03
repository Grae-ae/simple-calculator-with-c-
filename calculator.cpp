#include <iostream>
#include <string>
#include <limits>
#include <cmath>

int main() {
    std::cout << "Simple Calculator\n"
                 "Enter: <number> <operator> <number>   (e.g. 3.5 * 2)\n"
                 "Operators: + - * / % ^   |  Type 'q' to quit\n\n";

    while (true) {
        std::cout << "> ";
        std::string token;
        if (!(std::cin >> token)) break;          // EOF
        if (token == "q" || token == "quit") break;

        // Parse the first number
        double a;
        try {
            size_t pos;
            a = std::stod(token, &pos);
            if (pos != token.size()) throw std::invalid_argument("");
        } catch (...) {
            std::cout << "Invalid number: " << token << "\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        char op;
        double b;
        if (!(std::cin >> op >> b)) {
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        double result;
        switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) { std::cout << "Error: division by zero\n"; continue; }
                result = a / b; break;
            case '%':
                if (b == 0) { std::cout << "Error: modulo by zero\n"; continue; }
                result = std::fmod(a, b); break;
            case '^': result = std::pow(a, b); break;
            default:
                std::cout << "Unknown operator: " << op << "\n";
                continue;
        }
        std::cout << "= " << result << "\n";
    }
    std::cout << "Bye.\n";
    return 0;
}
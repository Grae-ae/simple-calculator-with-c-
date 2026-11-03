#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Parser {
    const std::string& src;
    size_t pos = 0;

public:
    explicit Parser(const std::string& s) : src(s) {}

    double parse() {
        double v = expression();
        skipWs();
        if (pos != src.size())
            throw std::runtime_error("Unexpected character at position " + std::to_string(pos));
        return v;
    }

private:
    void skipWs() {
        while (pos < src.size() && std::isspace((unsigned char)src[pos])) ++pos;
    }

    double expression() {                 // expression := term (('+'|'-') term)*
        double v = term();
        while (true) {
            skipWs();
            if (pos < src.size() && (src[pos] == '+' || src[pos] == '-')) {
                char op = src[pos++];
                double rhs = term();
                v = (op == '+') ? v + rhs : v - rhs;
            } else break;
        }
        return v;
    }

    double term() {                       // term := factor (('*'|'/') factor)*
        double v = factor();
        while (true) {
            skipWs();
            if (pos < src.size() && (src[pos] == '*' || src[pos] == '/')) {
                char op = src[pos++];
                double rhs = factor();
                if (op == '/' && rhs == 0.0)
                    throw std::runtime_error("Division by zero");
                v = (op == '*') ? v * rhs : v / rhs;
            } else break;
        }
        return v;
    }

    double factor() {                     // factor := ('-'|'+') factor | '(' expression ')' | number
        skipWs();
        if (pos >= src.size()) throw std::runtime_error("Unexpected end of input");

        if (src[pos] == '+' ) { ++pos; return  factor(); }
        if (src[pos] == '-') { ++pos; return -factor(); }

        if (src[pos] == '(') {
            ++pos;
            double v = expression();
            skipWs();
            if (pos >= src.size() || src[pos] != ')')
                throw std::runtime_error("Missing ')'");
            ++pos;
            return v;
        }

        size_t start = pos;
        while (pos < src.size() &&
               (std::isdigit((unsigned char)src[pos]) || src[pos] == '.'))
            ++pos;

        if (start == pos) throw std::runtime_error("Number expected");
        return std::stod(src.substr(start, pos - start));
    }
};

int main() {
    std::cout << "Expression Calculator (type 'q' to quit)\n"
                 "Example: 2 + 3 * (4 - 1) / 2\n\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "q" || line == "quit") break;
        if (line.empty()) continue;

        try {
            Parser p(line);
            std::cout << "= " << p.parse() << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}
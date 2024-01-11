#include <iostream>
#include <string>

using namespace std;

// Clase Token para representar cada simbolo en la entrada
class Token {
public:
    Token(char type, int value = 0) : type_(type), value_(value) {}

    char getType() const {
        return type_;
    }

    int getValue() const {
        return value_;
    }

private:
    char type_; // El tipo de simbolo (operador, parentesis, numero, etc.)
    int value_; // El valor del numero, si el tipo es numero
};

// Clase Lexer para convertir la cadena de entrada en una secuencia de tokens
class Lexer {
public:
    Lexer(string input) : input_(input), position_(0) {}

    // Obtener el siguiente token en la secuencia
    Token getNextToken() {
        char currentChar = getCurrentChar();

        // Si el caracter actual es un numero, leer el numero completo
        if (isdigit(currentChar)) {
            int value = currentChar - '0';
            advancePosition();
            while (isdigit(getCurrentChar())) {
                value = value * 10 + (getCurrentChar() - '0');
                advancePosition();
            }
            return Token('n', value);
        }
        // Si el caracter actual es un operador o parentesis, devolver el token correspondiente
        else if (currentChar == '+') {
            advancePosition();
            return Token('+');
        }
        else if (currentChar == '-') {
            advancePosition();
            return Token('-');
        }
        else if (currentChar == '*') {
            advancePosition();
            return Token('*');
        }
        else if (currentChar == '/') {
            advancePosition();
            return Token('/');
        }
        else if (currentChar == '(') {
            advancePosition();
            return Token('(');
        }
        else if (currentChar == ')') {
            advancePosition();
            return Token(')');
        }
        // Si no es ningun simbolo valido, lanzar una excepcion
        else {
            throw runtime_error("Error de sintaxis: simbolo invalido");
        }
    }

private:
    string input_; // La cadena de entrada
    int position_; // La posicion actual en la cadena de entrada

    // Obtener el caracter actual de la cadena de entrada
    char getCurrentChar() const {
        if (position_ >= input_.length()) {
            return '\0';
        }
        else {
            return input_[position_];
        }
    }

    // Avanzar la posicion actual en la cadena de entrada
    void advancePosition() {
        position_++;
    }
};

// Clase Parser para analizar la sintaxis de la secuencia de tokens
// class Parser {
// public:
//     Parser(Lexer& lexer) : lexer_(lexer), current
// }
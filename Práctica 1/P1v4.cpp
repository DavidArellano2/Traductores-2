#include <iostream>
#include <string>

using namespace std;

class Token
{
public:
    Token(char type, int val = 0) : tipo(type), valor(val) {}

    char getType()
    {
        return tipo;
    }

    int getVal()
    {
        return valor;
    }

private:
    char tipo;
    int valor;
};

class Lexer
{
public:
    Lexer(string input) : entrada(input), posicion(0) {}

    Token getNextToken()
    {
        char currentChar = getCurrentChar();

        if (isdigit(currentChar))
        {
            int value = currentChar - '0';
            avanza();
            while (isdigit(getCurrentChar()))
            {
                value = value * 10 + (getCurrentChar() - '0');
                avanza();
            }
            return Token('n', value);
        }
        // Si el caracter actual es un operador o parentesis, devolver el token correspondiente
        else if (currentChar == '+')
        {
            avanza();
            return Token('+');
        }
        else if (currentChar == '-')
        {
            avanza();
            return Token('-');
        }
        else if (currentChar == '*')
        {
            avanza();
            return Token('*');
        }
        else if (currentChar == '/')
        {
            avanza();
            return Token('/');
        }
        else if (currentChar == '(')
        {
            avanza();
            return Token('(');
        }
        else if (currentChar == ')')
        {
            avanza();
            return Token(')');
        }
        else
        {
            throw runtime_error("Error de sintaxis: simbolo invalido");
        }
    }

private:
    string entrada;
    int posicion;
    char getCurrentChar()
    {
        if (posicion >= entrada.length())
        {
            return 'x';
        }
        else
        {
            return entrada[posicion];
        }
    }
    void avanza()
    {
        posicion++;
    }
};

class Parser
{
public:
    Parser(Lexer &lexer)
        : lexer_(lexer), currentToken_(lexer.getNextToken())
    {
    }

    int expresion()
    {
        int result = termino();

        while (currentToken_.getType() == '+' || currentToken_.getType() == '-')
        {
            if (currentToken_.getType() == '+')
            {
                consume('+');
                result += termino();
            }
            else
            {
                consume('-');
                result -= termino();
            }
        }

        return result;
    }

    int termino()
    {
        int result = factor();

        while (currentToken_.getType() == '*' || currentToken_.getType() == '/')
        {
            if (currentToken_.getType() == '*')
            {
                consume('*');
                result *= factor();
            }
            else
            {
                consume('/');
                result /= factor();
            }
        }

        return result;
    }

    int factor()
    {
        if (currentToken_.getType() == '(')
        {
            consume('(');
            int result = expresion();
            consume(')');
            return result;
        }
        else if (currentToken_.getType() == 'n')
        {
            int result = currentToken_.getVal();
            consume('n');
            return result;
        }
        else
        {
            throw runtime_error("Factor invalido");
        }
    }

private:
    void consume(char tipo)
    {
        if (currentToken_.getType() == tipo)
        {
            currentToken_ = lexer_.getNextToken();
        }
        else
        {
            throw runtime_error("Token inesperado: " + currentToken_.getVal());
        }
    }
    Lexer lexer_;
    Token currentToken_;
};

int main()
{
    string input;
    cout << "Ingrese una expresion aritmetica: ";
    getline(cin, input);

    Lexer lexer(input);
    Parser parser(lexer);

    try
    {
        int resultado = parser.expresion();
        cout << "El resultado es: " << resultado << endl;
    }
    catch (const exception &ex)
    {
        cerr << "Error: " << ex.what() << endl;
    }
    return 0;
}
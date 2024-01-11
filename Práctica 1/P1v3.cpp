#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Token
{
public:
    enum Type
    {
        Invalid,
        EndOfFile,
        Plus,
        Minus,
        Asterisk,
        Slash,
        LeftParen,
        RightParen,
        Number
    };

    Token(Type type = Invalid, const string &value = "")
        : type_(type), value_(value)
    {
    }

    Type getType() const { return type_; }
    const string &getValue() const { return value_; }

private:
    Type type_;
    string value_;
};

class Lexer
{
public:
    Lexer(const string &input)
        : input_(input), position_(0)
    {
    }

    Token getNextToken()
    {
        while (position_ < input_.size())
        {
            const char currentChar = input_[position_];

            if (isdigit(currentChar))
            {
                return readNumber();
            }
            else if (isspace(currentChar))
            {
                advancePosition();
                continue;
            }
            else if (currentChar == '+')
            {
                advancePosition();
                return Token(Token::Plus, "+");
            }
            else if (currentChar == '-')
            {
                advancePosition();
                return Token(Token::Minus, "-");
            }
            else if (currentChar == '*')
            {
                advancePosition();
                return Token(Token::Asterisk, "*");
            }
            else if (currentChar == '/')
            {
                advancePosition();
                return Token(Token::Slash, "/");
            }
            else if (currentChar == '(')
            {
                advancePosition();
                return Token(Token::LeftParen, "(");
            }
            else if (currentChar == ')')
            {
                advancePosition();
                return Token(Token::RightParen, ")");
            }
            else
            {
                throw runtime_error("Caracter invalido en la entrada: " + string(1, currentChar));
            }
        }

        return Token(Token::EndOfFile, "");
    }

private:
    Token readNumber()
    {
        string value;

        while (position_ < input_.size() && isdigit(input_[position_]))
        {
            value += input_[position_];
            advancePosition();
        }

        return Token(Token::Number, value);
    }

    void advancePosition()
    {
        ++position_;
    }

    char getCurrentChar() const
    {
        if (position_ >= input_.size())
        {
            return '\0';
        }

        return input_[position_];
    }

    string input_;
    size_t position_;
};

class Parser
{
public:
    Parser(const Lexer &lexer)
        : lexer_(lexer), currentToken_(lexer.getNextToken(val))
    {
    }

    int expresion()
    {
        int result = termino();

        while (currentToken_.getType() == Token::Plus || currentToken_.getType() == Token::Minus)
        {
            if (currentToken_.getType() == Token::Plus)
            {
                consume(Token::Plus);
                result += termino();
            }
            else
            {
                consume(Token::Minus);
                result -= termino();
            }
        }

        return result;
    }

    int termino()
    {
        int result = factor();

        while (currentToken_.getType() == Token::Asterisk || currentToken_.getType() == Token::Slash)
        {
            if (currentToken_.getType() == Token::Asterisk)
            {
                consume(Token::Asterisk);
                result *= factor();
            }
            else
            {
                consume(Token::Slash);
                result /= factor();
            }
        }

        return result;
    }

    int factor()
    {
        if (currentToken_.getType() == Token::LeftParen)
        {
            consume(Token::LeftParen);
            int result = expresion();
            consume(Token::RightParen);
            return result;
        }
        else if (currentToken_.getType() == Token::Number)
        {
            int result = stoi(currentToken_.getValue());
            consume(Token::Number);
            return result;
        }
        else
        {
            throw runtime_error("Factor invalido");
        }
    }

private:
    void consume(Token::Type expectedType)
    {
        if (currentToken_.getType() == expectedType)
        {
            currentToken_ = lexer_.getNextToken();
        }
        else
        {
            throw runtime_error("Token inesperado: " + currentToken_.getValue());
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
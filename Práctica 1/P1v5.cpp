#include <iostream>
#include <string>

using namespace std;

string cadenaEntrada = "";
char analisis;
size_t index = 0;

void coincidir(char);

void expr();
void expr_();

void term();
void term_();

void factor();
void digito();

int main()
{
    index = 0;
    cout << "Escriba una expresion: ";
    cin >> cadenaEntrada;
    cadenaEntrada += "!";
    expr();
    if (cadenaEntrada[index] != '!')
    {
        cerr << "Hay un error en la cadena" << endl;
        exit(1);
    }
    
    cout << "Cadena valida" << endl;

    return 0;
}

void coincidir(char curr)
{
    if (analisis != curr)
    {
        cerr << "Hay un error en '" << curr << "'" << endl;
        exit(1);
    }
    index++;
}

void expr()
{
    term();
    expr_();
}

void expr_()
{
    while (true)
    {
        analisis = cadenaEntrada[index];
        switch (analisis)
        {
        case '+':
            coincidir('+');
            term();
            continue;

        case '-':
            coincidir('-');
            term();
            continue;
        default:
            return;
        }
    }
}

void term()
{
    factor();
    term_();
}

void term_()
{
    while (true)
    {
        analisis = cadenaEntrada[index];
        switch (analisis)
        {
        case '*':
            coincidir('*');
            factor();
            continue;

        case '/':
            coincidir('/');
            factor();
            continue;

        default:
            return;
        }
    }
}

void factor()
{
    analisis = cadenaEntrada[index];
    switch (analisis)
    {
    case '(':
        // cout << analisis << endl;
        coincidir('(');
        expr();
        coincidir(')');
        break;
    default:
        digito();
        break;
    }
}

void digito()
{
    analisis = cadenaEntrada[index];
    if (isdigit(analisis))
    {
        coincidir(analisis);
        return;
    }
    cerr << "Se introdujo un digito invalido" << endl;
    exit(1);
}
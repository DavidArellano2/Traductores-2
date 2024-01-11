#include <iostream>
#include <string>

using namespace std;

string cadenaEntrada = "";
string cadenaPF = "";
char analisis;
size_t indice = 0;

void coincidir(char);

void expr();
string expr_();

void term();
string term_();

string factor();
string digito();

int main()
{
    indice = 0;
    cout << "Escriba una expresion: ";
    cin >> cadenaEntrada;
    cadenaEntrada += "!";
    expr();
    if (cadenaEntrada[indice] != '!')
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
    indice++;
}

void expr()
{
    term();
    cadenaPF += expr_();
}

string expr_()
{
    while (true)
    {
        analisis = cadenaEntrada[indice];
        switch (analisis)
        {
        case '+':
            coincidir('+');
            term();
            return "+";

        case '-':
            coincidir('-');
            term();
            return "-";
        default:
            return;
        }
    }
}

void term()
{
    factor();
    cadenaPF += term_();
}

string term_()
{
    while (true)
    {
        analisis = cadenaEntrada[indice];
        switch (analisis)
        {
        case '*':
            coincidir('*');
            factor();
            return "*";

        case '/':
            coincidir('/');
            factor();
            return "/";

        default:
            return;
        }
    }
}

string factor()
{
    analisis = cadenaEntrada[indice];
    switch (analisis)
    {
    case '(':
        coincidir('(');
        expr();
        coincidir(')');
        break;
    default:
        cadenaPF += digito();
        break;
    }
}

string digito()
{
    analisis = cadenaEntrada[indice];
    if (isdigit(analisis))
    {
        coincidir(analisis);
        return analisis;
    }
    cerr << "Se introdujo un digito invalido" << endl;
    exit(1);
}
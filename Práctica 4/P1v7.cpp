#include <iostream>
#include <string>

using namespace std;

string cadenaEntrada = "";
string cadenaPF = "";
char analisis;
size_t indice = 0;

void coincidir(char);

void expr();
void expr_();

void term();
void term_();

void factor();
void digito();

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
    
    cout << "Cadena postfijo: " << cadenaPF << endl;

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
    expr_();
}

void expr_()
{
    char pf;
    while (true)
    {
        analisis = cadenaEntrada[indice];
        pf = analisis;
        switch (analisis)
        {
        case '+':
            coincidir('+');
            term();
            cadenaPF += pf;
            continue;

        case '-':
            coincidir('-');
            term();
            cadenaPF += pf;
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
    char pf;
    while (true)
    {
        analisis = cadenaEntrada[indice];
        pf = analisis;
        switch (analisis)
        {
        case '*':
            coincidir('*');
            factor();
            cadenaPF += pf;
            continue;

        case '/':
            coincidir('/');
            factor();
            cadenaPF += pf;
            continue;

        default:
            return;
        }
    }
}

void factor()
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
        digito();
        break;
    }
}

void digito()
{
    analisis = cadenaEntrada[indice];
    char pf = analisis;
    if (isdigit(analisis))
    {
        coincidir(analisis);
        cadenaPF += pf;
        return;
    }
    cerr << "Se introdujo un digito invalido" << endl;
    exit(1);
}
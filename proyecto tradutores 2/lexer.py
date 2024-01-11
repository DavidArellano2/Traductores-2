# -*- coding: utf-8 -*-
"""
Created on Mon Nov 20 19:51:30 2023

@author: David López
"""

import ply.lex as lex

# Lista de tokens
tokens = (
    'NUMBER',
    'PLUS',
    'MINUS',
    'TIMES',
    'DIVIDE',
    'LPAREN',
    'RPAREN',
)

# Expresiones regulares para tokens simples
t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_DIVIDE = r'/'
t_LPAREN = r'\('
t_RPAREN = r'\)'

# Token para números
def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t

# Ignorar caracteres espacio en blanco
t_ignore = ' \t'

# Manejo de errores
def t_error(t):
    #print("Carácter ilegal:", t.value[0])
    t.lexer.skip(1)

# Construir el analizador léxico
lexer = lex.lex()

# Ejemplo de uso
if __name__ == '__main__':
    lexer.input("3 + 4 * 5")
    while True:
        tok = lexer.token()
        if not tok:
            break
        print(tok)
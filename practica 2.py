# -*- coding: utf-8 -*-
"""
Created on Mon Oct  2 22:09:21 2023

@author: David López
"""

import tkinter as tk
from tkinter import ttk

# Función para verificar si un carácter es un operador
def es_operador(c):
    return c in ['+', '-', '*', '/']

# Función para obtener la precedencia de un operador
def precedencia(op):
    if op in ['+', '-']:
        return 1
    elif op in ['*', '/']:
        return 2
    return 0

# Función para convertir una expresión en notación postfija
def a_postfija(expresion):
    salida = []
    pila = []

    for token in expresion:
        if token.isnumeric():
            salida.append(token)
        elif token == '(':
            pila.append(token)
        elif token == ')':
            while pila and pila[-1] != '(':
                salida.append(pila.pop())
            pila.pop()
        else:
            while pila and precedencia(pila[-1]) >= precedencia(token):
                salida.append(pila.pop())
            pila.append(token)

    while pila:
        salida.append(pila.pop())

    return ' '.join(salida)

# Función para procesar la entrada y mostrar la notación postfija
def procesar_expresion():
    expresion = entrada.get()
    if expresion:
        resultado.set(a_postfija(expresion))

# Crear una ventana principal
ventana = tk.Tk()
ventana.title("Analizador Sintáctico Descendente")

# Etiqueta y entrada para ingresar la expresión
etiqueta = ttk.Label(ventana, text="Ingrese una expresión aritmética:")
etiqueta.pack()

entrada = ttk.Entry(ventana)
entrada.pack()

# Botón para procesar la expresión
boton = ttk.Button(ventana, text="Procesar", command=procesar_expresion)
boton.pack()

# Etiqueta para mostrar la notación postfija
resultado = tk.StringVar()
etiqueta_resultado = ttk.Label(ventana, textvariable=resultado)
etiqueta_resultado.pack()

ventana.mainloop()

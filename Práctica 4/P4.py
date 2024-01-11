import re
import tkinter as tk
from tkinter import font
from PIL import Image, ImageTk
import networkx as nx
import matplotlib.pyplot as plt

class Nodo:
    def __init__(self, operador, izquierda, derecha):
        self.operador = operador
        self.izquierda = izquierda
        self.derecha = derecha

class Hoja:
    def __init__(self, tipo, valor):
        self.tipo = tipo
        self.valor = valor

class TablaSimbolos:
    def __init__(self):
        self.tabla = {}

    def agregar(self, identificador, valor):
        self.tabla[identificador] = valor

    def obtener(self, identificador):
        return self.tabla.get(identificador, None)

def analizador_sintactico(expresion):
    tokens = re.findall(r'\d+|[-+*/()]|\w+', expresion)
    idx = 0

    def match(expected_token):
        nonlocal idx
        if idx < len(tokens) and tokens[idx] == expected_token:
            idx += 1
        else:
            raise Exception(f"Error de sintaxis: Se esperaba '{expected_token}'")

    def factor():
        if tokens[idx] == '(':  
            match('(')
            sub_arbol = expresion()
            match(')')
            return sub_arbol
        elif tokens[idx].isdigit():  
            num = Hoja('num', tokens[idx])
            match(tokens[idx])
            return num
        elif tokens[idx].isalpha():  
            id = Hoja('id', tokens[idx])
            match(tokens[idx])
            return id
        else:
            raise Exception("Error")

    def termino():
        left = factor()
        while idx < len(tokens) and tokens[idx] in ['*', '/']:
            operador = tokens[idx]
            match(operador)
            right = factor()
            left = Nodo(operador, left, right)
        return left

    def expresion():
        left = termino()
        while idx < len(tokens) and tokens[idx] in ['+', '-']:
            operador = tokens[idx]
            match(operador)
            right = termino()
            left = Nodo(operador, left, right)
        return left

    tabla_simbolos = TablaSimbolos()
    raiz = expresion()

    def construir_tabla_simbolos(nodo):
        if isinstance(nodo, Nodo):
            construir_tabla_simbolos(nodo.izquierda)
            construir_tabla_simbolos(nodo.derecha)
        elif isinstance(nodo, Hoja) and nodo.tipo == 'id':
            tabla_simbolos.agregar(nodo.valor, None)

    construir_tabla_simbolos(raiz)

    return raiz, tabla_simbolos

tSimbolos = ""  # Declarar tSimbolos como una variable global

def mostrar_tabla_simbolos(tabla_simbolos):
    global tSimbolos
    i = 0
    tSimbolos = "Tabla de símbolos:\n"
    for identificador in tabla_simbolos.tabla:
        i += 1
        valor = tabla_simbolos.obtener(identificador)
        tSimbolos += f"{i}\t{identificador}\t{valor}\n"
    tablaSimbolos.config(text=tSimbolos)  # Actualiza la etiqueta de la tabla de símbolos

def mostrar_grafo(raiz):
    global tGrafo
    tGrafo ="Tabla de grafo:\n"
    grafo = []

    def dfs(nodo):
        if isinstance(nodo, Nodo):
            left_id = dfs(nodo.izquierda)
            right_id = dfs(nodo.derecha)
            grafo.append((nodo.operador, left_id, right_id))
            return len(grafo)
        elif isinstance(nodo, Hoja):
            grafo.append((nodo.tipo, nodo.valor, None))
            return len(grafo)

    dfs(raiz)
    i = 0
    for item in grafo:
        i+=1
        if item[2] is not None:
            tGrafo +=f"{i}\t{item[0]}\t{item[1]}\t{item[2]}\n"
        else:
            tGrafo +=f"{i}\t{item[0]}\t{item[1]}\n"

def main():
    global tGrafo, tSimbolos
    expresion = entrada.get()
    raiz, tabla_simbolos = analizador_sintactico(expresion)
    mostrar_tabla_simbolos(tabla_simbolos)
    mostrar_grafo(raiz)

    tablaSimbolos.config(text=tSimbolos, anchor='w', justify='center')
    tablaGrafo.config(text=tGrafo, anchor='w', justify='left')

ventana = tk.Tk()
ventana.title("PRACTICA 4")

# Cambia el tamaño de la ventana
ventana.geometry("600x500")  # Cambia el ancho y alto

# Cambia el color de fondo de la ventana
ventana.configure(bg="gray")  # Cambia el color de fondo

# Crear una fuente personalizada después de crear la ventana
fuente_personalizada = font.Font(family="Algerian", size=12)  # Cambia "Arial" al tipo de fuente que desees y el tamaño

# Aplica la fuente personalizada a la etiqueta
etiqueta = tk.Label(ventana, text="Ingresa la expresión:", font=fuente_personalizada)
etiqueta.pack()

entrada = tk.Entry(ventana, font=fuente_personalizada)
entrada.pack()

# Crear un marco para contener las tablas
marco_tablas = tk.Frame(ventana)
marco_tablas.pack()

# Tabla de símbolos
tablaSimbolos = tk.Label(marco_tablas, text="", anchor='w', justify='left', font=fuente_personalizada)
tablaSimbolos.pack(side="left", padx=10, pady=10)

# Tabla de grafo
tablaGrafo = tk.Label(marco_tablas, text="", anchor="w", justify='left', font=fuente_personalizada)
tablaGrafo.pack(side="right", padx=10, pady=10)

# Cambia el tamaño y la forma de los botones a "ridge"
calcular_button = tk.Button(ventana, text="Hacer Grafo", command=main, font=fuente_personalizada, width=20, height=2, bg="black", fg="white")
calcular_button.pack()

ventana.mainloop()
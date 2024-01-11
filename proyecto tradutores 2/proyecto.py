import ply.yacc as yacc
from lexer import tokens
import tkinter as tk
from tkinter import filedialog, font
import re
import tkinter as tk
from tkinter import font
from PIL import Image, ImageTk
import networkx as nx
import matplotlib.pyplot as plt

# Reglas de la gramática
def p_expression(p):
    '''expression : expression PLUS term
                  | expression MINUS term
                  | term'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        if p[2] == '+':
            p[0] = p[1] + p[3]
        elif p[2] == '-':
            p[0] = p[1] - p[3]

def p_term(p):
    '''term : term TIMES factor
            | term DIVIDE factor
            | factor'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        if p[2] == '*':
            p[0] = p[1] * p[3]
        elif p[2] == '/':
            p[0] = p[1] / p[3]

def p_factor(p):
    '''factor : NUMBER
              | LPAREN expression RPAREN'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = p[2]

# Regla para manejar errores de sintaxis
def p_error(p):
    print("ARCHIVO INVÁLIDO :(")
    raise SyntaxError("Error de sintaxis en la entrada")

# Construir el analizador
parser = yacc.yacc()
# Crear la interfaz gráfica
ventana = tk.Tk()
ventana.title("< PROYECTO FINAL >")

# Agregar un subtítulo
subtitulo_label = tk.Label(ventana, text="El programa mostrará si el archivo es válido o inválido:", font=("Algerian", 14))
subtitulo_label.pack()

# Variable para almacenar el resultado y enlazarla con la etiqueta
result_var = tk.StringVar()

# Cambia el tamaño de la ventana
ventana.geometry("600x300")  # Cambia el ancho y alto

# Crear un Label para mostrar el resultado
resultado_label = tk.Label(ventana, textvariable=result_var, font=("Helvetica", 12))
resultado_label.pack()

# Función para analizar el archivo fuente
def parse_file(file_path):
    try:
        with open(file_path, 'r') as file:
            source_code = file.read()
            parser.parse(source_code)
            result_var.set("FELICIDADES, ARCHIVO VÁLIDO :)")
            resultado_label.config(fg="green")  # Cambia el color del texto a verde para indicar un resultado válido
    except SyntaxError as e:
        result_var.set("LO SENTIMOS, ARCHIVO INVÁLIDO :(")
        resultado_label.config(fg="red")  # Cambia el color del texto a rojo para indicar un resultado inválido

# Función para abrir un cuadro de diálogo y obtener la ruta del archivo
def open_file_dialog():
    file_path = filedialog.askopenfilename()
    if file_path:
        parse_file(file_path)

# Botón para abrir el cuadro de diálogo
open_button = tk.Button(ventana, text="Abrir Archivo", command=open_file_dialog, font=("Algerian", 12))
open_button.pack(pady=10)

# Texto con salto de línea
#texto_con_salto = "t_1 := 9\n_var1 := t_1\nt_2 :=22\n_var2 := t_2\nt_3 := _var1\nt_4 := _var2\nt_5 := t_3 + t_4\n_result := t_5\nif false _result > 25 jmp to jmp_1\nt_6 := 4\n_var2 := t_6\njmp to jmp_2\njmp_1:\nt_7 := 10\n_var2 := t_7\njmp_2:\n\njmp_3:\nif false _var1 < 15 jmp to jmp_4\nt_8 := _var1\nt_9 := 1\nt_10 := t_8 + t_9\n_var1 := t_10\njmp to jmp_3\njmp_4:"

# Label con texto y salto de línea
#label_con_salto = tk.Label(ventana, text=texto_con_salto, font=("Algerian", 13))
#label_con_salto.pack(pady=10)

# Iniciar el bucle de eventos de la interfaz gráfica
ventana.mainloop()
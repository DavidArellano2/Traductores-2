class Token:
    def __init__(self, type, value=None):
        self.type = type  # El tipo de simbolo (operador, parentesis, numero, etc.)
        self.value = value  # El valor del numero, si el tipo es numero

class Lexer:
    def __init__(self, input):
        self.input = input
        self.position = 0

    # Obtener el siguiente token en la secuencia
    def get_next_token(self):
        current_char = self.get_current_char()

        # Si el caracter actual es un numero, leer el numero completo
        if current_char.isdigit():
            value = int(current_char)
            self.advance_position()
            while self.get_current_char().isdigit():
                value = value * 10 + int(self.get_current_char())
                self.advance_position()
            return Token('n', value)
        # Si el caracter actual es un operador o parentesis, devolver el token correspondiente
        elif current_char == '+':
            self.advance_position()
            return Token('+')
        elif current_char == '*':
            self.advance_position()
            return Token('*')
        elif current_char == '(':
            self.advance_position()
            return Token('(')
        elif current_char == ')':
            self.advance_position()
            return Token(')')
        # Si no es ningun simbolo valido, lanzar una excepcion
        else:
            raise RuntimeError("Error de sintaxis: simbolo invalido")

    # Obtener el caracter actual de la cadena de entrada
    def get_current_char(self):
        if self.position >= len(self.input):
            return '\0'
        else:
            return self.input[self.position]

    # Avanzar la posicion actual en la cadena de entrada
    def advance_position(self):
        self.position += 1

class Parser:
    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = lexer.get_next_token()

    # Comprobar si el token actual es del tipo esperado y avanzar al siguiente token
    def eat(self, type):
        if self.current_token.type == type:
            self.current_token = self.lexer.get_next_token()
        else:
            raise RuntimeError(f"Error de sintaxis: se esperaba {type}, se encontro {self.current_token.type}")

    # Analizar un factor
    def factor(self):
        if self.current_token.type == '(':
            self.eat('(')
            self.expresion()
            self.eat(')')
        elif self.current_token.type == 'n':
            self.eat('n')
        else:
            raise RuntimeError("Error de sintaxis: se esperaba un factor")

    # Analizar un termino
    def termino(self):
        self.factor()
        while self.current_token.type in ('*', '/'):
            op = self.current_token.type
            self.eat(op)
            self.factor()

    # Analizar una expresion
    def expresion(self):
        self.termino()
        while self.current_token.type in ('+', '-'):
            op = self.current_token.type
            self.eat(op)
            self.termino()


lexer = Lexer('2+1')
parser = Parser(lexer)
parser.expresion()
import sys

import ply.lex as lex

reserved = {
    'istinno': 'ISTINNO', 'lozhno': 'LOZHNO', 'tseloye': 'TSELOYE', 'logicheskoe': 'LOGICHESKOE',
    'yacheyka': 'YACHEYKA', 'massiv': 'MASSIV', 'razmer': 'RAZMER', 'proverka': 'PROVERKA',
    'tsikl': 'TSIKL', 'nachalo': 'NACHALO', 'konets': 'KONETS',

    # robot

    'idi': 'IDI',
    'pered': 'PERED', 'vpered': 'VPERED', 'napered': 'NAPERED',
    'zad': 'ZAD', 'vzad': 'VZAD', 'nazad': 'NAZAD',
    'levo': 'LEVO', 'vlevo': 'VLEVO', 'nalevo': 'NALEVO',
    'pravo': 'PRAVO', 'vpravo': 'VPRAVO', 'napravo': 'NAPRAVO',
    'poverni': 'POVERNI', 'vzleti': 'VZLETI', 'smotri': 'SMOTRI',
    'ostanov': 'OSTANOV', 'gdeya': 'gdeya', 'funktsiya': 'FUNKTSIYA', 'esli': 'ESLI'}


class lexer(object):

    def __init__(self):
        self.lexer = lex.lex(module=self)

    tokens = ['DEC_NUMBER', 'VARIABLE', 'NEWLINE', 'EQUAL', 'PLUS', 'MINUS', 'UNARMINUS', 'AND', 'OR', 'GREATER', 'LESS',
                  'ASSIGNMENT', 'SEMICOLON', 'QUESTION', 'L_FIGBRACKET', 'R_FIGBRACKET'] + list(reserved.values())

    precedence = (
            ('left', 'ASSIGNMENT'),
            ('left', 'PLUS', 'MINUS'),
            ('right', 'UNARMINUS'),
            ('left', 'EQUAL'),
            ('left', 'GREATER', 'LESS'),
            ('left', 'QUESTION'),
            ('left', 'SEMICOLON')
        )

    t_EQUAL = r'\='
    t_PLUS = r'\+'
    t_MINUS = r'\-'
    t_UNARMINUS = r'~'
    t_AND = r'\&&'
    t_OR = r'\|\|'
    t_GREATER = r'\>'
    t_LESS = r'\<'
    t_ASSIGNMENT = r'\-\>'
    t_SEMICOLON = r'\;'
    t_QUESTION = r'\?'
    t_L_FIGBRACKET = r'\{'
    t_R_FIGBRACKET = r'\}'

    @staticmethod
    def t_DEC_NUMBER(t):
        r'(\-?(\d+))'
        t.value = int(t.value)
        return t

    @staticmethod
    def t_VARIABLE(t):
        r'[a-zA-Z][a-zA-Z_0-9]*'
        t.type = reserved.get(t.value, 'VARIABLE')
        return t

    @staticmethod
    def t_NEWLINE(t):
        r'\n+'
        t.lexer.lineno += t.value.count('\n')
        t.lexer.linestart = t.lexer.lexpos
        return t

    @staticmethod
    def t_error(t):
        sys.stderr.write(f'Error: Illegal character: {t.value[0]} at line {t.lexer.lineno}\n')
        t.lexer.skip(1)

    t_ignore = ' \t'

    def input(self, _data):
        return self.lexer.input(_data)

    def token(self):
        return self.lexer.token()


if __name__ == '__main__':
    f = open('../TestLEX.txt')
    data = f.read()
    f.close()
    lexer = lexer()
    lexer.input(data)
    while True:
        token = lexer.token()
        if token is None:
            break
        else:
            print(token)

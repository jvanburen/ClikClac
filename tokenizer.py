import binascii
from clacerror import ClacSyntaxError
import re

class Token:
    # integerpattern = re.compile(r"[0-9]+") #don't allow negatives because clac
    # identifierpattern = re.compile(r"[^0-9][^ \t\r\n]*")
    reserved = frozenset(('print', 'quit', 'drop', 'swap', 'rot', 'if', 'else',
                          'pick', 'input'))
    operators = frozenset(('<', '+', '-', '/', '*', '%'))

    def __init__(self, s, ln, col, file='stdin', line=None):
        self.s = str(s)
        self.ln = ln
        self.col = col
        self.line = line
        self.file = file
        self.macro=None
    
    def set_macro(self, macroname):
        self.macro = macroname
        
    def __repr__(self):
        return repr(self.s)
        
    def __hash__(self):
        return hash(self.s)
        
    def __eq__(self, other):
        return self is other
    
    def expect(self, token):
        if self.s != token:
            raise self.expectedError(token)
          
    def expectedError(self, expected):
        msg = 'Expected {}, but found {}'.format(expected, self.s)
        return ClacSyntaxError(msg + '\n' + self.traceback)
    
    @property
    def traceback(self):
        s = '  ' + "In file '{0.file}', line {0.ln}".format(self)
        if self.macro: s += ", in Macro '{}'".format(self.macro.name)
        if not self.line: return s
    
        s += '\n    ' + self.line
        s += '\n    ' + ' '*(self.col) + '^' + '-'*(len(self.s)-2) + '^'
        return s
    @property
    def is_integer(self):
        return type(self.s) == str and self.s.isdecimal()
    @property
    def is_identifier(self):
        # return self.s.isidentifier()
        return type(self.s) == str \
               and not self.is_reserved \
               and not self.is_integer \
               and not self.is_operator \
               and self.s.isprintable()
    @property
    def is_reserved(self):
        return self.s in Token.reserved
    @property
    def is_operator(self):
        return self.s in Token.operators
    @property
    def starts_macro(self):
        return self.s == ':'
    @property
    def ends_macro(self):
        return self.s == ';'
    
    def copy(self):
        return Token(self.s, self.ln, self.col, self.file, self.line)
        
class PartialToken:
    lineno = 0
    line = None
    file = None
    def __init__(self, start):
        self.l = []
        self.line = PartialToken.line
        self.lineno = PartialToken.lineno
        self.start = start
    def add_char(self, c):
        self.l.append(c)
        
    def token(self):
        return Token(''.join(self.l),
                     PartialToken.lineno,
                     self.start,
                     PartialToken.file,
                     PartialToken.line)
    
class Tokenizer:
    def __init__(self):
        self.files = {}
        self.tokens = []
        self.index = 0
        
    def tokenize(self, s, filename):
        PartialToken.file=filename
        self.files[filename] = s.split('\n')
        for line, toks in enumerate(self.files[filename]):
            PartialToken.line = toks
            PartialToken.lineno = line + 1
            current = None
            for col, char in enumerate(toks):
                if not char.isprintable():
                    raise ClacSyntaxError.unprintable(filename, line+1, col+1)
                elif current is not None:
                    if char.isspace():
                        self.tokens.append(current.token())
                        current = None
                    else:
                        current.add_char(char)
                elif not char.isspace():
                    current = PartialToken(col)
                    current.add_char(char)
                    
            if current is not None:
                self.tokens.append(current.token())
    
    def __iter__(self):
        return self

    def __next__(self):
        if self.index >= len(self.tokens):
            raise StopIteration
        self.index += 1
        return self.tokens[self.index-1]

    def reverse(self):
        if self.index == 0:
            raise StopIteration
        self.index -= 1

    def peek(self):
        if self.index >= len(self.tokens):
            raise ValueError("No Token to show")
        return self.tokens[self.index]
        
    def last(self):
        if self.index == 0:
            raise ValueError("No Token to show")
        return self.tokens[self.index - 1]

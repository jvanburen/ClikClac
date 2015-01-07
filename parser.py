# import re
from tokenizer import Tokenizer, Token
from clacerror import ClacIdentifierError, ClacSyntaxError, ClacError
from collections import deque
from macros import ClacMacro, SCMacros, Label, Jump, CondJump

class Parser:
    def __init__(self, inputs):
        self.identifiers = {}
        self.macros = set()
        self.T = Tokenizer()
        for name, prog in inputs:
            self.T.tokenize(prog, name)

        self.parse()
    
    def parse(self):
        self.make_macros()
        self.remove_unused()
        self.resolve_dependencies()
        self.add_labels()
        
    def new_macro(self):
        try: name = next(self.T)
        except StopIteration:
            raise ClacSyntaxError.unexpectedEOF(T.peek())
        if not name.is_identifier:
            raise ClacSyntaxError.expected("identifier", name)
        if name.is_reserved:
            raise ClacIdentifierError.reserved(name)
        if name in self.identifiers:
            raise ClacIdentifierError.redef(name)
        macro = ClacMacro(name.s)
        self.identifiers[name.s] = macro
        self.macros.add(macro)
        return macro
    
    def make_macros(self):
        current = None #None if we're outside a macro definition
        for token in self.T:
            # print("current:", current, "token:", token)
            if current is None:
                token.expect(':')
                current = self.new_macro()
            elif token.s in (';', ':'):
                token.expect(';')
                current = None
            else:
                current.add_token(token)
        if current:
            raise ClacSyntaxError.unexpectedEOF(self.T.last())

    def add_labels(self):
        def convert_ifs(macro):
            tokens = macro.tokens   
            labels = {}
            for index, token in enumerate(tokens):
                if token.s == 'if': 
                    if index+2 >= len(tokens):
                        raise ClacSyntaxError.iferror(macro, index)
                    if index+2 not in labels: labels[index+2] = Label()
                    tokens[index].s = CondJump(labels[index+2])
                elif token.s == 'else':
                    if index+1 >= len(tokens):
                        raise ClacSyntaxError.elseerror(macro, index)
                    if index+1 not in labels: labels[index+1] = Label()
                    tokens[index].s = Jump(labels[index+1])

            labelled = []
            for index, token in reversed(tuple(enumerate(tokens))):
                if index in labels: labelled.append(labels[index])
                labelled.append(token)
            labelled.reverse()
            macro.tokens = labelled
            
        for macro in self.macros:
            convert_ifs(macro)
    
    def remove_unused(self):
        def neighbors(macroname):
            for token in self.identifiers[macroname].dependencies:
                if token.s not in self.identifiers.keys():
                    raise ClacIdentifierError.undefined(token)
                yield token
        marked = {'main'}
        queue = ['main']
        
        while queue:
            v = queue.pop()
            for token in neighbors(v):
                if token.s not in self.identifiers.keys():
                    raise ClacIdentifierError.undefined(token)
                if token.s in marked: continue
                marked.add(token.s)
                queue.append(token.s)
        self.macros = set(m for m in self.macros if m.name in marked)
                
    def resolve_dependencies(self):
        for macro in self.macros:
            deps = set()
            for name in macro.dependencies:
                deps.add(self.identifiers[name.s])
            macro.tokendependencies = macro.dependencies
            macro.dependencies = set(deps)
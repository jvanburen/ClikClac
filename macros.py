from tokenizer import Token

class Label:
    count = 0
    def __init__(self):
        Label.count += 1
        self.N = Label.count
    def __repr__(self):
        return "<Label {}:>".format(self.N)
        
    def __str__(self):
        return "LABEL"+str(self.N)

class Jump:
    def __init__(self, label):
        self.label = label
    def __repr__(self):
        return "<JMP->{}>".format(self.label.N)

class CondJump(Jump):
    def __repr__(self):
        return "<Cond. JMP->{}>".format(self.label.N)    
        
class ClacMacro:
    def __init__(self, name, tokens=[], dependencies=set()):
        self.name = name
        self.tokens = tokens[:]
        self.dependencies = set(dependencies)

    def add_token(self, tok):
        if tok.is_identifier and not tok.is_reserved:
            self.dependencies.add(tok)
        self.tokens.append(tok)
        tok.set_macro(self)

    def copy_tokens(self):
        newlabels = {}
        copy = self.tokens[:]
        for i, tok in enumerate(copy):
            if isinstance(tok, Label):
                newlabels[tok] = Label()
                copy[i] = newlabels[tok]
        for i, tok in enumerate(copy):
            if isinstance(tok, Label):
                continue
            elif type(tok) == CondJump or type(tok.s) == CondJump:
                # import sys; print('asdfasdfasdfasdf', file=sys.stderr)
                copy[i] = tok.copy()
                copy[i].s = CondJump(newlabels[tok.s.label])
            if type(tok.s) == Jump:
                # import sys; print('copying', file=sys.stderr)
                copy[i] = tok.copy()
                copy[i].s = Jump(newlabels[tok.s.label])
        return copy

    def __hash__(self):
        return id(self)
    def __eq__(self, other):
        return self is other
    def __repr__(self):
        return "Macro<{}>".format(self.name)

class SCMacros:
    def __init__(self):
        self.macros = set()
        self.out = set()

    def add_macro(self, macro):
        for dep in macro.dependencies:
            self.out.add(dep)
        self.macros.add(macro)
        self.out -= self.macros

    def __iter__(self):
        return iter(self.macros)
    def __repr__(self):
        return "SCC" + repr(self.macros)
    def __hash__(self):
        return id(self)
    def __eq__(self, other):
        return self is other

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

        self.compile()
    
                
    def compile(self):
        self.make_macros()
        self.remove_unused()
        self.resolve_dependencies()
        self.generate_code_DG()
        self.add_labels()
        self.toposort()
        self.flatten()
        self.inline()
        
        #todo:
        #create list of program tokens for each SCC without inlining anything
        #convert if/else statements to conditional relative jumps
        #create list of if and else statements and their (relative) offsets for each SCC
        #topologically sort SCCs by dependencies
        #then, in reverse topological order, for each SCC, create a list of the
        #jump instructions and the ranges over which they operate.
        #then, inline macros by
        #replacing macro expansions to macros in different SCCs with the
        #processed macro bodies (unless some code size limitation is met?)
        #when a macro is inlined, find any relevant jumps and update their offsets
        #alternatively, insert labels into the token streams and when inlining
        #macros, make a copy of the bodies and update the jumps/labels to be
        #unique from the originals (I like this idea better :D)
        
        # sccs = self.find_scc()
        # topo = self.topo_sort(sccs)
        return
        
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
            macro.dependencies = frozenset(deps)
        
    def generate_code_DG(self):
        #Tarjan's algorithm
        sccs = set()
        counter = 0
        S = []
        index = {}
        lowlink = {}
        
        def sc(macro):
            nonlocal counter
            index[macro] = counter
            lowlink[macro] = counter
            counter += 1
            S.append(macro)

            for dep in macro.dependencies:
                if dep not in index:
                    sc(dep)
                    lowlink[macro] = min(lowlink[macro], lowlink[dep])
                elif dep in S:
                    lowlink[macro] = min(lowlink[macro], index[dep])
            if lowlink[macro] == index[macro]:
                cur = SCMacros()
                sccs.add(cur)
                
                v = None
                while v is not macro:
                    v = S.pop()
                    cur.add_macro(v)
            return
        
        
        for macro in self.macros:
            if macro not in index:
                sc(macro)
        
        self.component = {}
        for scc in sccs:
            for macro in scc:
                self.component[macro] = scc
        for scc in sccs:
            out = set()
            for macro in scc.out:
                out.add(self.component[macro])
            scc.out = out
        self.sccs = sccs

    def toposort(self):
        sccs = []
        incoming = {node:len(node.out) for node in self.sccs}
        rev = {node:set() for node in self.sccs} #edge-reversed graph
        for node in self.sccs:
            for nbr in node.out:
                rev[nbr].add(node)
        q = deque(node for node in self.sccs if incoming[node] == 0)
        while q:
            node = q.pop()
            sccs.append(node)
            for nbr in rev[node]:
                if incoming[nbr] == 1:
                    q.appendleft(nbr)
                incoming[nbr] -= 1
        self.sccs = sccs
        
    def flatten(self):
        #make sure that the sccs are ordered!
        macros = []
        for scc in self.sccs:
            for macro in scc:
                macros.append(macro)
        self.macros = macros
        self.defs = macros
        self.main = self.identifiers['main']
        self.defs.remove(self.main)

    def inline(self):
        def neighbors(macro):
            scc = self.component[macro].macros
            for neighbor in macro.dependencies:
                if neighbor in scc: continue
                yield neighbor.name
                
        for macro in self.macros:
            # import sys
            # print("beforemacro:", macro.name, "tokens:", macro.tokens, file=sys.stderr)
            nbrs = frozenset(neighbors(macro))
            tokens = []
            for token in macro.tokens:
                if isinstance(token, Token):
                    if token.s in nbrs:
                        dep = self.identifiers[token.s]
                        tokens.extend(dep.copy_tokens())
                    else: tokens.append(token)
                else: tokens.append(token)

            # print("aftermacro:", macro.name, "tokens:", tokens, file=sys.stderr)
            macro.tokens = tokens 
            
                
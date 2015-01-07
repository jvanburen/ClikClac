        # What happens: 
        # create list of program tokens for each SCC without inlining anything
        # convert if/else statements to conditional relative jumps
        # create list of if and else statements and their (relative) offsets for each SCC
        # topologically sort SCCs by dependencies
        # then, in reverse topological order, for each SCC, create a list of the
        # jump instructions and the ranges over which they operate.
        # then, inline macros by
        # replacing macro expansions to macros in different SCCs with the
        # processed macro bodies (unless some code size limitation is met?) (TODO: later)
        # Insert labels into the token streams and when inlining
        # macros, make a copy of the bodies and update the jumps/labels to be
        # unique from the originals (I like this idea better :D)
class Optimizer:
    def __init__(self, parser, options):
        self.macros = parser.macros
        self.options = options
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
        # import pdb; pdb.set_trace()
        def neighbors(macro):
            scc = self.component[macro].macros
            for neighbor in macro.dependencies:
                if neighbor in scc: continue
                yield neighbor.name
                
        for macro in self.defs:
            # import sys
            # print("beforemacro:", macro.name, "tokens:", macro.tokens, file=sys.stderr)
            nbrs = frozenset(neighbors(macro))
            inlined = set()
            tokens = []
            for token in macro.tokens:
                if isinstance(token, Token) and token.s in nbrs:
                    dep = self.identifiers[token.s]
                    # print("copying tokens of", token.s, file=__import__("sys").stderr)
                    tokens.extend(dep.copy_tokens())
                    inlined.add(dep)
                else: tokens.append(token)

            # print("aftermacro:", macro.name, "tokens:", tokens, file=sys.stderr)
            macro.tokens = tokens
            # import pdb; pdb.set_trace()
            # deps = frozenset(self.identifiers[t.s] for t in tokens if isinstance(t, Token) and t.s in self.identifiers)
            macro.dependencies -= inlined
        
        #remove unused again
        # import pdb; pdb.set_trace()
        marked = {self.main}
        queue = [self.main]
        
        while queue:
            v = queue.pop()
            for macro in v.dependencies:
                if macro in marked: continue
                marked.add(macro)
                queue.append(macro)
        
        # import pdb; pdb.set_trace()
        self.defs = frozenset(m for m in self.macros if m in marked)
        # self.defs = self.macros

    
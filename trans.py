from macros import Jump, CondJump, Label

class Language:
    @classmethod
    def transpile(cls, macro):
        translator = {
            'print': cls.output,
            'quit': cls.abort,
            'drop': cls.drop,
            'swap': cls.swap,
            'rot': cls.rot,
            'pick': cls.pick,
            'input': cls.input,
            '<': cls.lt,
            '+': cls.add,
            '-': cls.sub,
            '/': cls.div,
            '*': cls.mul,
            '%': cls.mod
        }
        args = {
            'print': 1,
            'quit': 0,
            'drop': 1,
            'swap': 2,
            'rot': 3,
            'pick': 1,
            'input': 0,
            '<': 2,
            '+': 2,
            '-': 2,
            '/': 2,
            '*': 2,
            '%': 2
        }
        tokens = macro.tokens
        lines = []
        if macro.name == 'main':
            lines.append(cls.main_init(macro));
        current = []
        for token in tokens:
            # print('transpiling', token)
            lines.append(cls.line_preamble(token))
            line = []
            
            if isinstance(token, str):
                line.append(token)
            elif isinstance(token, Label):
                line.append(cls.label(token))
            elif isinstance(token.s, CondJump):
                line.append(cls.cjmp(token.s))
            elif isinstance(token.s, Jump):
                line.append(cls.jmp(token.s))
            elif token.is_integer:
                line.append(cls.integer(token))
                line.append(cls.epilogue(token))
            elif token.is_reserved or token.is_operator:
                if args[token.s]:
                    line.append(cls.check_size(args[token.s]))
                line.append(translator[token.s](token))
                if token.s != 'pick':
                    line.append(cls.epilogue(token))
            elif token.is_identifier:
                line.append(cls.call(token))
            else:
                assert False, "what is token " + repr(token)
            lines.append(' '.join(line))
        if macro.name == 'main':
            lines.append(cls.main_cleanup(macro))
        return '\n'.join(lines)
    
    
    @classmethod
    def main_init(cls, token):
        return ""
        
    @classmethod
    def main_cleanup(cls, token):
        return ""
    
    @classmethod
    def line_preamble(cls, token):
        return ""
        
    @classmethod
    def epilogue(cls, token):
        return ""
    
    @classmethod
    def check_size(cls, size):
        pass
    
    @classmethod
    def lt(cls, token):
        pass
    
    @classmethod
    def add(cls, token):
        pass
    
    @classmethod
    def sub(cls, token):
        pass
        
    @classmethod
    def mul(cls, token):
        pass
        
    @classmethod
    def div(cls, token):
        pass
        
    @classmethod
    def mod(cls, token):
        pass
    
    @classmethod
    def output(cls, token):
        pass
        
    @classmethod
    def output(cls, token):
        pass
        
    @classmethod
    def abort(cls, token):
        pass
    
    @classmethod
    def drop(cls, token):
        pass
        
    @classmethod
    def swap(cls, token):
        pass
    
    @classmethod
    def rot(cls, token):
        pass
        
    @classmethod
    def jmp(cls, jump):
        NotImplemented()
        
    @classmethod
    def cjmp(cls, token):
        pass
       
    @classmethod
    def pick(cls, token):
        pass
        
    @classmethod
    def call(cls, token):
        pass
    
    @classmethod
    def label(cls, label):
        pass
    
    @classmethod
    def integer(cls, token):
        pass
    

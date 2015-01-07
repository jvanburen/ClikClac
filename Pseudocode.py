from parser import Parser
from trans import Language
from macros import ClacMacro, Label, Jump, CondJump
from tokenizer import Token
import os, re

class Pseudocode(Language):
    options = {}
    with open("header.c", 'rt') as f:
        header = f.read()
    
    @classmethod
    def id_name(cls, s):
        name = ["MACRO_"]
        for char in s:
            if char.isalnum(): name.append(char) 
            else: name.append('_'+ hex(ord(char))[2:])
        return ''.join(name)
        
    #overridden methods

    @classmethod
    def main_init(cls, macro):
        return ""
    @classmethod
    def main_cleanup(cls, macro):
        return ""
    @classmethod
    def line_preamble(cls, token):
        try:
            if cls.options['nopreamble']: return ""
        except KeyError: pass
        
        if isinstance(token, Token):
            if os.path.exists(token.file):
                return "#line {} \"{}\"".format(token.ln, token.file)
            else:
                return "#line {}".format(token.ln)
        return ""
    @classmethod
    def epilogue(cls, token):
        return ""
    @classmethod
    def check_size(cls, size):
        return ""
    @classmethod
    def lt(cls, token):
        return "cmp"
    @classmethod
    def add(cls, token):
        return "add"
    @classmethod
    def sub(cls, token):
        return "sub"
    @classmethod
    def mul(cls, token):
        return "mul"
    @classmethod
    def div(cls, token):
        return "div"
    @classmethod
    def mod(cls, token):
        return "mod"
    @classmethod
    def output(cls, token):
        return "output"
    @classmethod
    def input(cls, token):
        return "input";
    @classmethod
    def abort(cls, token):
        return "abort"
    @classmethod
    def drop(cls, token):
        return "drop"
    @classmethod
    def swap(cls, token):
        return "swap"
    @classmethod
    def rot(cls, token):
        return "rot"
    @classmethod
    def jmp(cls, jump):
        return "jmp {}".format(str(jump.label))
    @classmethod
    def cjmp(cls, jump):
        return "jz {}".format(str(jump.label))
    @classmethod
    def pick(cls, token):
        return "pick"
    @classmethod
    def call(cls, token):
        return "call {}".format(cls.id_name(token.s))
    @classmethod
    def integer(cls, token):
        return "push {}".format(token.s)
    @classmethod
    def label(cls, label):
        return "@label {}:".format(str(label))
        
    @classmethod
    def convert(cls, inputs, **kwargs):
        cls.options = kwargs
        p = Parser(inputs)
        defs = p.defs
        main = p.main
        
        prog = []
    
        for macro in defs:
            prog.append(cls.id_name(macro.name)+":")
            prog.append(cls.transpile(macro))
            prog.append("#"+ "_"*20)
    
        prog.append("MAIN:")
        prog.append(cls.transpile(main))
        prog.append("#"+ "_"*20)
    
        return '\n'.join(filter(None, prog))
    

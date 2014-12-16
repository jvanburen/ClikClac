from parser import Parser
from trans import Language
from macros import ClacMacro, Label, Jump, CondJump
from tokenizer import Token
import os

class C(Language):
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
        return "allocated = SMALL_STACK_SIZE;\n"\
              +"stack = malloc(allocated*sizeof(clac_t));\n"\
              +"sp=stack-1;\n"
    @classmethod
    def main_cleanup(cls, macro):
        # return "free(stack);"
        return ""
    @classmethod
    def line_preamble(cls, token):
        if isinstance(token, Token):
            if os.path.exists(token.file):
                return "#line {} \"{}\"".format(token.ln, token.file)
            else:
                return "#line {}".format(token.ln)
        return ""
    @classmethod
    def epilogue(cls, token):
        return "STACK_RESIZE();"
    @classmethod
    def check_size(cls, size):
        return "CHECK_SIZE({});".format(size)
    @classmethod
    def lt(cls, token):
        return "sp--; *sp = *sp < *(sp+1);"
    @classmethod
    def add(cls, token):
        return "sp--; *sp = *sp + *(sp+1);"
    @classmethod
    def sub(cls, token):
        return "sp--; *sp = *sp - *(sp+1);"
    @classmethod
    def mul(cls, token):
        return "sp--; *sp = *sp * *(sp+1);"
    @classmethod
    def div(cls, token):
        return "CHECK_DIV(); sp--; *sp = *sp / *(sp+1);"
    @classmethod
    def mod(cls, token):
        return "CHECK_DIV(); sp--; *sp = *sp % *(sp+1);"
    @classmethod
    def output(cls, token):
        return "printf(\"%d\\n\", *sp--);"
    @classmethod
    def input(cls, token):
        return "scanf(\"%d\", ++sp);";
    @classmethod
    def abort(cls, token):
        return "sp--; *sp = *sp * *(sp+1);"
    @classmethod
    def drop(cls, token):
        return "sp--;"
    @classmethod
    def swap(cls, token):
        return "{clac_t temp = *sp; *sp = *(sp-1); *(sp-1) = temp;};"
    @classmethod
    def rot(cls, token):
        return "{clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;};"
    @classmethod
    def jmp(cls, jump):
        return "STACK_RESIZE();goto {};".format(str(jump.label))
    @classmethod
    def cjmp(cls, jump):
        return "if (!*sp--){{STACK_RESIZE();goto {};}}".format(str(jump.label))
    @classmethod
    def pick(cls, token):
        return "CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};"
    @classmethod
    def call(cls, token):
        return "{}();".format(C.id_name(token.s))
    @classmethod
    def integer(cls, token):
        return "*++sp = {};".format(token.s)
    @classmethod
    def label(cls, label):
        return "{}:".format(str(label))

def convert(inputs):
    p = Parser(inputs)
    defs = p.defs
    main = p.main
    
    prog = [C.header]

    for macro in defs:
        prog.append("void {}(void);".format(C.id_name(macro.name)))
    prog.append("int main(void);")

    for macro in defs:
        prog.append("void {}(void) {{".format(C.id_name(macro.name)))
        prog.append(C.transpile(macro))
        prog.append("return;\n}")
    
    prog.append("int main(void){")
    prog.append(C.transpile(main))
    prog.append("return 0;\n}")
   
    return '\n'.join(filter(None, prog))
  

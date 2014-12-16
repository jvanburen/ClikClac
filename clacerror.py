class ClacError(Exception):
    line = 1
    @staticmethod
    def set_line(line):
        ClacError.line = line

class ClacSyntaxError(ClacError):
    @classmethod
    def expected(cls, expected, token):
        return cls("\n{}\n  Expected {}, but found '{}'"
                   .format(token.traceback, expected, token.s))
    @classmethod
    def unexpectedEOF(cls, preceding):
        s = '  ' + "In file '{0.file}', line{0.ln}".format(preceding)
        if preceding.line:
            s += '\n    ' + preceding.line
            s += '\n    ' + ' '*(preceding.col+len(preceding.s)) + '^'
        return cls("Unexpected EOF while parsing\n" + s)
    @classmethod
    def unprintable(cls, file, line, col):
        return cls("\n  File {}, line {}:, col {}\n\
    unprintable character encountered".format(file, line, col))
    
    @classmethod
    def iferror(cls, macro, index):
        return cls("\n  In Macro {} at token #{}:\n\t\
if statements need at least 2 tokens after".format(macro.name, index+1))
    @classmethod
    def elseerror(cls, macro, index):
        return cls("\n  In Macro {} at token #{}:\n\t\
else statements need at least 1 token after".format(macro.name, index+1))

class ClacIdentifierError(ClacError):
    @classmethod
    def undefined(cls, token):
        return cls("\n{}\n  Undefined identifier: '{}'"
                   .format(token.traceback, token.s))
    @classmethod
    def reserved(cls, token):
        return cls("\n{}\n  Cannot assign to reserved identifier '{}'"
                   .format(token.traceback, token.s))
    @classmethod
    def redefined(cls, name):
        return cls("\n{}\n  Redefinition of identifier '{}'"
                   .format(token.traceback, token.s))

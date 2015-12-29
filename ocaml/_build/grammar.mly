%token <int> INT
%token <string> ID
%token LESS_THAN
%token PLUS
%token MINUS
%token DIV
%token MUL
%token MOD
%token COLON
%token SEMICOLON
%token PRINT
%token QUIT
%token DROP
%token SWAP
%token ROT
%token IF
%token ELSE
%token PICK
%token INPUT
%token EOF

%{
  open Token
%}

%start <Token.macro list option> prog
%%

prog:
  | EOF       { None }
  | ms=nonempty_list(macro);EOF { Some ms };

macro: 
  | COLON; nametok=ID; bodytoks=list(tok); SEMICOLON
    { Macro(nametok, bodytoks) };

tok:
  | x=simple_tok 
    { Simple(x) }
  | IF; thentok=simple_tok
    { Ifthen(thentok) }
  | IF; thentok=simple_tok; ELSE; elsethen=simple_tok 
    { Ifelsethen(thentok, elsethen) };

simple_tok:
  | LESS_THAN           { Lt }
  | PLUS                { Add }
  | MINUS               { Sub }
  | DIV                 { Div }
  | MUL                 { Mul }
  | MOD                 { Mod }
  | ROT                 { Rot }
  | QUIT                { Quit }
  | DROP                { Drop }
  | SWAP                { Swap }
  | PICK                { Pick }
  | INPUT               { Input }
  | PRINT               { Print }
  | x = INT             { Const x }
  | x = ID              { Macroname x };

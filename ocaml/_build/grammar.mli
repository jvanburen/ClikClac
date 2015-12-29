
(* The type of tokens. *)

type token = 
  | SWAP
  | SEMICOLON
  | ROT
  | QUIT
  | PRINT
  | PLUS
  | PICK
  | MUL
  | MOD
  | MINUS
  | LESS_THAN
  | INT of (int)
  | INPUT
  | IF
  | ID of (string)
  | EOF
  | ELSE
  | DROP
  | DIV
  | COLON

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val prog: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Token.macro list option)

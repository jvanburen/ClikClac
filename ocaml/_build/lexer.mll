{
open Core.Std
open Lexing
open Grammar

exception SyntaxError of string

let next_line lexbuf =
  let pos = lexbuf.lex_curr_p in
    lexbuf.lex_curr_p <-
      { pos with pos_bol = lexbuf.lex_curr_pos;
                pos_lnum = pos.pos_lnum + 1
      }
}

let int = '-'? ['0'-'9'] ['0'-'9']*
let digit = ['0'-'9']
let white = [' ' '\t' ]+
let newline = '\r' | '\n' | "\r\n"
let id = ['\x21'-'\x7e']+

rule read =
  parse
  | white   { read lexbuf }
  | newline { next_line lexbuf; read lexbuf }
  | int     { INT (int_of_string (Lexing.lexeme lexbuf)) }
  | '<'     { LESS_THAN }
  | '+'     { PLUS }
  | '-'     { MINUS }
  | '*'     { MUL }
  | '/'     { DIV }
  | '%'     { MOD }
  | ':'     { COLON }
  | ';'     { SEMICOLON }
  | "print" { PRINT }
  | "quit"  { QUIT }
  | "drop"  { DROP }
  | "swap"  { SWAP }
  | "rot"   { ROT }
  | "if"    { IF }
  | "else"  { ELSE }
  | "pick"  { PICK }
  | "input" { INPUT }
  | eof     { EOF }
  | id      { ID(Lexing.lexeme lexbuf) }
  | _ { raise (SyntaxError ("Unexpected char: " ^ Lexing.lexeme lexbuf)) }
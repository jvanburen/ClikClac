type simple_tok =
  | Lt
  | Add
  | Sub
  | Div
  | Mul
  | Mod
  | Rot
  | Quit
  | Drop
  | Swap
  | Pick
  | Input
  | Print
  | Const of int
  | Macroname of bytes


type tok = 
  | Simple of simple_tok
  | Ifthen of simple_tok
  | Ifelsethen of (simple_tok * simple_tok)


type macro = 
  | Macro of (bytes * tok list)


let simple_tok_to_string = function
  | Lt     -> "Lt"
  | Add    -> "Add"
  | Sub    -> "Sub"
  | Div    -> "Div"
  | Mul    -> "Mul"
  | Mod    -> "Mod"
  | Rot    -> "Rot"
  | Quit   -> "Quit"
  | Drop   -> "Drop"
  | Swap   -> "Swap"
  | Pick   -> "Pick"
  | Input  -> "Input"
  | Print  -> "Print"
  | Const value -> "push:" ^ (string_of_int value)
  | Macroname name -> "call:" ^ (Bytes.to_string name)

let hex_alphabet = "0123456789abcdef";;

let show_hex out c = 
  let d1 = (Char.code c) mod 16 in
  let d2 = (Char.code c) / 16 in
  let hex = (String.sub hex_alphabet d1 (d1+1) )
      ^ (String.sub hex_alphabet d2 (d2+1)) in
      output_string out hex

let show_simple_tok out tok =
  output_string out (simple_tok_to_string tok)

let show_tok out tok =
  let put thing = output_string out thing in
    match tok with
    | Simple tok ->
      (show_simple_tok out tok; put " ")
    | Ifthen thentok ->
      (put "If("; show_simple_tok out thentok; put ") ")
    | Ifelsethen (thentok,elsethen) ->
      (put "Ifelse(";
        show_simple_tok out thentok;
        put ")Else(";
        show_simple_tok out elsethen;
        put ") "
      )

let show_macro out (Macro(macroname, macrobody)) =
  output_string out "\nListing for macro ";
  (* Bytes.iter (fun name -> show_hex out name) macroname; *)
  output_string out (Bytes.unsafe_to_string @@ Bytes.escaped macroname);
  output_string out ":\n";
  List.iter (show_tok out) macrobody;
  output_string out "\n";()

let show_ast out ast =
  List.iter (fun mac -> show_macro out mac) ast


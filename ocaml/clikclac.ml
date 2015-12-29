open Core.Std

let do_hash file () =
  In_channel.with_file file ~f:(fun ic ->
    print_char |> print_endline
  )

let get_inchan = function
  | None | Some "-" ->
    In_channel.stdin
  | Some filename ->
    In_channel.create ~binary:true filename

let command = 
  Command.basic
    ~summary:"ClikClac"
    ~readme:(fun () -> "More detailed information")
    Command.Spec.(empty +> anon (maybe ("filename" %: file)))
    do_hash


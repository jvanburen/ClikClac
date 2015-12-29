open Core.Std;;

let compile_clac filename = 
  let tokq : String Core_queue = Core_queue() in
  Out_channel.output_lines stdout (In_channel.read_lines filename);;

let args =
  let open Command.Spec in
  empty +> anon ("filename" %: string)

let command =
  Command.basic
    ~summary:"Cross-compile clac into code of some sort"
    ~readme:(fun () -> "Only God can help you now")
    args
    (fun filename () -> compile_clac filename)

let () =
  Command.run ~version:"1.0" ~build_info:"RWO" command

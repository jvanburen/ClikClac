
exception Error

let _eRR =
  Error

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

type _menhir_env = {
  _menhir_lexer: Lexing.lexbuf -> token;
  _menhir_lexbuf: Lexing.lexbuf;
  _menhir_token: token;
  mutable _menhir_error: bool
}

and _menhir_state = 
  | MenhirState31
  | MenhirState23
  | MenhirState21
  | MenhirState16
  | MenhirState3
  | MenhirState0
  
  open Token

let rec _menhir_goto_nonempty_list_macro_ : _menhir_env -> 'ttv_tail -> _menhir_state -> (Token.macro list) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
    match _menhir_s with
    | MenhirState0 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | EOF ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, ms) = _menhir_stack in
            let _2 = () in
            let _v : (Token.macro list option) =                                 ( Some ms ) in
            _menhir_goto_prog _menhir_env _menhir_stack _menhir_s _v
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState31 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, x), _, xs) = _menhir_stack in
        let _v : (Token.macro list) =     ( x :: xs ) in
        _menhir_goto_nonempty_list_macro_ _menhir_env _menhir_stack _menhir_s _v
    | _ ->
        _menhir_fail ()

and _menhir_fail : unit -> 'a =
  fun () ->
    Printf.fprintf Pervasives.stderr "Internal failure -- please contact the parser generator's developers.\n%!";
    assert false

and _menhir_goto_tok : _menhir_env -> 'ttv_tail -> _menhir_state -> (Token.tok) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
    let _menhir_stack = Obj.magic _menhir_stack in
    assert (not _menhir_env._menhir_error);
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | DIV ->
        _menhir_run19 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | DROP ->
        _menhir_run18 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | ID _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState23 _v
    | IF ->
        _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | INPUT ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | INT _v ->
        _menhir_run14 _menhir_env (Obj.magic _menhir_stack) MenhirState23 _v
    | LESS_THAN ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | MINUS ->
        _menhir_run12 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | MOD ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | MUL ->
        _menhir_run10 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | PICK ->
        _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | PLUS ->
        _menhir_run8 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | PRINT ->
        _menhir_run7 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | QUIT ->
        _menhir_run6 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | ROT ->
        _menhir_run5 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | SWAP ->
        _menhir_run4 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | SEMICOLON ->
        _menhir_reduce1 _menhir_env (Obj.magic _menhir_stack) MenhirState23
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState23

and _menhir_goto_list_tok_ : _menhir_env -> 'ttv_tail -> _menhir_state -> (Token.tok list) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
    match _menhir_s with
    | MenhirState23 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s, x), _, xs) = _menhir_stack in
        let _v : (Token.tok list) =     ( x :: xs ) in
        _menhir_goto_list_tok_ _menhir_env _menhir_stack _menhir_s _v
    | MenhirState3 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | SEMICOLON ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _menhir_env = _menhir_discard _menhir_env in
            let _menhir_stack = Obj.magic _menhir_stack in
            let (((_menhir_stack, _menhir_s), nametok), _, bodytoks) = _menhir_stack in
            let _4 = () in
            let _1 = () in
            let _v : (Token.macro) =     ( Macro(nametok, bodytoks) ) in
            let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
            let _menhir_stack = Obj.magic _menhir_stack in
            assert (not _menhir_env._menhir_error);
            let _tok = _menhir_env._menhir_token in
            (match _tok with
            | COLON ->
                _menhir_run2 _menhir_env (Obj.magic _menhir_stack) MenhirState31
            | EOF ->
                let _menhir_stack = Obj.magic _menhir_stack in
                let (_menhir_stack, _menhir_s, x) = _menhir_stack in
                let _v : (Token.macro list) =     ( [ x ] ) in
                _menhir_goto_nonempty_list_macro_ _menhir_env _menhir_stack _menhir_s _v
            | _ ->
                assert (not _menhir_env._menhir_error);
                _menhir_env._menhir_error <- true;
                _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState31)
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | _ ->
        _menhir_fail ()

and _menhir_goto_simple_tok : _menhir_env -> 'ttv_tail -> _menhir_state -> (Token.simple_tok) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_stack = (_menhir_stack, _menhir_s, _v) in
    match _menhir_s with
    | MenhirState16 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        assert (not _menhir_env._menhir_error);
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | ELSE ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let _menhir_env = _menhir_discard _menhir_env in
            let _tok = _menhir_env._menhir_token in
            (match _tok with
            | DIV ->
                _menhir_run19 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | DROP ->
                _menhir_run18 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | ID _v ->
                _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState21 _v
            | INPUT ->
                _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | INT _v ->
                _menhir_run14 _menhir_env (Obj.magic _menhir_stack) MenhirState21 _v
            | LESS_THAN ->
                _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | MINUS ->
                _menhir_run12 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | MOD ->
                _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | MUL ->
                _menhir_run10 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | PICK ->
                _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | PLUS ->
                _menhir_run8 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | PRINT ->
                _menhir_run7 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | QUIT ->
                _menhir_run6 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | ROT ->
                _menhir_run5 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | SWAP ->
                _menhir_run4 _menhir_env (Obj.magic _menhir_stack) MenhirState21
            | _ ->
                assert (not _menhir_env._menhir_error);
                _menhir_env._menhir_error <- true;
                _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState21)
        | DIV | DROP | ID _ | IF | INPUT | INT _ | LESS_THAN | MINUS | MOD | MUL | PICK | PLUS | PRINT | QUIT | ROT | SEMICOLON | SWAP ->
            let _menhir_stack = Obj.magic _menhir_stack in
            let ((_menhir_stack, _menhir_s), _, thentok) = _menhir_stack in
            let _1 = () in
            let _v : (Token.tok) =     ( Ifthen(thentok) ) in
            _menhir_goto_tok _menhir_env _menhir_stack _menhir_s _v
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            let _menhir_stack = Obj.magic _menhir_stack in
            let (_menhir_stack, _menhir_s, _) = _menhir_stack in
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s)
    | MenhirState21 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (((_menhir_stack, _menhir_s), _, thentok), _, elsethen) = _menhir_stack in
        let _3 = () in
        let _1 = () in
        let _v : (Token.tok) =     ( Ifelsethen(thentok, elsethen) ) in
        _menhir_goto_tok _menhir_env _menhir_stack _menhir_s _v
    | MenhirState3 | MenhirState23 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, x) = _menhir_stack in
        let _v : (Token.tok) =     ( Simple(x) ) in
        _menhir_goto_tok _menhir_env _menhir_stack _menhir_s _v
    | _ ->
        _menhir_fail ()

and _menhir_reduce1 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _v : (Token.tok list) =     ( [] ) in
    _menhir_goto_list_tok_ _menhir_env _menhir_stack _menhir_s _v

and _menhir_run4 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Swap ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run5 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Rot ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run6 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Quit ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run7 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Print ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run8 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Add ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run9 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Pick ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run10 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Mul ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run11 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Mod ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run12 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Sub ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run13 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Lt ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run14 : _menhir_env -> 'ttv_tail -> _menhir_state -> (int) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let x = _v in
    let _v : (Token.simple_tok) =                         ( Const x ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run15 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Input ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run16 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_stack = (_menhir_stack, _menhir_s) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | DIV ->
        _menhir_run19 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | DROP ->
        _menhir_run18 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | ID _v ->
        _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState16 _v
    | INPUT ->
        _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | INT _v ->
        _menhir_run14 _menhir_env (Obj.magic _menhir_stack) MenhirState16 _v
    | LESS_THAN ->
        _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | MINUS ->
        _menhir_run12 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | MOD ->
        _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | MUL ->
        _menhir_run10 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | PICK ->
        _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | PLUS ->
        _menhir_run8 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | PRINT ->
        _menhir_run7 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | QUIT ->
        _menhir_run6 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | ROT ->
        _menhir_run5 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | SWAP ->
        _menhir_run4 _menhir_env (Obj.magic _menhir_stack) MenhirState16
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState16

and _menhir_run17 : _menhir_env -> 'ttv_tail -> _menhir_state -> (string) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let x = _v in
    let _v : (Token.simple_tok) =                         ( Macroname x ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run18 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Drop ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_run19 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_env = _menhir_discard _menhir_env in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = () in
    let _v : (Token.simple_tok) =                         ( Div ) in
    _menhir_goto_simple_tok _menhir_env _menhir_stack _menhir_s _v

and _menhir_errorcase : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    match _menhir_s with
    | MenhirState31 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState23 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState21 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s, _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState16 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState3 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let ((_menhir_stack, _menhir_s), _) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s
    | MenhirState0 ->
        let _menhir_stack = Obj.magic _menhir_stack in
        raise _eRR

and _menhir_goto_prog : _menhir_env -> 'ttv_tail -> _menhir_state -> (Token.macro list option) -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s _v ->
    let _menhir_stack = Obj.magic _menhir_stack in
    let _menhir_stack = Obj.magic _menhir_stack in
    let _1 = _v in
    Obj.magic _1

and _menhir_run2 : _menhir_env -> 'ttv_tail -> _menhir_state -> 'ttv_return =
  fun _menhir_env _menhir_stack _menhir_s ->
    let _menhir_stack = (_menhir_stack, _menhir_s) in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | ID _v ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = (_menhir_stack, _v) in
        let _menhir_env = _menhir_discard _menhir_env in
        let _tok = _menhir_env._menhir_token in
        (match _tok with
        | DIV ->
            _menhir_run19 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | DROP ->
            _menhir_run18 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | ID _v ->
            _menhir_run17 _menhir_env (Obj.magic _menhir_stack) MenhirState3 _v
        | IF ->
            _menhir_run16 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | INPUT ->
            _menhir_run15 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | INT _v ->
            _menhir_run14 _menhir_env (Obj.magic _menhir_stack) MenhirState3 _v
        | LESS_THAN ->
            _menhir_run13 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | MINUS ->
            _menhir_run12 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | MOD ->
            _menhir_run11 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | MUL ->
            _menhir_run10 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | PICK ->
            _menhir_run9 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | PLUS ->
            _menhir_run8 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | PRINT ->
            _menhir_run7 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | QUIT ->
            _menhir_run6 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | ROT ->
            _menhir_run5 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | SWAP ->
            _menhir_run4 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | SEMICOLON ->
            _menhir_reduce1 _menhir_env (Obj.magic _menhir_stack) MenhirState3
        | _ ->
            assert (not _menhir_env._menhir_error);
            _menhir_env._menhir_error <- true;
            _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState3)
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        let (_menhir_stack, _menhir_s) = _menhir_stack in
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) _menhir_s

and _menhir_discard : _menhir_env -> _menhir_env =
  fun _menhir_env ->
    let lexer = _menhir_env._menhir_lexer in
    let lexbuf = _menhir_env._menhir_lexbuf in
    let _tok = lexer lexbuf in
    {
      _menhir_lexer = lexer;
      _menhir_lexbuf = lexbuf;
      _menhir_token = _tok;
      _menhir_error = false;
    }

and prog : (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Token.macro list option) =
  fun lexer lexbuf ->
    let _menhir_env = let _tok = Obj.magic () in
    {
      _menhir_lexer = lexer;
      _menhir_lexbuf = lexbuf;
      _menhir_token = _tok;
      _menhir_error = false;
    } in
    Obj.magic (let _menhir_stack = () in
    let _menhir_env = _menhir_discard _menhir_env in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | COLON ->
        _menhir_run2 _menhir_env (Obj.magic _menhir_stack) MenhirState0
    | EOF ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_s = MenhirState0 in
        let _menhir_stack = Obj.magic _menhir_stack in
        let _1 = () in
        let _v : (Token.macro list option) =               ( None ) in
        _menhir_goto_prog _menhir_env _menhir_stack _menhir_s _v
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        _menhir_errorcase _menhir_env (Obj.magic _menhir_stack) MenhirState0)
  


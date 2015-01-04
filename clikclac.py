import clacc0
import sys

def main():
    files = []
    nopreamble =  '-nopreamble' in sys.argv
    if nopreamble: sys.argv.remove("-nopreamble")
    
    if len(sys.argv) <= 1 or sys.argv[1] == '-':
        files.append(("stdin", sys.stdin.read()))
    else:
        for fn in sys.argv[1:]:
            with open(fn, 'rt') as f:
                files.append((fn, f.read()))

    print(clacc0.convert(files, nopreamble=nopreamble))

if __name__ == '__main__':
    main()

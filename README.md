# C-COW-Interpreter
An interpreter for the [COW](https://bigzaphod.github.io/COW/) language, written in C.

## How to use
- Put your COW source code in the `sourceCode` variable in the `cow-interpreter.c` script
- `cd` in the project's folder
- `make` or `gcc cow-interpreter.c -o cow-interpreter`
- `make run`

## TODO
- [x] Implement `MOO`
- [x] Implement `moo`
- [ ] Implement STDIN-related commands
- [ ] Allow reading source code from a file
- [ ] Fix 99 bottles
- [ ] Fix Hello World
- [ ] Add links to programs to try
- [ ] Add tests
- [ ] Make sure code follows best practices (`enum`, `const`, `define`, etc.)
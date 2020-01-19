# C-COW-Interpreter
An interpreter for the [COW](https://bigzaphod.github.io/COW/) language, written in C.

- [Language specification](https://bigzaphod.github.io/COW/)
- [Commented "Hello word" example](examples/hello_world_commented.cow)

## How to use

- Compile
    - `cd` in the project's folder
    - `make` or `gcc cow-interpreter.c -o cow-interpreter`
- Run
    - `cd` in the project's folder
    - `./cow-interpreter <file_path>`
        - The argument is the path to a COW source file
        - You can use `./cow-interpreter examples/hello_world_commented.cow`

If you're on Windows you'll need to install at least GCC, which can be obtained as part of [MinGW](https://osdn.net/projects/mingw/releases/) (remember to add `path\to\MinGW\bin` to `PATH`).


## Notes
- The "Hello world" programs you find online may show the wrong character in place of the space between the words. This happens if ASCII 160 is used instead of ASCII 32 for the space character.
- The "Fibonacci" example you find on COW website will result in an infinite loop. Since also the JS interpreter hangs, I think the example is designed that way.

## TODO
- [x] Implement `MOO`
- [x] Implement `moo`
- [ ] Implement STDIN-related commands
- [x] Allow reading source code from a file
- [ ] Fix 99 bottles
- [x] Fix Hello World
- [ ] Simplify comments syntax in the Hello World example
- [ ] Add links to programs to try
- [ ] Add tests
- [ ] Make sure code follows best practices (`enum`, `const`, `define`, etc.)
- [ ] Remove "TODO" comments in the code

## Ideas
- [ ] Create a tool which creates a HTML pag with the instructions with different colors and hovbering the mouse explains what it does
- [ ] Create a tool which allows to visualize what every instruction does (visualize memory)
- [ ] Create a VS Code extension

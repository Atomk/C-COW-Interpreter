# C-COW-Interpreter
An interpreter for the [COW](https://bigzaphod.github.io/COW/) language, written in C.

## How to use

- Compile
    - `cd` in the project's folder
    - `make` or `gcc cow-interpreter.c -o cow-interpreter`
- Run
    - `cd` in the project's folder
    - `./cow-interpreter <file_path>`, the argument is the path to a COW source file
        - You can download the samples and use `./cow-interpreter ./examples/hello_world_commented.cow`

If you're on Windows you'll need to use a Unix terminal (command prompt and Powershell won't work), I use [Git Bash](https://gitforwindows.org/). Both GCC and Make can be obtained as part of [MinGW](https://osdn.net/projects/mingw/releases/).


## Notes
- The "Hello world" programs you find online may show the wrong character in place of the space between the words. This happens if ASCII 160 is used instead of ASCII 32 for the space character.

## TODO
- [x] Implement `MOO`
- [x] Implement `moo`
- [ ] Implement STDIN-related commands
- [x] Allow reading source code from a file
- [ ] Fix 99 bottles
- [x] Fix Hello World
- [ ] Add links to programs to try
- [ ] Add tests
- [ ] Make sure code follows best practices (`enum`, `const`, `define`, etc.)

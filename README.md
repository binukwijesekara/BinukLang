# BinukLang (`.bnk`)

**BinukLang** is a lightweight, Turing-complete interpreted programming language built from scratch in **C**, featuring Sinhala-inspired keywords, an interactive REPL shell, recursive-descent expression parsing (BODMAS), control flow, loops, and built-in I/O & random utilities.

## Architecture

- **Lexer (`src/lexer.c`)**: Tokenizes source code into keywords, identifiers, string/numeric literals, and relational/arithmetic operators while stripping single-line comments (`//`).
- **Recursive Descent Parser (`src/parser.c`)**: Evaluates arithmetic expressions respecting operator precedence (BODMAS) and relational conditions.
- **Execution Engine & Symbol Table (`src/interpreter.c`)**: Manages variable state in memory and executes conditional branching (`nam`/`naththan`) and iterative loops (`thuru`).
- **CLI & REPL (`src/main.c`)**: Supports executing `.bnk` script files as well as an interactive read-eval-print loop (`bnk>>>`).

## Language Syntax

| Feature | BinukLang Keyword | Example |
| :--- | :--- | :--- |
| Variable Declaration | `danna` | `danna x = 10;` |
| Print Output | `penwanna` | `penwanna("Ayubowan!");` |
| User Input | `ganna()` | `danna age = ganna();` |
| Random Number | `ahamben(min, max)` | `danna r = ahamben(1, 100);` |
| If / Else | `nam` / `naththan` | `nam (x > 5) { ... } naththan { ... }` |
| While Loop | `thuru` | `thuru (x <= 10) { x = x + 1; }` |

## Build & Run

Compile all modules using `gcc`:

```bash
gcc main.c lexer.c parser.c interpreter.c -o binuk
./binuk game.bnk

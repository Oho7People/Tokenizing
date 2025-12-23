# Tokenizing & Expression Calculator (C++)

Small C++20 project that tokenizes, parses, and evaluates arithmetic expressions from the command line.

## Capabilities at a Glance
| Category   | Supported items                     |
| ---------- | ----------------------------------- |
| Numbers    | non-negative integers               |
| Operators  | `+`, `-`, `*`, `/`, `%`             |
| Grouping   | parentheses `(` `)`                 |
| Functions  | `min`, `max`, `abs`, `sqr`          |
| UX helpers | descriptive error messages on fail  |

## Repository Layout
Tokenize
├── src/             # concrete implementations
│   ├── tokenize.cpp     # converts source text into tokens
│   ├── parser.cpp       # builds an AST from the token stream
│   ├── calculator.cpp   # exposes CalculateExpression()
│   └── main.cpp         # CLI entry point
└── include/         # headers shared across components

## Build & Run
1. **Prerequisite:** any C++20-capable compiler (clang++ / g++).
2. **Compile:** `g++ -std=c++20 src/*.cpp -Iinclude -o calc`
3. **Execute:** `./calc`

## Example Interaction
Input : min(5, sqr(3))
Output: 5


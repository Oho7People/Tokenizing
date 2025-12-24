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
```text
Tokenize/
├── src/
│   ├── tokenize.cpp     # tokenizer (lexical analysis)
│   ├── parser.cpp       # AST builder
│   ├── calculator.cpp  # CalculateExpression()
│   └── main.cpp         # CLI entry point
└── include/
    └── *.hpp            # public headers

## Build & Run
1. **Prerequisite:** any C++20-capable compiler (clang++ / g++).
2. **Compile:** `g++ -std=c++20 src/*.cpp -Iinclude -o calc`
3. **Execute:** `./calc`

## Examples Interaction
Input : `3     +5`
Output: 8

Input : `abs-18` (or `abs (-18)`)
Output: 18

Input : `abs-5 * sqr5`
Output: 125

Input: `435 + (58-64) * 5`
Output: 405

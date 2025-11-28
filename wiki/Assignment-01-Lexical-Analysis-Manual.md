# Assignment 01: Lexical Analysis (Manual Implementation)

## Overview

This assignment implements a hand-written lexical analyzer using Finite State Automata (FSA). The lexer manually implements state transitions to recognize tokens without using automated tools like Flex.

## Key Concepts

### Finite State Automata (FSA)

A Finite State Automaton is defined as a 5-tuple:
- **Q**: Finite set of states
- **Σ**: Input alphabet
- **δ**: Transition function (Q × Σ → Q)
- **q₀**: Initial state
- **F**: Set of accepting states

### Token Categories

The lexer recognizes the following token types:

| Token Type | Examples | Pattern |
|------------|----------|---------|
| Keywords | `int`, `float`, `if`, `while`, `return` | Reserved words |
| Identifiers | `count`, `myVar`, `_temp` | `[a-zA-Z_][a-zA-Z0-9_]*` |
| Integer Constants | `42`, `0`, `123` | `[0-9]+` |
| Float Constants | `3.14`, `0.5`, `1.0` | `[0-9]+\.[0-9]+` |
| Operators | `+`, `-`, `*`, `/`, `=`, `==` | Various |
| Delimiters | `;`, `,`, `(`, `)`, `{`, `}` | Single characters |

## Implementation Details

### State Machine Design

The lexer uses a state-based approach where each state handles specific character patterns:

```c
typedef enum {
    STATE_START,
    STATE_IDENTIFIER,
    STATE_INTEGER,
    STATE_FLOAT,
    STATE_OPERATOR,
    STATE_COMMENT,
    // ...
} LexerState;
```

### Transition Diagram

```
                  [a-zA-Z_]
    ┌───────────────────────────┐
    │                           ▼
┌───┴───┐  [a-zA-Z0-9_]   ┌─────────────┐
│ START │ ────────────────│ IDENTIFIER  │──→ Accept
└───┬───┘                 └─────────────┘
    │
    │ [0-9]
    ▼
┌─────────────┐   [0-9]   ┌─────────────┐
│   INTEGER   │◄──────────│   INTEGER   │
└─────┬───────┘           └─────────────┘
      │
      │ [.]
      ▼
┌─────────────┐   [0-9]   ┌─────────────┐
│    FLOAT    │◄──────────│    FLOAT    │──→ Accept
└─────────────┘           └─────────────┘
```

## Building and Running

### Build the Lexer

```bash
cd Assignment-01
make -f Makefile_transition
```

### Run with Test Input

```bash
./transition_lexer transition_test.c
```

### Example Output

For input:
```c
int x = 42;
```

Output:
```
Token: KEYWORD (int)
Token: IDENTIFIER (x)
Token: OPERATOR (=)
Token: INTEGER (42)
Token: DELIMITER (;)
```

## Files

| File | Description |
|------|-------------|
| `transition_diagram_lexer.c` | Main lexer implementation |
| `Makefile_transition` | Build configuration |
| `transition_test.c` | Test input file |
| `README_transition.md` | Detailed documentation |
| `v1/THEORY.md` | Theoretical foundations |
| `v1/THEORY.tex` | LaTeX documentation |

## Theory Topics

### Regular Languages

The lexer recognizes regular languages defined by regular expressions:
- **Concatenation**: `ab` matches "a" followed by "b"
- **Alternation**: `a|b` matches "a" or "b"
- **Kleene Star**: `a*` matches zero or more "a"s
- **Positive Closure**: `a+` matches one or more "a"s

### Error Handling

The lexer handles lexical errors including:
- Unrecognized characters
- Malformed numbers (e.g., `12.34.56`)
- Unterminated strings or comments

## Learning Outcomes

After completing this assignment, you will understand:
- ✅ How finite automata recognize tokens
- ✅ Manual implementation of state machines
- ✅ Buffer management in lexical analysis
- ✅ Token classification and recognition

## Related Pages

- [Assignment 02: Lexical Analysis with Flex](Assignment-02-Lexical-Analysis-Flex)
- [Theory Index](Theory-Index)
- [Home](Home)

---

**Next:** [Assignment 02: Lexical Analysis (Flex)](Assignment-02-Lexical-Analysis-Flex)

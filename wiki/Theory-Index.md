# Compiler Design Theory Index

This page provides an index of all theoretical concepts covered across all assignments.

## Compiler Phases Overview

```
┌─────────────────────────────────────────────────────────────┐
│                    COMPILER PHASES                           │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  Source Code                                                 │
│      │                                                       │
│      ▼                                                       │
│  ┌────────────────────┐                                     │
│  │ Lexical Analysis   │  Assignment 01, 02                  │
│  │ (Scanner/Lexer)    │  → Tokens                           │
│  └─────────┬──────────┘                                     │
│            ▼                                                 │
│  ┌────────────────────┐                                     │
│  │ Syntax Analysis    │  Assignment 03                      │
│  │ (Parser)           │  → Parse Tree/AST                   │
│  └─────────┬──────────┘                                     │
│            ▼                                                 │
│  ┌────────────────────┐                                     │
│  │ Semantic Analysis  │  Assignment 04                      │
│  │ (Type Checking)    │  → Annotated AST                    │
│  └─────────┬──────────┘                                     │
│            ▼                                                 │
│  ┌────────────────────┐                                     │
│  │ Intermediate Code  │  Assignment 05                      │
│  │ Generation         │  → Three-Address Code               │
│  └─────────┬──────────┘                                     │
│            ▼                                                 │
│  ┌────────────────────┐                                     │
│  │ Target Code        │  Assignment 06                      │
│  │ Generation         │  → Assembly Code                    │
│  └─────────┬──────────┘                                     │
│            ▼                                                 │
│      Assembly/Machine Code                                   │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

## Theoretical Topics by Category

### 1. Automata Theory

| Topic | Assignment | Description |
|-------|------------|-------------|
| Finite State Automata (FSA) | [01](Assignment-01-Lexical-Analysis-Manual) | State machines for pattern recognition |
| Deterministic FSA (DFA) | [01](Assignment-01-Lexical-Analysis-Manual), [02](Assignment-02-Lexical-Analysis-Flex) | Single transition per input |
| Non-deterministic FSA (NFA) | [02](Assignment-02-Lexical-Analysis-Flex) | Multiple transitions per input |
| ε-NFA | [02](Assignment-02-Lexical-Analysis-Flex) | NFA with epsilon transitions |
| State Minimization | [02](Assignment-02-Lexical-Analysis-Flex) | DFA optimization |

### 2. Regular Languages

| Topic | Assignment | Description |
|-------|------------|-------------|
| Regular Expressions | [01](Assignment-01-Lexical-Analysis-Manual), [02](Assignment-02-Lexical-Analysis-Flex) | Pattern specification |
| Thompson's Construction | [02](Assignment-02-Lexical-Analysis-Flex) | RE → NFA conversion |
| Subset Construction | [02](Assignment-02-Lexical-Analysis-Flex) | NFA → DFA conversion |
| Maximal Munch | [02](Assignment-02-Lexical-Analysis-Flex) | Longest match principle |

### 3. Context-Free Languages

| Topic | Assignment | Description |
|-------|------------|-------------|
| Context-Free Grammars | [03](Assignment-03-Syntax-Analysis) | Syntax specification |
| Derivations | [03](Assignment-03-Syntax-Analysis) | Grammar rewriting |
| Parse Trees | [03](Assignment-03-Syntax-Analysis) | Syntactic structure |
| Ambiguity | [03](Assignment-03-Syntax-Analysis) | Multiple parse trees |

### 4. Parsing Theory

| Topic | Assignment | Description |
|-------|------------|-------------|
| Bottom-Up Parsing | [03](Assignment-03-Syntax-Analysis) | Shift-reduce parsing |
| LALR(1) Algorithm | [03](Assignment-03-Syntax-Analysis) | LR parsing variant |
| Operator Precedence | [03](Assignment-03-Syntax-Analysis) | Expression parsing |
| Error Recovery | [03](Assignment-03-Syntax-Analysis) | Panic mode, phrase-level |

### 5. Semantic Analysis

| Topic | Assignment | Description |
|-------|------------|-------------|
| Symbol Tables | [04](Assignment-04-Type-Checking) | Identifier management |
| Type Systems | [04](Assignment-04-Type-Checking) | Type rules and checking |
| Type Compatibility | [04](Assignment-04-Type-Checking) | Valid type combinations |
| Scope Management | [04](Assignment-04-Type-Checking) | Block scoping |

### 6. Intermediate Representations

| Topic | Assignment | Description |
|-------|------------|-------------|
| Three-Address Code | [05](Assignment-05-ICG) | IR format |
| Quadruples | [05](Assignment-05-ICG) | TAC storage format |
| Temporaries | [05](Assignment-05-ICG) | Intermediate values |
| Syntax-Directed Translation | [05](Assignment-05-ICG) | Code generation during parsing |

### 7. Code Generation

| Topic | Assignment | Description |
|-------|------------|-------------|
| Register Allocation | [06](Assignment-06-TCG) | Register assignment |
| getReg Algorithm | [06](Assignment-06-TCG) | Aho-Sethi-Ullman |
| Register Descriptors | [06](Assignment-06-TCG) | Register tracking |
| Address Descriptors | [06](Assignment-06-TCG) | Variable location tracking |
| Register Spilling | [06](Assignment-06-TCG) | Memory overflow handling |

## Key Algorithms

### Lexical Analysis Algorithms

| Algorithm | Purpose |
|-----------|---------|
| **Thompson's Construction** | Convert RE to NFA |
| **Subset Construction** | Convert NFA to DFA |
| **Hopcroft's Algorithm** | Minimize DFA |
| **Double-Buffer Scheme** | Efficient input handling |

### Parsing Algorithms

| Algorithm | Type | Purpose |
|-----------|------|---------|
| **Recursive Descent** | Top-Down | Simple hand-written parser |
| **LL(1)** | Top-Down | Predictive parsing |
| **LR(0)** | Bottom-Up | Basic LR parsing |
| **SLR(1)** | Bottom-Up | Simple LR |
| **LALR(1)** | Bottom-Up | Look-Ahead LR (YACC/Bison) |
| **LR(1)** | Bottom-Up | Full canonical LR |

### Code Generation Algorithms

| Algorithm | Purpose |
|-----------|---------|
| **Aho-Sethi-Ullman** | Register allocation |
| **Sethi-Ullman Numbering** | Tree evaluation order |
| **Graph Coloring** | Global register allocation |

## Formal Definitions

### Finite Automaton
```
M = (Q, Σ, δ, q₀, F)
  Q  = finite set of states
  Σ  = input alphabet
  δ  = transition function (Q × Σ → Q)
  q₀ = initial state
  F  = set of accepting states
```

### Context-Free Grammar
```
G = (V, Σ, P, S)
  V = finite set of non-terminals
  Σ = finite set of terminals
  P = set of productions (A → α)
  S = start symbol
```

### Three-Address Instruction
```
x = y op z    (binary operation)
x = op y      (unary operation)
x = y         (assignment)
goto L        (unconditional jump)
if x goto L   (conditional jump)
```

## Study Paths

### Beginner Path
1. [Assignment 01](Assignment-01-Lexical-Analysis-Manual) - FSA basics
2. [Assignment 02](Assignment-02-Lexical-Analysis-Flex) - Automated lexing
3. [Assignment 03](Assignment-03-Syntax-Analysis) - Parsing

### Advanced Path
1. [Assignment 04](Assignment-04-Type-Checking) - Type systems
2. [Assignment 05](Assignment-05-ICG) - IR generation
3. [Assignment 06](Assignment-06-TCG) - Code generation

### Complete Pipeline
Follow assignments 01 → 02 → 03 → 04 → 05 → 06 for full understanding.

## References

### Textbooks
1. **Compilers: Principles, Techniques, and Tools** (Dragon Book) - Aho, Lam, Sethi, Ullman
2. **flex & bison** - John Levine
3. **Introduction to Automata Theory** - Hopcroft, Motwani, Ullman

### Original Papers
- Thompson, K. (1968) - "Regular Expression Search Algorithm"
- Knuth, D. (1965) - "On the Translation of Languages from Left to Right"
- DeRemer, F. (1969) - "Practical Translators for LR(k) Languages"

## Related Pages

- [Home](Home)
- [Getting Started](Getting-Started)
- All assignment pages

---

**Back to [Home](Home)**

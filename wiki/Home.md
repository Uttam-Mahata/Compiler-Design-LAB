# Compiler Design Lab - Wiki Documentation

Welcome to the **Compiler Design Lab** wiki! This wiki contains comprehensive documentation for a complete compiler implementation covering all major phases of compiler design.

## 📋 Quick Navigation

| Assignment | Topic | Description |
|------------|-------|-------------|
| [Assignment 01](Assignment-01-Lexical-Analysis-Manual) | Lexical Analysis (Manual) | Hand-written lexer using FSA |
| [Assignment 02](Assignment-02-Lexical-Analysis-Flex) | Lexical Analysis (Flex) | Automated lexer using Flex/Lex |
| [Assignment 03](Assignment-03-Syntax-Analysis) | Syntax Analysis | Parser using YACC/Bison |
| [Assignment 04](Assignment-04-Type-Checking) | Type Checking | Symbol table and semantic analysis |
| [Assignment 05](Assignment-05-ICG) | Intermediate Code | Three-address code generation |
| [Assignment 06](Assignment-06-TCG) | Target Code | Assembly code generation |

## 🎯 Overview

This repository contains a complete implementation of a compiler for a subset of the C programming language, built incrementally through six assignments. Each assignment builds upon the previous one, demonstrating the full compiler pipeline from source code to target machine code.

### Complete Compilation Pipeline

```
┌──────────────┐
│  C Source    │  Input: C language subset
│   Code       │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│  Assignment  │  Lexical Analysis (Lexer)
│     01-02    │  • Token recognition
│              │  • Pattern matching
└──────┬───────┘
       │
       ▼
┌──────────────┐
│  Assignment  │  Syntax Analysis (Parser)
│      03      │  • Grammar checking
│              │  • Parse tree generation
└──────┬───────┘
       │
       ▼
┌──────────────┐
│  Assignment  │  Semantic Analysis
│      04      │  • Type checking
│              │  • Symbol table management
└──────┬───────┘
       │
       ▼
┌──────────────┐
│  Assignment  │  Intermediate Code Generation
│      05      │  • Three-address code
│              │  • Quadruples
└──────┬───────┘
       │
       ▼
┌──────────────┐
│  Assignment  │  Target Code Generation
│      06      │  • Assembly code
│              │  • Register allocation
└──────┬───────┘
       │
       ▼
┌──────────────┐
│   Assembly   │  Output: RISC-like assembly
│     Code     │
└──────────────┘
```

## 🚀 Getting Started

### Prerequisites

- **GCC/Clang:** C compiler (GCC 7.0+ or Clang 5.0+)
- **Flex:** Fast lexical analyzer generator (version 2.5+)
- **Bison/YACC:** Parser generator (Bison 3.0+)
- **Make:** Build automation tool
- **Git:** Version control

### Installation

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential flex bison make git
```

**macOS:**
```bash
brew install flex bison make
```

**Arch Linux:**
```bash
sudo pacman -S base-devel flex bison
```

### Quick Start

```bash
# Clone the repository
git clone https://github.com/Uttam-Mahata/Compiler-Design-LAB.git
cd Compiler-Design-LAB

# Run complete pipeline (Assignment 06)
cd Assignment-06-TCG
make clean && make
./icg_compiler < test_comprehensive.c
./codegen three_address_code.txt
cat assembly_code.asm
```

## 📖 Documentation Guide

### Theoretical Documentation

Each assignment includes detailed theoretical documentation:

- **THEORY.md** - Comprehensive theory and concepts
- **README.md** - Practical usage guide
- **THEORY.tex** - LaTeX documentation with diagrams (where applicable)

### Key Topics Covered

| Topic | Location |
|-------|----------|
| Finite State Automata | [Assignment 01](Assignment-01-Lexical-Analysis-Manual) |
| Regular Expressions | [Assignment 02](Assignment-02-Lexical-Analysis-Flex) |
| Context-Free Grammars | [Assignment 03](Assignment-03-Syntax-Analysis) |
| Symbol Tables | [Assignment 04](Assignment-04-Type-Checking) |
| Three-Address Code | [Assignment 05](Assignment-05-ICG) |
| Register Allocation | [Assignment 06](Assignment-06-TCG) |

## 🛠️ Technologies Used

- **C** - Primary implementation language
- **Flex/Lex** - Lexical analyzer specification
- **YACC/Bison** - Parser specification
- **LaTeX/TikZ** - Documentation and diagrams

## 📚 References

1. **Compilers: Principles, Techniques, and Tools** (Dragon Book) - Aho, Lam, Sethi, Ullman (2006)
2. **flex & bison** - John Levine (2009)
3. **Introduction to Automata Theory, Languages, and Computation** - Hopcroft, Motwani, Ullman (2006)

## 📊 Project Statistics

- **Lines of Code:** 10,000+
- **Documentation:** 83,000+ words
- **Test Files:** 30+ comprehensive test cases
- **Assignments:** 6 complete phases

---

**Author:** [Uttam Mahata](https://github.com/Uttam-Mahata)

**License:** MIT

# Compiler Design Lab

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A comprehensive collection of compiler construction assignments covering all major phases of compiler design, from lexical analysis to target code generation.

## 📋 Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Assignments](#assignments)
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Documentation](#documentation)
- [Technologies Used](#technologies-used)
- [Learning Outcomes](#learning-outcomes)
- [Contributing](#contributing)
- [References](#references)

## 🎯 Overview

This repository contains a complete implementation of a compiler for a subset of the C programming language, built incrementally through six assignments. Each assignment builds upon the previous one, demonstrating the full compiler pipeline from source code to target machine code.

**Complete Compilation Pipeline:**
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

## 📁 Repository Structure

```
Compiler-Design-LAB/
├── Assignment-01/              # Lexical Analysis (Hand-written)
│   ├── v1/                    # Manual FSA implementation
│   ├── lexer                  # Compiled lexer executable
│   └── transition_diagram_lexer.c
│
├── Assignment-02-LA/           # Lexical Analysis (Flex/Lex)
│   ├── v1/                    # Comprehensive Flex lexer
│   └── v2/                    # Alternative implementation
│
├── Assignment-03-SA/           # Syntax Analysis (YACC/Bison)
│   ├── v1/                    # Complete parser with error recovery
│   └── v2/                    # Minimal lexer for parser integration
│
├── Assignment-04-TC/           # Type Checking & Semantic Analysis
│   ├── symbol_table.c/h       # Symbol table implementation
│   └── test_*.c               # Type checking test files
│
├── Assignment-05-ICG/          # Intermediate Code Generation
│   ├── icg.c/h                # ICG module
│   └── three_address_code.txt # Generated intermediate code
│
├── Assignment-06-TCG/          # Target Code Generation
│   ├── codegen.c/h            # Code generator with register allocation
│   └── assembly_code.asm      # Generated assembly code
│
└── docs/                       # Comprehensive documentation
    ├── DOCUMENTATION_GUIDE.md
    └── THEORY_INDEX.md
```

## 📚 Assignments

### Assignment 01: Lexical Analysis (Hand-Written)
**Focus:** Manual implementation of lexical analyzer using finite state automata

**Key Features:**
- Hand-crafted finite state machine
- Complete transition diagram design
- Recognizes identifiers, keywords, operators, and constants
- Buffer management and error handling

**Technologies:** C, Manual FSA implementation

📖 [Detailed README](Assignment-01/README_transition.md)

---

### Assignment 02: Lexical Analysis (Flex/Lex)
**Focus:** Automated lexer generation using Flex/Lex tools

**Key Features:**
- Regular expression patterns for tokens
- Automated NFA/DFA generation
- Maximal munch principle
- Integration with parser

**Technologies:** Flex, Lex, C

📖 [Detailed README](Assignment-02-LA/v1/README.md)

---

### Assignment 03: Syntax Analysis (YACC/Bison)
**Focus:** Parser implementation using parser generators

**Key Features:**
- Context-free grammar for C subset
- LALR(1) parsing algorithm
- Parse tree construction
- Error recovery strategies
- Integration with lexer

**Technologies:** YACC, Bison, C

📖 [Detailed README](Assignment-03-SA/v1/README.md)

---

### Assignment 04: Type Checking & Semantic Analysis
**Focus:** Type checking and semantic validation

**Key Features:**
- Symbol table with scope management
- Type compatibility checking
- Expression type inference
- Assignment validation
- Conditional statement type checking
- Array and pointer type checking
- Memory error detection

**Technologies:** C, YACC, Flex

📖 [Detailed README](Assignment-04-TC/README.md)

---

### Assignment 05: Intermediate Code Generation
**Focus:** Syntax-directed translation to three-address code

**Key Features:**
- Quadruple representation
- Temporary variable management
- Control flow translation (if, while, for)
- Expression evaluation
- Label management
- Backpatching for control flow

**Technologies:** C, YACC, Flex

📖 [Detailed README](Assignment-05-ICG/README.md)

---

### Assignment 06: Target Code Generation
**Focus:** Assembly code generation with register allocation

**Key Features:**
- Register allocation using Aho-Sethi-Ullman algorithm
- RISC-like instruction set (8085/8086 compatible)
- Address and register descriptor management
- Register spilling strategy
- Dead variable elimination
- Optimized register reuse

**Technologies:** C

📖 [Detailed README](Assignment-06-TCG/README.md)

---

## 🚀 Getting Started

### Quick Start Guide

#### 1. Clone the Repository
```bash
git clone https://github.com/Uttam-Mahata/Compiler-Design-LAB.git
cd Compiler-Design-LAB
```

#### 2. Run Complete Pipeline Example

Navigate to Assignment 06 for the complete compilation pipeline:

```bash
cd Assignment-06-TCG

# Compile the ICG compiler and code generator
make clean
make

# Generate three-address code from C source
./icg_compiler < test_comprehensive.c

# Generate assembly code from three-address code
./codegen three_address_code.txt

# View the generated assembly
cat assembly_code.asm
```

#### 3. Try Individual Assignments

**Lexical Analysis (Assignment 01):**
```bash
cd Assignment-01
make -f Makefile_transition
./transition_lexer transition_test.c
```

**Parser (Assignment 03):**
```bash
cd Assignment-03-SA/v1
make
./parser < test_input.c
```

**Type Checking (Assignment 04):**
```bash
cd Assignment-04-TC
make
./symbol_parser < test_type_checking.c
```

**Intermediate Code Generation (Assignment 05):**
```bash
cd Assignment-05-ICG
make
./icg_compiler < test_comprehensive.c
```

## 🔧 Prerequisites

### Required Software

- **GCC/Clang:** C compiler (GCC 7.0+ or Clang 5.0+)
- **Flex:** Fast lexical analyzer generator (version 2.5+)
- **Bison/YACC:** Parser generator (Bison 3.0+)
- **Make:** Build automation tool
- **Git:** Version control

### Optional Software

- **LaTeX:** For compiling documentation (TeX Live 2018+)
- **TikZ:** For viewing state diagrams
- **PDF viewer:** For viewing generated documentation

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

### Verify Installation
```bash
gcc --version
flex --version
bison --version
make --version
```

## 📖 Documentation

Comprehensive theoretical and practical documentation is available:

### Main Documentation Files

- **[Documentation Guide](docs/DOCUMENTATION_GUIDE.md)** - Complete overview of all documentation
- **[Theory Index](docs/THEORY_INDEX.md)** - Index of theoretical concepts covered

### Documentation by Assignment

Each assignment includes:
- **README.md** - Practical usage guide
- **THEORY.md** - Theoretical foundations (where applicable)
- **THEORY.tex** - LaTeX documentation with diagrams (where applicable)
- **Test files** - Example inputs and expected outputs

### Topics Covered

- **Finite State Automata (FSA)** - Manual and automated construction
- **Regular Expressions** - Pattern matching theory
- **Context-Free Grammars (CFG)** - Syntax specification
- **LALR(1) Parsing** - Bottom-up parsing algorithm
- **Symbol Tables** - Scope management and lookups
- **Type Systems** - Type checking and inference
- **Intermediate Representations** - Three-address code
- **Code Generation** - Assembly code generation
- **Register Allocation** - Optimization techniques

### Total Documentation
- **83,000+ words** of documentation
- **16 documentation files**
- **73 topics** covered
- **50+ diagrams** (FSAs, parse trees, etc.)

## 🛠️ Technologies Used

### Programming Languages
- **C** - Primary implementation language
- **Lex/Flex** - Lexical analyzer specification
- **YACC/Bison** - Parser specification
- **LaTeX** - Documentation and diagrams

### Tools & Frameworks
- **Flex 2.6+** - Fast lexical analyzer generator
- **Bison 3.0+** - GNU parser generator (compatible with YACC)
- **GCC/Clang** - C compiler
- **Make** - Build automation
- **TikZ** - LaTeX package for diagrams

### Algorithms Implemented
- **Thompson's Construction** - Regular expression to NFA
- **Subset Construction** - NFA to DFA conversion
- **Hopcroft's Algorithm** - DFA minimization
- **LALR(1) Parsing** - Efficient LR parsing
- **Aho-Sethi-Ullman** - Register allocation

## 🎓 Learning Outcomes

By working through these assignments, you will:

### Theoretical Understanding
- ✅ Understand finite automata and regular languages
- ✅ Master context-free grammars and parsing theory
- ✅ Learn type systems and semantic analysis
- ✅ Understand intermediate representations
- ✅ Master code generation and optimization

### Practical Skills
- ✅ Implement lexical analyzers (manual and automated)
- ✅ Build parsers using parser generators
- ✅ Design and implement symbol tables
- ✅ Perform type checking and semantic validation
- ✅ Generate intermediate code
- ✅ Generate target assembly code
- ✅ Implement register allocation algorithms

### Tool Proficiency
- ✅ Flex/Lex for lexer generation
- ✅ YACC/Bison for parser generation
- ✅ C programming for systems software
- ✅ Make for build automation
- ✅ Git for version control

### Software Engineering
- ✅ Modular design and code organization
- ✅ Error handling and recovery
- ✅ Testing and validation strategies
- ✅ Documentation and specification
- ✅ Incremental development

## 🤝 Contributing

Contributions are welcome! Please follow these guidelines:

### How to Contribute

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/improvement
   ```
3. **Make your changes**
   - Follow existing code style
   - Add tests where applicable
   - Update documentation
4. **Commit your changes**
   ```bash
   git commit -m "Add: description of changes"
   ```
5. **Push to your fork**
   ```bash
   git push origin feature/improvement
   ```
6. **Create a Pull Request**

### Contribution Guidelines

- **Code Style:** Follow existing C coding conventions
- **Documentation:** Update relevant README and documentation files
- **Testing:** Include test files for new features
- **Commits:** Write clear, descriptive commit messages
- **Issues:** Report bugs and suggest features via GitHub Issues

### Areas for Contribution

- 🐛 Bug fixes and error handling improvements
- 📚 Documentation enhancements
- ✨ New test cases and examples
- 🚀 Performance optimizations
- 🎨 Code refactoring for better readability
- 🔧 Build system improvements

## 📚 References

### Textbooks

1. **Compilers: Principles, Techniques, and Tools** (Dragon Book)
   - Authors: Aho, Lam, Sethi, Ullman (2006)
   - The definitive compiler design textbook

2. **flex & bison**
   - Author: John Levine (2009)
   - Practical guide to lexer and parser generators

3. **Introduction to Automata Theory, Languages, and Computation**
   - Authors: Hopcroft, Motwani, Ullman (2006)
   - Theoretical foundations

### Research Papers

- **Thompson, K.** (1968) - "Regular Expression Search Algorithm"
- **DeRemer, F.** (1969) - "Practical Translators for LR(k) Languages"
- **Knuth, D.** (1965) - "On the Translation of Languages from Left to Right"

### Online Resources

- [Flex Manual](https://westes.github.io/flex/manual/)
- [Bison Manual](https://www.gnu.org/software/bison/manual/)
- [Compiler Design Tutorial](https://www.tutorialspoint.com/compiler_design/)

## 📝 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 👨‍💻 Author

**Uttam Mahata**
- GitHub: [@Uttam-Mahata](https://github.com/Uttam-Mahata)

## 🙏 Acknowledgments

- Course instructors and teaching assistants
- Authors of the Dragon Book and reference materials
- Open source community for Flex, Bison, and related tools

---

## 📊 Project Statistics

- **Lines of Code:** 10,000+ (across all assignments)
- **Test Files:** 30+ comprehensive test cases
- **Documentation:** 83,000+ words
- **Assignments:** 6 complete phases
- **Compilation Pipeline:** Full C subset compiler

---

**⭐ If you find this repository helpful, please consider giving it a star!**

For questions, issues, or suggestions, please open an issue on GitHub.

---

*Last Updated: November 2025*

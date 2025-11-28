# Getting Started with Compiler Design Lab

This guide will help you get started with the Compiler Design Lab repository.

## Prerequisites

Before you begin, ensure you have the following software installed:

### Required Software

| Software | Version | Purpose |
|----------|---------|---------|
| **GCC** or **Clang** | GCC 7.0+ / Clang 5.0+ | C compiler |
| **Flex** | 2.5+ | Lexical analyzer generator |
| **Bison** | 3.0+ | Parser generator |
| **Make** | Any recent version | Build automation |
| **Git** | Any recent version | Version control |

### Installation Instructions

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential flex bison make git
```

#### macOS
```bash
brew install flex bison make
```

#### Arch Linux
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

## Repository Setup

### 1. Clone the Repository
```bash
git clone https://github.com/Uttam-Mahata/Compiler-Design-LAB.git
cd Compiler-Design-LAB
```

### 2. Repository Structure
```
Compiler-Design-LAB/
├── Assignment-01/          # Lexical Analysis (Manual)
├── Assignment-02-LA/       # Lexical Analysis (Flex)
├── Assignment-03-SA/       # Syntax Analysis (YACC/Bison)
├── Assignment-04-TC/       # Type Checking
├── Assignment-05-ICG/      # Intermediate Code Generation
├── Assignment-06-TCG/      # Target Code Generation
├── docs/                   # Documentation
├── wiki/                   # Wiki pages
├── LICENSE                 # MIT License
└── README.md               # Main readme
```

## Quick Start Examples

### Example 1: Run the Complete Pipeline (Assignment 06)

This runs the full compiler from C source to assembly:

```bash
cd Assignment-06-TCG

# Clean and build
make clean
make

# Generate intermediate code from C source
./icg_compiler < test_comprehensive.c

# Generate assembly from intermediate code
./codegen three_address_code.txt

# View the generated assembly
cat assembly_code.asm
```

### Example 2: Build and Run Lexer (Assignment 01)

```bash
cd Assignment-01

# Build the transition diagram lexer
make -f Makefile_transition

# Run with test input
./transition_lexer transition_test.c
```

### Example 3: Build and Run Parser (Assignment 03)

```bash
cd Assignment-03-SA/v1

# Build
make clean
make

# Run with test input
./parser < test_input.c
```

### Example 4: Type Checking (Assignment 04)

```bash
cd Assignment-04-TC

# Build
make clean
make

# Run with test file
./symbol_parser < test_type_checking.c
```

## Understanding the Pipeline

The compiler processes source code through these stages:

```
┌──────────────┐
│  C Source    │  Your input program
└──────┬───────┘
       │
       ▼
┌──────────────┐
│   Lexer      │  Breaks into tokens (Assignment 01, 02)
└──────┬───────┘
       │
       ▼
┌──────────────┐
│   Parser     │  Checks syntax (Assignment 03)
└──────┬───────┘
       │
       ▼
┌──────────────┐
│ Type Checker │  Validates types (Assignment 04)
└──────┬───────┘
       │
       ▼
┌──────────────┐
│    ICG       │  Generates TAC (Assignment 05)
└──────┬───────┘
       │
       ▼
┌──────────────┐
│   CodeGen    │  Generates assembly (Assignment 06)
└──────────────┘
```

## Recommended Learning Path

### For Beginners

1. **Start with Assignment 01** - Understand how tokens are recognized manually
2. **Move to Assignment 02** - Learn automated lexer generation with Flex
3. **Continue to Assignment 03** - Understand parsing with YACC/Bison

### For Intermediate Users

1. **Study Assignment 04** - Learn about type systems and symbol tables
2. **Explore Assignment 05** - Understand intermediate representations
3. **Complete Assignment 06** - Learn code generation and register allocation

## Documentation Resources

### Main Documentation
- [docs/DOCUMENTATION_GUIDE.md](https://github.com/Uttam-Mahata/Compiler-Design-LAB/blob/main/docs/DOCUMENTATION_GUIDE.md)
- [docs/THEORY_INDEX.md](https://github.com/Uttam-Mahata/Compiler-Design-LAB/blob/main/docs/THEORY_INDEX.md)

### Assignment-Specific READMEs
Each assignment folder contains:
- `README.md` - Practical usage guide
- `THEORY.md` - Theoretical foundations (where applicable)

## Troubleshooting

### Common Issues

#### 1. Flex/Bison not found
```bash
# Ubuntu/Debian
sudo apt-get install flex bison

# macOS
brew install flex bison
# Note: You may need to add to PATH
export PATH="/usr/local/opt/bison/bin:$PATH"
export PATH="/usr/local/opt/flex/bin:$PATH"
```

#### 2. Build errors
```bash
# Clean and rebuild
make clean
make
```

#### 3. Parser conflicts
YACC/Bison may report shift/reduce conflicts. These are often warnings, not errors. Check the `y.output` file for details.

#### 4. Permission denied
```bash
chmod +x ./lexer
chmod +x ./parser
```

## Next Steps

- Browse the [Wiki Home](Home) for complete documentation
- Check the [Theory Index](Theory-Index) for theoretical concepts
- Explore individual [assignment pages](#wiki-navigation)

## Getting Help

- Open an [issue](https://github.com/Uttam-Mahata/Compiler-Design-LAB/issues) on GitHub
- Check existing documentation in the `docs/` folder
- Review assignment-specific `README.md` files

---

**Back to [Home](Home)**

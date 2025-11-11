#include "codegen.h"
#include <ctype.h>

// Global variables
RegisterDescriptor registers[MAX_REGS];
AddressDescriptor address_desc[MAX_VARS];
Instruction instructions[MAX_QUADS];
int num_instructions = 0;
int num_vars = 0;
FILE *output_file = NULL;

// Memory base address for static allocation
static int memory_base = 1000;

void init_code_generator() {
    init_registers();
    init_address_descriptors();
    num_instructions = 0;
    num_vars = 0;
    
    output_file = fopen("assembly_code.asm", "w");
    if (!output_file) {
        fprintf(stderr, "Error: Cannot open output file\n");
        exit(1);
    }
    
    fprintf(output_file, "; Assembly Code Generated from Three-Address Code\n");
    fprintf(output_file, "; Target Architecture: Intel 8086\n");
    fprintf(output_file, "; Instruction Set: x86 (8086 compatible)\n");
    fprintf(output_file, "; Registers used: AX, BX, CX, DX (16-bit general purpose)\n\n");
    fprintf(output_file, ".MODEL SMALL\n");
    fprintf(output_file, ".STACK 100h\n\n");
    fprintf(output_file, ".DATA\n");
    fprintf(output_file, "    ; Variable declarations will be added here\n\n");
    fprintf(output_file, ".CODE\n");
    fprintf(output_file, "MAIN PROC\n");
    fprintf(output_file, "    MOV AX, @DATA\n");
    fprintf(output_file, "    MOV DS, AX\n\n");
    fprintf(output_file, "    ; Generated code starts here\n");
}


void close_code_generator() {
    // Add program termination
    fprintf(output_file, "\n    ; Program termination\n");
    fprintf(output_file, "    MOV AH, 4Ch      ; DOS exit function\n");
    fprintf(output_file, "    INT 21h          ; Call DOS interrupt\n");
    fprintf(output_file, "MAIN ENDP\n");
    fprintf(output_file, "END MAIN\n");
    
    fclose(output_file);
    printf("\n=== Assembly code generated in 'assembly_code.asm' ===\n");
}




void init_registers() {
    // Using 8086 16-bit registers: AX, BX, CX, DX
    const char *reg_names[] = {"AX", "BX", "CX", "DX"};
    for (int i = 0; i < MAX_REGS; i++) {
        strcpy(registers[i].name, reg_names[i]);
        registers[i].is_free = true;
        registers[i].contains[0] = '\0';
        registers[i].dirty = false;
    }
}


void init_address_descriptors() {
    for (int i = 0; i < MAX_VARS; i++) {
        address_desc[i].var_name[0] = '\0';
        address_desc[i].in_memory = true;
        address_desc[i].reg_num = -1;
        address_desc[i].live = false;
    }
}


bool is_temporary(char *name) {
    return (name && name[0] == 'T' && isdigit(name[1]));
}


bool is_constant(char *name) {
    if (!name || name[0] == '\0') return false;
    
    int i = 0;
    if (name[0] == '-') i = 1;
    
    for (; name[i] != '\0'; i++) {
        if (!isdigit(name[i])) return false;
    }
    return i > 0;
}

int get_address_descriptor(char *var) {
    if (!var || var[0] == '\0') return -1;
    
    for (int i = 0; i < num_vars; i++) {
        if (strcmp(address_desc[i].var_name, var) == 0) {
            return i;
        }
    }
    
    if (num_vars < MAX_VARS) {
        strcpy(address_desc[num_vars].var_name, var);
        address_desc[num_vars].in_memory = true;
        address_desc[num_vars].reg_num = -1;
        address_desc[num_vars].live = true;
        return num_vars++;
    }
    
    return -1;
}


void update_address_descriptor(char *var, int reg_num, bool in_mem) {
    int desc_idx = get_address_descriptor(var);
    if (desc_idx != -1) {
        address_desc[desc_idx].reg_num = reg_num;
        address_desc[desc_idx].in_memory = in_mem;
    }
}


void set_variable_live(char *var, bool live) {
    int desc_idx = get_address_descriptor(var);
    if (desc_idx != -1) {
        address_desc[desc_idx].live = live;
    }
}


bool is_variable_live(char *var) {
    int desc_idx = get_address_descriptor(var);
    if (desc_idx != -1) {
        return address_desc[desc_idx].live;
    }
    return false;
}


int find_register(char *var) {
    if (!var || var[0] == '\0') return -1;
    
    for (int i = 0; i < MAX_REGS; i++) {
        if (!registers[i].is_free && strcmp(registers[i].contains, var) == 0) {
            return i;
        }
    }
    return -1;
}

bool is_register_free(int reg_num) {
    return (reg_num >= 0 && reg_num < MAX_REGS && registers[reg_num].is_free);
}


void mark_register_dirty(int reg_num) {
    if (reg_num >= 0 && reg_num < MAX_REGS) {
        registers[reg_num].dirty = true;
    }
}


void mark_register_clean(int reg_num) {
    if (reg_num >= 0 && reg_num < MAX_REGS) {
        registers[reg_num].dirty = false;
    }
}





void spill_register(int reg_num) {
    if (reg_num < 0 || reg_num >= MAX_REGS) return;
    
    RegisterDescriptor *reg = &registers[reg_num];
    
    // If register contains a value and is dirty, store it
    if (!reg->is_free && reg->dirty && reg->contains[0] != '\0') {
        emit_store(reg->contains, reg_num);
        reg->dirty = false;
        
        // Update address descriptor
        update_address_descriptor(reg->contains, -1, true);
    }
}





void free_register(int reg_num) {
    if (reg_num >= 0 && reg_num < MAX_REGS) {
        spill_register(reg_num);
        registers[reg_num].is_free = true;
        registers[reg_num].contains[0] = '\0';
        registers[reg_num].dirty = false;
    }
}


int get_reg(char *var, char *arg1, char *arg2, int next_use[]) {
    int reg_num = -1;
    
    // If var is already in a register, return that register
    reg_num = find_register(var);
    if (reg_num != -1) {
        return reg_num;
    }
    
    // Find a free register
    for (int i = 0; i < MAX_REGS; i++) {
        if (registers[i].is_free) {
            registers[i].is_free = false;
            strcpy(registers[i].contains, var);
            registers[i].dirty = false;
            update_address_descriptor(var, i, true);
            return i;
        }
    }
    
    
    int best_reg = -1;
    int best_priority = -1;
    
    for (int i = 0; i < MAX_REGS; i++) {
        char *reg_var = registers[i].contains;
        
        // Skip if this register contains arg1 or arg2
        if ((arg1 && strcmp(reg_var, arg1) == 0) ||
            (arg2 && strcmp(reg_var, arg2) == 0)) {
            continue;
        }
        
        int priority = 0;
        
        // Prefer registers with dead variables
        if (!is_variable_live(reg_var)) {
            priority = 1000;
        }
        // Prefer clean registers (not dirty)
        else if (!registers[i].dirty) {
            priority = 100;
        }
        // Prefer registers with temporaries
        else if (is_temporary(reg_var)) {
            priority = 50;
        }
        
        if (priority > best_priority) {
            best_priority = priority;
            best_reg = i;
        }
    }
    
    // If we found a register to spill, spill it
    if (best_reg != -1) {
        spill_register(best_reg);
        registers[best_reg].is_free = false;
        strcpy(registers[best_reg].contains, var);
        registers[best_reg].dirty = false;
        update_address_descriptor(var, best_reg, true);
        return best_reg;
    }
    
    // Fallback: use R0
    spill_register(0);
    registers[0].is_free = false;
    strcpy(registers[0].contains, var);
    registers[0].dirty = false;
    update_address_descriptor(var, 0, true);
    return 0;
}


void emit(char *instruction) {
    fprintf(output_file, "%s\n", instruction);
    printf("%s\n", instruction);
}





void emit_load(int reg_num, char *var) {
    char instr[256];
    
    if (is_constant(var)) {
        // Load immediate constant (8086 syntax)
        sprintf(instr, "    MOV %s, %s        ; Load constant %s", 
                registers[reg_num].name, var, var);
    } else {
        // Load from memory location (8086 syntax with brackets)
        sprintf(instr, "    MOV %s, [%s]      ; Load %s into %s", 
                registers[reg_num].name, var, var, registers[reg_num].name);
    }
    
    emit(instr);
}


void emit_store(char *var, int reg_num) {
    char instr[256];
    // 8086 syntax: MOV destination, source
    sprintf(instr, "    MOV [%s], %s      ; Store %s to %s", 
            var, registers[reg_num].name, registers[reg_num].name, var);
    emit(instr);
}


void emit_arithmetic_op(char *op, int dest_reg, int src1_reg, int src2_reg) {
    char instr[256];
    
    // For 8086, we need to handle arithmetic operations differently
    // 8086 uses two-operand format: OP dest, source
    // Result goes into dest, so we need: dest = dest OP source
    
    // First, move src1 to dest if they're different
    if (dest_reg != src1_reg) {
        sprintf(instr, "    MOV %s, %s        ; Copy operand", 
                registers[dest_reg].name, registers[src1_reg].name);
        emit(instr);
    }
    
    // Then apply the operation
    if (strcmp(op, "+") == 0) {
        sprintf(instr, "    ADD %s, %s        ; %s = %s + %s", 
                registers[dest_reg].name, registers[src2_reg].name,
                registers[dest_reg].name, registers[src1_reg].name, registers[src2_reg].name);
    } else if (strcmp(op, "-") == 0) {
        sprintf(instr, "    SUB %s, %s        ; %s = %s - %s", 
                registers[dest_reg].name, registers[src2_reg].name,
                registers[dest_reg].name, registers[src1_reg].name, registers[src2_reg].name);
    } else if (strcmp(op, "*") == 0) {
        // For MUL in 8086, result goes in AX (or DX:AX for 16-bit)
        // We'll use IMUL which allows: IMUL dest, source
        sprintf(instr, "    IMUL %s, %s       ; %s = %s * %s", 
                registers[dest_reg].name, registers[src2_reg].name,
                registers[dest_reg].name, registers[src1_reg].name, registers[src2_reg].name);
    } else if (strcmp(op, "/") == 0) {
        // DIV is complex in 8086 - requires AX/DX setup
        sprintf(instr, "    ; DIV operation - requires special handling");
        emit(instr);
        sprintf(instr, "    MOV AX, %s", registers[src1_reg].name);
        emit(instr);
        sprintf(instr, "    CWD               ; Sign extend AX to DX:AX");
        emit(instr);
        sprintf(instr, "    IDIV %s           ; AX = DX:AX / operand", registers[src2_reg].name);
        emit(instr);
        if (dest_reg != 0) { // 0 is AX
            sprintf(instr, "    MOV %s, AX        ; Move quotient to result", 
                    registers[dest_reg].name);
        } else {
            return; // Result already in AX
        }
    }
    
    emit(instr);
}


void gen_assignment(char *result, char *arg1) {
    char instr[256];
    
    // Get register for result
    int result_reg = get_reg(result, arg1, NULL, NULL);
    
    // Check if arg1 is already in a register
    int arg1_reg = find_register(arg1);
    
    if (arg1_reg != -1) {
        // arg1 is in a register, do register-to-register copy (8086 syntax)
        if (arg1_reg != result_reg) {
            sprintf(instr, "    MOV %s, %s        ; %s = %s", 
                    registers[result_reg].name, 
                    registers[arg1_reg].name,
                    result, arg1);
            emit(instr);
        }
    } else {
        // Load arg1 from memory or constant
        emit_load(result_reg, arg1);
    }
    
    // Mark result register as containing result and dirty
    strcpy(registers[result_reg].contains, result);
    mark_register_dirty(result_reg);
    update_address_descriptor(result, result_reg, false);
}


void gen_arithmetic(char *op, char *result, char *arg1, char *arg2) {
    int arg1_reg, arg2_reg, result_reg;
    
    // Get or load arg1 into a register
    arg1_reg = find_register(arg1);
    if (arg1_reg == -1) {
        arg1_reg = get_reg(arg1, NULL, NULL, NULL);
        emit_load(arg1_reg, arg1);
        strcpy(registers[arg1_reg].contains, arg1);
    }
    
    // Get or load arg2 into a register
    arg2_reg = find_register(arg2);
    if (arg2_reg == -1) {
        arg2_reg = get_reg(arg2, arg1, NULL, NULL);
        emit_load(arg2_reg, arg2);
        strcpy(registers[arg2_reg].contains, arg2);
    }
    
    // Get register for result
    result_reg = get_reg(result, arg1, arg2, NULL);
    
    // Perform the arithmetic operation
    emit_arithmetic_op(op, result_reg, arg1_reg, arg2_reg);
    
    // Update register and address descriptors
    strcpy(registers[result_reg].contains, result);
    mark_register_dirty(result_reg);
    update_address_descriptor(result, result_reg, false);
}


void gen_unary(char *op, char *result, char *arg1) {
    char instr[256];
    int arg1_reg, result_reg;
    
    // Get or load arg1 into a register
    arg1_reg = find_register(arg1);
    if (arg1_reg == -1) {
        arg1_reg = get_reg(arg1, NULL, NULL, NULL);
        emit_load(arg1_reg, arg1);
        strcpy(registers[arg1_reg].contains, arg1);
    }
    
    // Get register for result
    result_reg = get_reg(result, arg1, NULL, NULL);
    
    // Generate unary operation (8086 syntax)
    if (strcmp(op, "uminus") == 0) {
        // First copy if different registers
        if (result_reg != arg1_reg) {
            sprintf(instr, "    MOV %s, %s        ; Copy operand", 
                    registers[result_reg].name,
                    registers[arg1_reg].name);
            emit(instr);
        }
        // Then negate (8086 NEG is single operand)
        sprintf(instr, "    NEG %s            ; %s = -%s", 
                registers[result_reg].name,
                result, arg1);
        emit(instr);
    }
    
    // Update descriptors
    strcpy(registers[result_reg].contains, result);
    mark_register_dirty(result_reg);
    update_address_descriptor(result, result_reg, false);
}


void gen_label(char *label) {
    char instr[256];
    sprintf(instr, "%s:", label);
    emit(instr);
}


void gen_conditional_jump(char *condition, char *label) {
    char instr[256];
    int cond_reg;
    
    // Get condition into a register
    cond_reg = find_register(condition);
    if (cond_reg == -1) {
        cond_reg = get_reg(condition, NULL, NULL, NULL);
        emit_load(cond_reg, condition);
        strcpy(registers[cond_reg].contains, condition);
    }
    
    // Generate conditional branch (8086 syntax)
    sprintf(instr, "    CMP %s, 0         ; Compare %s with 0", 
            registers[cond_reg].name, condition);
    emit(instr);
    
    sprintf(instr, "    JE %s             ; Jump to %s if equal (false)", 
            label, label);
    emit(instr);
}


void gen_unconditional_jump(char *label) {
    char instr[256];
    // 8086 syntax is the same for JMP
    sprintf(instr, "    JMP %s            ; Unconditional jump to %s", 
            label, label);
    emit(instr);
}


void generate_code(char *op, char *arg1, char *arg2, char *result) {
    fprintf(output_file, "\n; %s %s, %s, %s\n", op, arg1, arg2, result);
    
    if (strcmp(op, "=") == 0) {
        // Assignment
        gen_assignment(result, arg1);
    }
    else if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || 
             strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        // Arithmetic operations
        gen_arithmetic(op, result, arg1, arg2);
    }
    else if (strcmp(op, "uminus") == 0) {
        // Unary minus
        gen_unary(op, result, arg1);
    }
    else if (strcmp(op, "label_begin") == 0 || strcmp(op, "label_end") == 0) {
        // Label
        gen_label(result);
    }
    else if (strcmp(op, "ifFalse") == 0) {
        // Conditional jump
        gen_conditional_jump(arg1, result);
    }
    else if (strcmp(op, "goto") == 0) {
        // Unconditional jump
        gen_unconditional_jump(result);
    }
}


void print_register_state() {
    printf("\n=== Register State ===\n");
    for (int i = 0; i < MAX_REGS; i++) {
        printf("%s: ", registers[i].name);
        if (registers[i].is_free) {
            printf("FREE\n");
        } else {
            printf("Contains: %s, Dirty: %s\n", 
                   registers[i].contains,
                   registers[i].dirty ? "Yes" : "No");
        }
    }
}


void print_address_descriptors() {
    printf("\n=== Address Descriptors ===\n");
    for (int i = 0; i < num_vars; i++) {
        if (address_desc[i].var_name[0] != '\0') {
            printf("%s: ", address_desc[i].var_name);
            if (address_desc[i].reg_num != -1) {
                printf("R%d ", address_desc[i].reg_num);
            }
            if (address_desc[i].in_memory) {
                printf("MEM ");
            }
            printf("Live: %s\n", address_desc[i].live ? "Yes" : "No");
        }
    }
}

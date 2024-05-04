#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Instruction {
    char label[20];
    char instruction[20];
    char rs1[20];
    char rs2[20];
    char rd[20];
    int immediate;
};

int main() {
    struct Instruction instructions[1000];
    int n;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        if (scanf("%s : %s", instructions[i].label, instructions[i].instruction) != 2) {
            return 1;
        }
        if (strcmp(instructions[i].instruction, "addi") == 0) {
            if (scanf(" %s , %s , %x", instructions[i].rd, instructions[i].rs1, &instructions[i].immediate) != 3) {
                return 1;
            }
        }
        else if (strcmp(instructions[i].instruction, "jalr") == 0 || strcmp(instructions[i].instruction, "lb") == 0 ||
                 strcmp(instructions[i].instruction, "lbu") == 0 || strcmp(instructions[i].instruction, "lw") == 0) {
            if (scanf(" %s , %x ( %s )", instructions[i].rd, &instructions[i].immediate, instructions[i].rs1) != 3) {
                return 1;
            }
        }
        else if (strcmp(instructions[i].instruction, "lui") == 0 || strcmp(instructions[i].instruction, "auipc") == 0) {
            if (scanf(" %s , 0x%x", instructions[i].rd, &instructions[i].immediate) != 2) {
                return 1;
            }
        }
        else if (strcmp(instructions[i].instruction, "srai") == 0) {
            if (scanf(" %s , %s , %x", instructions[i].rd, instructions[i].rs1, &instructions[i].immediate) != 3) {
                return 1;
            }
        }
        else {
            if (scanf(" %s , %s , %s", instructions[i].rd, instructions[i].rs1, instructions[i].rs2) != 3) {
                return 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int machine_code = 0;
        if (strcmp(instructions[i].instruction, "addi") == 0) {
            machine_code += ((instructions[i].immediate & 0xfff) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x13; // Set the opcode
        }
        else if (strcmp(instructions[i].instruction, "sll") == 0) {
            machine_code += ((atoi(&instructions[i].rs2[1]) & 0x1f) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x1033;
        }
        else if (strcmp(instructions[i].instruction, "xor") == 0) {
            machine_code += ((atoi(&instructions[i].rs2[1]) & 0x1f) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x4033;
        }
        else if (strcmp(instructions[i].instruction, "or") == 0) {
            machine_code += ((atoi(&instructions[i].rs2[1]) & 0x1f) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x6033;
        }
        else if (strcmp(instructions[i].instruction, "and") == 0) {
            machine_code += ((atoi(&instructions[i].rs2[1]) & 0x1f) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x7033;
        }
        else if (strcmp(instructions[i].instruction, "jalr") == 0) {
            machine_code += ((instructions[i].immediate & 0xfff) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x67;
        }
        else if (strcmp(instructions[i].instruction, "lb") == 0) {
            machine_code += ((instructions[i].immediate & 0xfff) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x03;
        }
        else if (strcmp(instructions[i].instruction, "lbu") == 0) {
            machine_code += ((instructions[i].immediate & 0xfff) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x03;
            machine_code += (0x04 << 12);
        }
        else if (strcmp(instructions[i].instruction, "lw") == 0) {
            machine_code += ((instructions[i].immediate & 0xfff) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x03;
            machine_code += (0x02 << 12);
        }
        else if (strcmp(instructions[i].instruction, "lui") == 0) {
            machine_code += ((instructions[i].immediate & 0xfffff) << 12);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x37;
        }
        else if (strcmp(instructions[i].instruction, "auipc") == 0) {
            machine_code += ((instructions[i].immediate & 0xfffff) << 12);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x17;
        }
        else if (strcmp(instructions[i].instruction, "srai") == 0) {
            machine_code += ((instructions[i].immediate & 0xfff) << 20);
            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x40005013;
        }

        printf("0x%08x\n", machine_code);
    }

    return 0;
}

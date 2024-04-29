#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Instruction {
    char label[20];
    char instruction[20];
    char rs1[20];
    char rd[20];
    int immediate;
};

int main() {
    struct Instruction instructions[1000];
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s : %s %s , %x ( %s )", instructions[i].label, instructions[i].instruction,
              instructions[i].rd, &instructions[i].immediate, instructions[i].rs1);
    }


    for (int i = 0; i < n; i++) {
        int machine_code = 0;

        machine_code += ((instructions[i].immediate & 0xfff) << 20);
        machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);
        machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);


        if (strcmp(instructions[i].instruction, "jalr") == 0) {
            machine_code += 0x67; // Set the opcode
        }
        else if (strcmp(instructions[i].instruction, "lb") == 0) {
            machine_code += 0x03; // Set the opcode
        }
        else if (strcmp(instructions[i].instruction, "lbu") == 0) {
            machine_code += 0x03; // Set the opcode

            machine_code += (0x04 << 12); // Set the function3
        }
        else if (strcmp(instructions[i].instruction, "lw") == 0) {
            machine_code += 0x03; // Set the opcode

            machine_code += (0x02 << 12); // Set the function3
        }

        printf("0x%08x\n", machine_code);
    }

    return 0;
}

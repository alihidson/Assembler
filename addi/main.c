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

        scanf("%s : %s %s , %s , %x", instructions[i].label, instructions[i].instruction,
              instructions[i].rd, instructions[i].rs1,
              &instructions[i].immediate);
    }


    for (int i = 0; i < n; i++) {
        if (strcmp(instructions[i].instruction, "addi") == 0) {
            int machine_code = 0;

            machine_code += ((instructions[i].immediate & 0xfff) << 20);

            machine_code += ((atoi(&instructions[i].rs1[1]) & 0x1f) << 15);

            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);

            machine_code += 0x13; // Set the opcode


            printf("0x%08x\n", machine_code);
        }
    }

    return 0;
}
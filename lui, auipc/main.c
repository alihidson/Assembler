#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Instruction {
    char label[20];
    char instruction[20];
    char rd[20];
    int immediate;
};

int main() {
    struct Instruction instructions[1000];
    int n;
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        scanf("%s : %s %s , 0x%x", instructions[i].label, instructions[i].instruction,
              instructions[i].rd, &instructions[i].immediate);
    }

    for (int i = 0; i < n; i++) {
        int machine_code = 0;

        if (strcmp(instructions[i].instruction, "lui") == 0) {
            machine_code += ((instructions[i].immediate & 0xfffff) << 12);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x37;
        }
        else if (strcmp(instructions[i].instruction, "auipc") == 0) {
            machine_code += ((instructions[i].immediate & 0xfffff) << 12);
            machine_code += ((atoi(&instructions[i].rd[1]) & 0x1f) << 7);
            machine_code += 0x17;
        }

        printf("0x%08x\n", machine_code);
    }

    return 0;
}

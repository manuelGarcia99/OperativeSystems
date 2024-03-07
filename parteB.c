#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INSTR_LENGTH 20 // Tamanho máximo de uma instrução
#define MAX_BUFFER_SIZE 1000 // Tamanho máximo do buffer

// Função que gera uma instrução aleatória
char* generate_instruction(char *instruction, int *n_pass) {
    char *inst = malloc(MAX_INSTR_LENGTH * sizeof(char));
    int n;

    switch(rand() % 5) {
        case 0:
            strcpy(inst, "+");
            break;
        case 1:
            strcpy(inst, "-");
            break;
        case 2:
            strcpy(inst, "i");
            break;
        case 3:
            strcpy(inst, "f");
            break;
        case 4:
            strcpy(inst, "r");
            break;
    }

    if (inst[0] == '+' || inst[0] == '-') {
        n = rand() % 10 + 1;
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
    }
    else if (inst[0] == 'i' || inst[0] == 'f') {
        n = rand() % 10 + 1;
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
    }
    else if (inst[0] == 'r') {
        n = rand() % 10 + 1;
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
    }

    return instruction;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Binary file and message requiered\n");
        return 1;
    }

    FILE* binary_file = fopen(argv[1], "rb");
    if (binary_file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char* string = argv[2];
    int string_len = strlen(string);

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    char instruction[MAX_INSTR_LENGTH];
    int param;
    char buffer[MAX_BUFFER_SIZE];
    int buffer_pos = 0;

    while (buffer_pos < string_len) {
        generate_instruction(instruction, &param);

        if (instruction[0] == '+') {
            fseek(binary_file, param, SEEK_CUR);
        }
        else if (instruction[0] == '-') {
            fseek(binary_file, -param, SEEK_CUR);
        }
        else if (instruction[0] == 'i') {
            fseek(binary_file, param, SEEK_SET);
        }
        else if (instruction[0] == 'f') {
            fseek(binary_file, -param, SEEK_END);
        }
        else if (instruction[0] == 'r') {
            fread(buffer + buffer_pos, 1, param, binary_file);
            buffer_pos += param;
        }

        if (buffer_pos >= MAX_BUFFER_SIZE - string_len) {
            printf("s 0\n");
            memset(buffer, 0, MAX_BUFFER_SIZE);
            buffer_pos = 0;
        }
    }

    printf("r %d\n", string_len);
    fread(buffer + buffer_pos, 1, string_len, binary_file);

    fclose(binary_file);

    return 0;
}
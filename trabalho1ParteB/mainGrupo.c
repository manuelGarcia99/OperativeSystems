#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INSTR_LENGTH 6 // Tamanho máximo de uma instrução
 // Tamanho máximo do buffer

// Função que gera uma instrução aleatória
char* generate_instruction(char *instruction, int *n_pass , int tamDoBuffer, int tamDaStringARevelar ,FILE * position  ,int binaryl, int actualposition, char * stringAProcurar , int *posicaoDaString) {
    char *inst = malloc(MAX_INSTR_LENGTH * sizeof(char));
    int n = 0, sum= 0, choice;
    // printf("Size of string: %d\n",tamDaStringARevelar);
    //printf("Size of buffer: %d\n",tamDoBuffer);
    
    do{
    switch(choice=rand() % 5) {
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

    //printf("%dº Choice\n",choice);   

    if (inst[0] == '+' && binaryl >= actualposition + n) {
        //puts("Debug1");
        if(binaryl - actualposition!=0){
            n= rand() % (binaryl - actualposition) +1;
        }
        else{
            continue;
        }
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
        if(binaryl >= actualposition + n)
        sum = 1;
    }

    else if (inst[0] == '-' && (actualposition-n) >= 1)
    {        
        n= rand() % actualposition + 1 ;
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
        if((actualposition-n) >= 1)
        sum = 1;
    }

    else if (inst[0] == 'i' && binaryl >= n) {
        n= rand() % binaryl +1 ;
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
        if(binaryl >= n)
        sum = 1;
    }
    
    else if (inst[0] == 'f' && n <= binaryl)
    {
        n= rand()  % binaryl +1;
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
        if(n <= binaryl)
        sum = 1;
    }
    else if ((inst[0] == 'r') && (binaryl >= actualposition + n) && (tamDaStringARevelar > tamDoBuffer)) {
        //puts("Debug2");
        if((binaryl - actualposition !=0) && (tamDaStringARevelar -tamDoBuffer != 0)){
            n= rand() % (((binaryl - actualposition)< (tamDaStringARevelar -tamDoBuffer)) ? (binaryl -actualposition) : (tamDaStringARevelar - tamDoBuffer)) +1;
        }
        else{
            continue;
        }
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
        //////se fizermos isto isto é este else if der o objetivo então terminamosé tudo 

        char *sample =malloc( sizeof(char) *  (n+1));
        fread(sample,1,n,position);
        sample[n] = '\0';
        char *comparator = malloc(sizeof(char) * (n+1));
        strncpy(comparator,stringAProcurar,n);  
        comparator[n] = '\0';
        //printf("Sample:%s\n",sample);
        //printf("Comparator:%s\n",comparator);      
        if(n +actualposition <= binaryl && (n<= (tamDaStringARevelar -tamDoBuffer)) && strcmp(comparator , sample) == 0){
        sum = 1;
        *posicaoDaString += n; 
        
        }
        if(strcmp(comparator, sample) != 0){
            fseek(position,-n,SEEK_CUR);
        }
        
        free(sample);
        free(comparator);
        
    }
    } while (sum != 1 );
    if(n!=0)
        printf("%s\n",instruction);
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
    strtok(string, "\n");
    int string_len = strlen(string);
    fseek(binary_file,0l,SEEK_END);
    int binarylength = ftell(binary_file);
    rewind(binary_file);

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    char instruction[MAX_INSTR_LENGTH];
    int param;
    int maxBufferSize = strlen(argv[2]) +1 ;
    char * buffer = malloc(maxBufferSize);
    buffer[maxBufferSize] = '\0';
    int buffer_pos = 0;
    int posicaoNaString =0;

    while (strlen(buffer) < string_len) {
        
        generate_instruction(instruction, &param, strlen(buffer) , strlen(string), binary_file, binarylength, ftell(binary_file), &(string[posicaoNaString]), &posicaoNaString );

        if (instruction[0] == '+' && param != 0) {
            fseek(binary_file, param, SEEK_CUR);
        }
        else if (instruction[0] == '-' && param != 0) {
            fseek(binary_file, -param, SEEK_CUR);
        }
        else if (instruction[0] == 'i' && param != 0) {
            fseek(binary_file, param, SEEK_SET);
        }
        else if (instruction[0] == 'f' && param != 0) {
            fseek(binary_file, -param, SEEK_END);
        }
        else if (instruction[0] == 'r' && param != 0) {
            /*fread(buffer + buffer_pos, 1, param, binary_file);
            buffer_pos += param;*/
            
            char * apender = malloc(sizeof(char) *  (param +1));
            
            fread (apender, 1, param ,binary_file );
            apender[param] = '\0';
            
            strcat(buffer,apender);
            
            free(apender);
        }
        else{continue;}

        if (buffer_pos >= maxBufferSize -1) {
            printf("s 0\n");
            memset(buffer, 0,maxBufferSize);
            buffer_pos = 0;
        }
    }

    free(buffer);
    fclose(binary_file);
    printf("s 0\n");
    //printf("%s\n",buffer);
    return 0;
}
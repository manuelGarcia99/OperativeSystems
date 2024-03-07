#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INSTR_LENGTH 6 // Tamanho máximo de uma instrução

/* Função que gera uma instrução aleatória
   A função tem 9 parâmetros importantes, os dois primeiros são feitos para o retorno da função que detém o "operador" e o "número de movimento". 
   (*n_pass retorna alterando a variável principal), estas duas variáveis com "binaryl" fazem quase todos os casos.
   Assim, a primeira parte da função começa com o "switch" que selecciona aleatoriamente o operador, depois cada caso deve ter uma condição que verifique que após a realização da operação não excedemos o tamanho do ficheiro, 
   pelo que todos os se devem ter o "binaril" em comparação com a posição actual "actualposition"   então o programa guardará toda a informação se passar as condições e voltar ao principal.

   Se o operador escolhido for "r", então realizará a comparação explicada acima, juntamente com uma comparação que verifica que o tamanho da string é maior do que o buffer.
   Depois, sempre que o tamanho da cadeia de caracteres e o tamanho do buffer não forem iguais, e também quando a posição actual estiver no fim do ficheiro, será criado um novo número aleatório que terá um intervalo entre um e 
   o menor de (tamanho do ficheiro - posição actual) e (tamanho da string - tamanho do buffer). -> (1 - o mais pequeno)

   A última parte compara se a variável "sample" (que faz uma leitura de n elementos do ficheiro) e o "comparator" (que faz uma cópia de n elementos da palavra a pesquisar), são iguais, caso sejam, salvá-los-á no buffer, caso contrário voltará ao início.

   Toda a função tem um do- while necessário para repetir todo o algoritmo até encontrar um operador e um número que possa passar os condicionantes.

*/
char* generate_instruction(char *instruction, int *n_pass , int tamDoBuffer, int tamDaStringARevelar ,FILE * position  ,int binaryl, int actualposition, char * stringAProcurar , int *posicaoDaString) {
    
    char *inst = malloc(MAX_INSTR_LENGTH * sizeof(char));
    int n = 0, sum= 0, choice;

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


    if (inst[0] == '+' && binaryl >= actualposition + n) {

        if(binaryl - actualposition!=0){
            n= rand() % (binaryl - actualposition) +1;
        }
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
        sum = 1;
    }

    else if (inst[0] == '-' && (actualposition-n) >= 1)
    {        
        n= rand() % actualposition + 1 ;
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
        sum = 1;
    }

    else if (inst[0] == 'i' && binaryl >= n) {
        n= rand() % binaryl +1 ;
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
        sum = 1;
    }
    
    else if (inst[0] == 'f' && n <= binaryl)
    {
        n= rand()  % binaryl +1;
        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;
        sum = 1;
    }
    else if ((inst[0] == 'r') && (binaryl >= actualposition + n) && (tamDaStringARevelar > tamDoBuffer)) {

        if((binaryl - actualposition !=0) && (tamDaStringARevelar -tamDoBuffer != 0)){
            n= rand() % (((binaryl - actualposition)< (tamDaStringARevelar -tamDoBuffer)) ? (binaryl -actualposition) : (tamDaStringARevelar - tamDoBuffer)) +1;
        }

        sprintf(instruction, "%s %d", inst, n);
        *n_pass = n;

        char *sample =malloc( sizeof(char) *  (n+1));
        fread(sample,1,n,position);
        sample[n] = '\0';
        
        char *comparator = malloc(sizeof(char) * (n+1));
        strncpy(comparator,stringAProcurar,n);  
        comparator[n] = '\0';
    
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

/* 
    A função main tem como objetivo só alocar as variaveis que temos que utilizaremos na função generate_instructions, e ejecutar os operadores e os numeros que esta função retorna 
    No inicio temos comparadores que comprueban si o fichero existe ou si foi possivel abri-lo, depois de alocar a variaveis necesarias comenzamos um ciclo while
    que ejecutara os operadores llamando a funcao generate_instructions e dependiendo do resultado as condicionais fazeram as operacoes,
    o comando "read" tem operacoes especiais que so fazem o guardado no buffer dos caracteres leidos, utilizando primero o read em uma string "apender" para depois copiar toda a informacao no buffer
*/

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
        
        generate_instruction(instruction, &param, strlen(buffer) , string_len, binary_file, binarylength, ftell(binary_file), &(string[posicaoNaString]), &posicaoNaString );

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
            
            char * apender = malloc(sizeof(char) *  (param +1));
            
            fread (buffer, 1, param ,binary_file );
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
    return 0;
}
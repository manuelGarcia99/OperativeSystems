#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include <sys/stat.h>
#include <fcntl.h>


void andvancefromi(FILE *file, int n);
void returnfromf(FILE *file, int n);
void recuar(FILE * enderecoDoFile, int numeroDeBytesARecuar);
void ler(char * buffer, FILE * file ,int numeroDeCaracteresAApender);
void advance(FILE *file, int numberOfCharsToAdvance);

void andvancefromi(FILE *file, int n)
{
    fseek(file, n, SEEK_SET);
    printf("i %d\n",n);
    
}

void returnfromf(FILE *file, int n)
{
    fseek(file, -n, SEEK_END);

    printf("f %d\n",n);
}

void recuar(FILE * enderecoDoFile, int numeroDeBytesARecuar){

    numeroDeBytesARecuar = 0 - numeroDeBytesARecuar;

    fseek( enderecoDoFile, numeroDeBytesARecuar, SEEK_CUR);

    printf("- %d\n",numeroDeBytesARecuar);
}

void  ler(char * buffer, FILE * file ,int numeroDeCaracteresAApender){
    char * apender = malloc(sizeof(char) *  (numeroDeCaracteresAApender +1));
    fread (apender, sizeof(char), numeroDeCaracteresAApender ,file );
    
    apender[numeroDeCaracteresAApender] = '\0';
    strcat(buffer,apender);
    free(apender);

    printf("l %d\n",numeroDeCaracteresAApender);
}

void advance(FILE *file, int numberOfCharsToAdvance)
{
    fseek(file,numberOfCharsToAdvance,SEEK_CUR);

    printf("+ %d\n",numberOfCharsToAdvance);
}



int main(int argc, char *argv[]){
    if(argc != 3){
        return 1;
    }
    FILE* fd = fopen(argv[1],"rb");
    int tamanhoDaString = strlen(argv[2]);
    char aRevelar [tamanhoDaString + 1] ;
    strcpy(aRevelar, argv[2]);
    //Andar aleatoriamente pelo ficheiro e construir a string aRevelar num buffer usando as funções enunciadas em cima e o seu input sempre que 
    //elas forem usadas
    char * buffer = malloc(sizeof(aRevelar));
    
}
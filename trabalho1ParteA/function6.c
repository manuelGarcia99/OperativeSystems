#include"searcher.h"

char * ler(char * buffer, int * file ,int numeroDeCaracteresAApender){
    char apender[101];
    while(numeroDeCaracteresAApender !=0){
        read(*file, apender,1);


        numeroDeCaracteresAApender--;
    }    
    strcat(buffer,apender);

    return buffer;
    
}
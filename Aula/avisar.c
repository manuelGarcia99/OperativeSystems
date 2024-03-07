#include "shell.h"

void avisar(char * mensagem, int tempo){
    while(tempo > 0){
        sleep(1);
        tempo--;
    }
    fprintf(stderr,"aviso %s", mensagem);
}

void * avisoWrapper(void * args){
    aviso_t * ptr = (aviso_t *) args;
    avisar(ptr-> mensagem, ptr-> tempo);
    free(ptr);
    return NULL;
}
#include "shell.h"

void * socpwrapper(void * args){
    copiar_t * ptr = (copiar_t *) args;
    socp(ptr -> fonte, ptr -> destino);
    free(ptr);
    return  NULL;
}
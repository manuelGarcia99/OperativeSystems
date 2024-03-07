#include <stdio.h>
#include "shell.h"

void aviso(char *xmsg, int tempo)
{
    while (tempo >0)
        {
            sleep(1);
            tempo--;
        }
    fprintf(stderr,"Aviso: %s\n", xmsg);
}

void *avisowrapper (void *args)
{
    aviso_t *ptr= (aviso_t *) args;
    aviso(ptr->msg, ptr->tempo);
    free(ptr);
    return NULL;
}

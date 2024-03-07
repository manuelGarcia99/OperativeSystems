#include "shell.h"

//#define BUFFSIZE 128
//iocopy
int socplow(int in, int out){
        
        int n;
        char buf[128];
        
        while ( (n = read(in, buf, 128) ) > 0 )
        {
            //    fprintf(stderr, "\n*** N=%d dados lidos ***\n",n);
                write(out, buf, n);
        }
        if (n < 0)
                perror("Erro de leitura!\n");
        return(0);
}

void* socp(void* args){
        copiar_t* copiarPTR = (copiar_t*)args;
        socplow(copiarPTR->in, copiarPTR->out);
        return NULL;
        
}

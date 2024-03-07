#include <stdio.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>



void ioCopy (int *IN,int* OUT ,char *arg);

void ioCopy (int *IN, int *OUT,char * arg) //no error reporting
{ 
 int n;
 int BUFFSIZE = atoi(arg);
 char *buf = malloc(BUFFSIZE);
 while ( ( n = read (*IN, buf, sizeof(char) *BUFFSIZE )) > 0)
 { 
    if (write (*OUT, buf,n) > n )
        perror("Erro de Yo1escrita!\n");
 
 }
    if (n < 0)
         perror("Erro deYo2 leitura!\n");
}

int main(int argc , char * argv[]){///Usar o create ........
    
    int BUFFSIZE = atoi(argv[3]);
    
    int f =open(argv[1] , O_RDONLY);
    int b =open(argv[2] ,  O_CREAT|O_WRONLY, S_IRWXU|S_IRWXG|S_IRWXO );
    
     if(f<0)
       printf("Error");
    clock_t inicio, fim;
    float tempoUsado;
    inicio=clock();
    ioCopy(&f,&b,argv[3]);
    fim=clock();
    tempoUsado= (float)(fim-inicio)/ (float) CLOCKS_PER_SEC;
    fprintf(stderr,"Cópia feita com BlockSize %i Tempo do CPU %f ",BUFFSIZE, tempoUsado);
    perror(NULL);

    //ver mostrar
    close(f);
    close(b);
    return 0;
}

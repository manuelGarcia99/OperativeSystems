#include <stdio.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define BUFFSIZE 128
void ioCopy (int *IN,int* OUT );

void socp(char *fonte, char *destino) ;


void ioCopy (int *IN, int *OUT) //no error reporting
{ 
 int n;
 char buf[BUFFSIZE];
 while ( ( n = read (*IN, buf, sizeof(char) *BUFFSIZE )) > 0)
 { 
    if (write (*OUT, buf,n) > n )
        perror("Erro de escrita!\n");
 
 }
    if (n < 0)
         perror("Erro de leitura!\n");
}

int socp(char * fonte , char * destino){///Usar o create ........
    char str[BUFFSIZE];
    
    int f =open(fonte , O_RDONLY);
    int b =open(destino , O_TRUNC |O_CREAT|O_WRONLY, S_IRWXU|S_IRWXG|S_IRWXO );
    
    
     if(f<0)
       printf("Error");
    ioCopy(&f,&b);
    printf("\n");

    close(f);
    close(b);
    return 0;
}

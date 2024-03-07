#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PERMS 0666
#define DEBUGGING 1

 int token = -1;

#define TRUE 1

int ** pipetas;
int main (int argc,char * argv[] )
{
    int numDePipetas= atoi(argv[1]), max = atoi(argv[4]), tempoDeEspera= atoi(argv[3]);
    srand(time(NULL));
    float prob= atof(argv[2]);
    int pid   = -1; 
    int ids[numDePipetas];
    char nomes[5][15];
    int len = sizeof(int *) * numDePipetas + sizeof(int) * 2 * numDePipetas;
    pipetas = (int **) malloc(len);
    int * ptr = ( int *) (pipetas+numDePipetas);
    for(int i = 0; i< numDePipetas; i++)
    {
        pipetas[i] = (ptr + 2 * i);
    }
    
    for(int i = 0; i< numDePipetas; i++){
        char * buffer = (char *) malloc(15);
        if(i!=numDePipetas-1){
        sprintf(buffer,"pipe%dto%d",i+1,i+2);}
        else  sprintf(buffer,"pipe%dto%d",numDePipetas,1);
        mkfifo(buffer,PERMS);
        strncpy(nomes[i],buffer,15);
        memset(buffer,0,15);
        free(buffer);
        if(DEBUGGING){ printf("CRIAR PIPE\n");}
    }
    for(int i = 0; i< numDePipetas  ;i ++){
        printf("%d\n",i);
        if(fork() == 0){ // processo filho
        if(DEBUGGING){ printf("CRIAR FILHO\n");}
        ids[i] = getpid();
        //abrir pipes
        
            pipetas[i][0] = open(nomes[i], O_RDONLY);
        
        
            pipetas[i][1] = open(nomes[i+1],O_WRONLY);

        

        while(1){
            printf("%d\n",i);
            read(pipetas[i][0], &token, sizeof(int));
            
            
            
            
            if((int) (prob * 100) >= (rand() % 100 + 1)){
                printf("[p%d] blocked on token (val = %d) PROCESSO = %d\n",i+1,token, getpid());
                sleep(tempoDeEspera);
            }
            
             if(token >= max){
                for(int k=0;k<numDePipetas;k++){
                    
                    close(pipetas[k][1]);
                    unlink(nomes[k]);
                    
                    
                }
                exit(0);
                return 0;                
             }
             if(fcntl(pipetas[i][0],F_GETFD) == -1 && fcntl(pipetas[i][1], F_GETFD) == -1)
             {
                exit(0);
             }
            
            token = token +1;
            if(i != numDePipetas-1)
             write(pipetas[i+1][1], &token, sizeof(int));
             else 
             write(pipetas[0][1], &token, sizeof(int));
            
            


           }
           

        }
        
      
    }


    int fd_write = open("pipe1to2", O_WRONLY);
    token = 0;
    write(fd_write, &token, sizeof(int));
    close(fd_write);
    exit(0);
    return !TRUE;
}


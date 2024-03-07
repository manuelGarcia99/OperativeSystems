#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#define FIFO1 "/tmp/f1"

#define PERMS 0666



int ** ptrParaPipetasEsc;
int ** ptrParaPipetasLei;
int pipe1[2];
int todasAsPipetas;
void sighandler(int);
void stopHandler(int);



int main(int argc,char *argv[])
{
    int numDePipetas= atoi(argv[1]), tempoDeEspera= atoi(argv[3]);
    srand(time(NULL));
    
    todasAsPipetas= numDePipetas;
    float prob= atof(argv[2]);
    int pid= fork();
    if(pid==0){
    
    signal(SIGINT, stopHandler);

            mknod(FIFO1, S_IFIFO | PERMS, 0);
    pipe1[1] = open(FIFO1,1); // 0 leitura
    
    // 1 escrita

   
   // printf("Debug1\n");
    /*int * pipetasDeLeitura = malloc(numeroDePipetas);
    int * pipetasDeEscrita = malloc(numeroDePipetas);
    for(int i = 1; i<= numeroDePipetas; i++)
    {
       pipetasDeLeitura[i] =(int *) malloc(2 * sizeof(int));
       pipetasDeEscrita[i] =(int*)malloc(2 * sizeof(int));
    }*/
    //int pipetasDeLeitura[numeroDePipetas*2 ][2];
    int **pipetasDeEscrita = (int **) malloc (numDePipetas* sizeof(int*));
    for(int i = 0;i < numDePipetas; i++)
        pipetasDeEscrita[i] = (int*) malloc (2*sizeof(int));
    ptrParaPipetasEsc = pipetasDeEscrita;
    for(int i = 0;i<numDePipetas  ;i++){
        
        //char * bufferLei = malloc(15);
        char * bufferEsc = malloc(15);
        //sprintf(bufferLei,"/tmp/f%d",i+7);
         sprintf(bufferEsc,"/tmp/f%d",i+2);
        //printf("%d || %d\n",i,numeroDePipetas);
        //mknod(bufferLei,S_IFIFO | PERMS ,0);//limpar
        mknod(bufferEsc,S_IFIFO | PERMS ,0);
       // printf("%d || %d\n",i,numeroDePipetas);
        
        pipetasDeEscrita[i][1] = open(bufferEsc,1);
        //printf("%d || %d\n",i,numeroDePipetas);
        //memset(bufferLei,0,15);
        memset(bufferEsc,0,15);
        free(bufferEsc);
    }
    int token=0;
    int i=0;
    //printf("Debug1\n");
    while (1){  
        //printf("%d\n",token);
        
        //read(pipe1[0], &x,sizeof(int));
        //read(pipe1[0], &y,sizeof(int));
        //read(pipe1[0] , &numeroDePipetas ,sizeof(int));
        //write(pipe2[1], &numeroDePipetas, sizeof(int));
        //res = x + y;

        //write(pipe2[1],&res, sizeof(int)); 
        if(((int) (prob * 100)) >= (rand() % 100 + 1)){
            //printf("OCORREU, %d\n", i);
            write(pipe1[1],&token,sizeof(int));
            write(pipetasDeEscrita[i][1],&(i),sizeof(int));
            
        }
        if(i== numDePipetas- 1){
            i=0;
        }
        else{
            i++;
        }
        
        token++;
        ///
    }
    }
    else{
        signal(SIGINT, sighandler);


        pipe1[0] = open(FIFO1,0);
    

    
    int **pipetasDeLeitura = (int **) malloc (numDePipetas* sizeof(int*));
    for(int i = 0;i < numDePipetas; i++)
        pipetasDeLeitura[i] = (int*) malloc (2*sizeof(int));
    ptrParaPipetasLei = pipetasDeLeitura;
    //int pipetasDeEscrita[numDePipetas*2][2];
    for(int i = 0;i<numDePipetas   ;i++ ){
        char * bufferLei = malloc(15);
        //char * bufferEsc = malloc(15);
         sprintf(bufferLei,"/tmp/f%d",i+2);
        //sprintf(bufferEsc,"/tmp/f%d",i+6);
        //limpar
        //mudar no server
       // printf("%d || %d\n",i,numDePipetas);
        pipetasDeLeitura[i][0] = open(bufferLei, 0);
        
        //printf("%d || %d\n",i,numDePipetas);
        memset(bufferLei,0,15);
        free(bufferLei);
        //memset(bufferEsc,0,15);
    }
    
    /*while (1)
    {
        
        
        read(pipe2[0], &res, sizeof(int));
        
        printf("%d \n", res);
    }
*/
    int token= 0;
    int change=0;
    int pipeta=0;
    while((read(pipe1[0],&token ,sizeof(int)))!= -1){
        

        if(change != token){

            read(pipetasDeLeitura[token % numDePipetas ][0],&pipeta,sizeof(int));//será?
            printf("[p%d] blocked on token (val = %d)\n",pipeta+1,token);
            sleep(tempoDeEspera );
            change= token;
        }
        
    }
        

    
    }
    return 0;
}

void sighandler(int signum) {/////E aqui que tenho que dar unlink
    for(int i = 0; i<todasAsPipetas ; i++){
            close(ptrParaPipetasLei[i][0]);
        }
    close(pipe1[0]);
    free(ptrParaPipetasLei);
   printf("Terminating...\n");
   exit(1);
}

void stopHandler(int signum){
    wait(NULL);
    for(int i = 0; i<todasAsPipetas ; i++){
            char * buffer = malloc(15);
            sprintf(buffer,"/tmp/f%d",i+2);
            close(ptrParaPipetasEsc[i][1]);
            if (unlink(buffer) == -1)
            {
                perror(NULL);
                puts("erro a fechar pipetas");
            }
            
            memset(buffer,0,15);
            free(buffer);
        }
        
    close(pipe1[1]);
    if(unlink(FIFO1) == -1){
        perror(NULL);
        puts("erro a fechar pipeta token");
    }
    free(ptrParaPipetasEsc);
    exit(1);
}
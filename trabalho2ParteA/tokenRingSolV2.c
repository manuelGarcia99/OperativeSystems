#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define FIFO1 "/tmp/f1"
#define FIFO2 "/tmp/f2"
#define FIFO3 "/tmp/f3"
#define FIFO4 "/tmp/f4"

#define PERMS 0666

int pipe1[2],  pipe2[2], pipe3[2], pipe4[2];
    

int main(int argc,char *argv[])
{
    int  fd[2] = {open("tokenctl.txt",0),open("tokenctl.txt",0)} ;
    int numDePipetas= atoi(argv[1]), tempoDeEspera= atoi(argv[3]);
    srand(time(NULL));
    float prob= atof(argv[2]);
    printf("HI\n");
    int pid= fork();
    if(pid==0){
        pipe1[1] = open(FIFO1,1);
    
    pipe2[1] = open(FIFO2,1);
    pipe3[1] = open(FIFO3,1);
    pipe4[0] = open(FIFO4,0);
        write(pipe1[1], &numDePipetas, sizeof(int));
    
    write(pipe2[1], &tempoDeEspera, sizeof(int));
    write(pipe3[1], &prob, sizeof(float));
    int pipetasDeLeitura[numDePipetas][2];
    //int pipetasDeEscrita[numDePipetas*2][2];

    for(int i = 0;i<numDePipetas   ;i++ ){
        char * bufferLei = malloc(15);
        //char * bufferEsc = malloc(15);
        sprintf(bufferLei,"/tmp/f%d",i+5);
        //sprintf(bufferEsc,"/tmp/f%d",i+6);
        //limpar
        //mudar no server
        printf("%d || %d\n",i,numDePipetas);
        pipetasDeLeitura[i][0] = open(bufferLei, 0);
        //pipetasDeEscrita[i/2][1] = open(bufferEsc,1);
        printf("%d || %d\n",i,numDePipetas);
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
    int * check = (int *) malloc(2 * sizeof(int));
    read(fd[1],&(check[1]),sizeof(int));
    printf("Debug3 %d\n",check[1]);
    while(check[1] !='1'){//cond paragem~
    printf("Debug4  %d\n",check[1]);
    memset(&(check[1]),0,sizeof(int));
    puts("Debug4.0");
        if(check[1] =='1') {break;}
        puts("Debug4.1");
        if(change != token){
            read(pipetasDeLeitura[token % numDePipetas ][0],&pipeta,sizeof(int));//será?
            printf("[p%d] blocked on token (val = %d)\n",pipeta+1,token);
            sleep(tempoDeEspera );
            change= token;
        }
        puts("Debug4.2");
        read(fd[1],&(check[1]),sizeof(int));
        puts("Debug4.3");
        fd[1]=lseek(fd[1],0,SEEK_SET);
        puts("Debug4.4");
        if(fd[1]== -1) printf("Error0\n");
        puts("Debug4.5");
    }
    close(pipe1[1]);
    close(pipe2[1]);
    close(pipe3[1]);
    close(pipe4[0]);
    
    for(int i =0 ; i<numDePipetas; i++){
        close(pipetasDeLeitura[i][0]);
    }
    free(check);
    
    }
    else{
            mknod(FIFO1, S_IFIFO | PERMS, 0);
    mknod(FIFO2, S_IFIFO | PERMS, 0);
    mknod(FIFO3, S_IFIFO | PERMS, 0);
    mknod(FIFO4, S_IFIFO | PERMS, 0);
    pipe1[0] = open(FIFO1,0); // 0 leitura
    pipe2[0] = open(FIFO2,0); // 1 escrita
    
    pipe3[0] = open(FIFO3,0);
    pipe4[1] = open(FIFO4,1);

    read(pipe1[0], &numDePipetas,sizeof(int));
    
    read(pipe2[0],&tempoDeEspera,sizeof(int));
    read(pipe3[0],&prob,sizeof(float));
   printf("Debug1\n");
    /*int * pipetasDeLeitura = malloc(numeroDePipetas);
    int * pipetasDeEscrita = malloc(numeroDePipetas);
    for(int i = 1; i<= numeroDePipetas; i++)
    {
       pipetasDeLeitura[i] =(int *) malloc(2 * sizeof(int));
       pipetasDeEscrita[i] =(int*)malloc(2 * sizeof(int));
    }*/
    //int pipetasDeLeitura[numeroDePipetas*2 ][2];
    int pipetasDeEscrita[numDePipetas ][2];
    for(int i = 0;i<numDePipetas  ;i++){
        
        //char * bufferLei = malloc(15);
        char * bufferEsc = malloc(15);
        //sprintf(bufferLei,"/tmp/f%d",i+7);
        sprintf(bufferEsc,"/tmp/f%d",i+5);
        printf("%d || %d\n",i,numDePipetas);
        //mknod(bufferLei,S_IFIFO | PERMS ,0);//limpar
        mknod(bufferEsc,S_IFIFO | PERMS ,0);
        printf("%d || %d\n",i,numDePipetas);
        //pipetasDeLeitura[i/2][0] = open(bufferLei, 0);
        pipetasDeEscrita[i][1] = open(bufferEsc,1);
        printf("%d || %d\n",i,numDePipetas);
        //memset(bufferLei,0,15);
        memset(bufferEsc,0,15);
        free(bufferEsc);
    }
    int token=0;
    int i=0;
   
    int *check= (int *) malloc(2 * sizeof(int));
    read(fd[0],&(check[0]),sizeof(int));
    printf("Debug2\n");
    while (check[0]!= '1' ){  ///cond paragem
        printf("%d\n",token);
        memset(&(check[0]),0,sizeof(int));
        if(read(fd[0],&(check[0]),sizeof(int))=='1' || check[0]=='1')//quando para
        {
            printf("FIM\n");
            write(pipe4[1],&token,sizeof(int) );
            break;
        } 
        //read(pipe1[0], &x,sizeof(int));
        //read(pipe1[0], &y,sizeof(int));
        //read(pipe1[0] , &numeroDePipetas ,sizeof(int));
        //write(pipe2[1], &numeroDePipetas, sizeof(int));
        //res = x + y;

        //write(pipe2[1],&res, sizeof(int)); 
        if(((int) (prob * 100)) >= (rand() % 100 + 1)){
            printf("OCORREU, %d\n", i);
            write(pipe4[1],&token,sizeof(int));
            write(pipetasDeEscrita[i][1],&(i),sizeof(int));
            
        }
        if(i== numDePipetas- 1){
            i=0;
        }
        else{
            i++;
        }
        
        token++;
        fd[0]= lseek(fd[0],0,SEEK_SET);
        if(fd[0]== -1) printf("Error1\n");
               ///
    }
    printf("Terminou Server\n");
    
    free(check);
    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe3[0]);
    close(pipe4[1]);
    
    for(int i = 0; i<numDePipetas ; i++){
        close(pipetasDeEscrita[i][1]);
    }
    wait(NULL);
    }
    return 0;
}
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include<semaphore.h>
#define N 10


volatile int billDisp = 45522;
volatile int Vendas[10]={0};
volatile int semente;
volatile int numt = 0;
volatile int level[N] = {0};
volatile int turn = 0;

int metodo;

pthread_mutex_t lock;
sem_t sem;

void * fn0(void *argumentos){

    int id = *(int *)argumentos;
    srand(semente + id);

    for (int i = 0; i < 1500; i++)
    {
        int b = 1+rand()%4;
        billDisp -= b;
        Vendas[numt] += b;
    }   

    pthread_exit(NULL);

}

void * fn1(void *argumentos){

    int id = *(int *)argumentos;
    srand(semente + id);

    for (int i = 0; i < 1500; i++)
    {
        pthread_mutex_lock(&lock);
        int b = 1+rand()%4;
        billDisp -= b;
        Vendas[numt] += b;
        pthread_mutex_unlock(&lock);
    }   

    
    pthread_exit(NULL);
}

void * fn2(void *argumentos){
    int id = *(int *)argumentos;
    srand(semente + id);

    for (int i = 0; i < 1500; i++)
    {
        sem_wait(&sem);
        int b = 1+rand()%4;
        billDisp -= b;
        Vendas[numt] += b;
        sem_post(&sem);
    }   

    
    pthread_exit(NULL);
}
/*Funcoes para o algoritmo Peterson*/

void * fn3(void *argumentos){
    int id = *(int *)argumentos;
    int X = 1 - id;
    int b = 1+rand()%4;

    level[id] = 1;
    turn = X;
    srand(semente + id);
    
    while (level[X] && turn == X) {
        continue;
    }

    for (int i = 0; i < 1500; i++)
    {
        
        billDisp -= b;
        Vendas[numt] += b;
        
    }   
    level[id] = 0;
    pthread_exit(NULL);
}

void* funcao(void* args) {
       
    if (metodo == 1) { // pthreadMutex
        fn1((int*)args);
    } else if (metodo == 2) { // semPost
        fn2((int*)args);
    } else if (metodo == 3) { // peterson
        fn3((int*)args);
    }else{
        fn0((int*)args);
    }

    return NULL;
}

int main(int argc, char const *argv[]){

    pthread_t th[N];
    int ids[N] = {0,1};
    int capaicity, totalventas = 0;
    semente = atoi(argv[1]);
    metodo = atoi(argv[2]); //1 = mutex - 2 = semaforo binario - 3 = Peterson
    printf("::: Bilheteira do Estadio de Anfield :::\n");

    pthread_mutex_init(&lock,NULL);
    sem_init(&sem, 0, 1);

    for (int i = 0; i < N; i++)
    {
        pthread_create(&th[i],NULL,funcao, &ids[i]);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(th[i],NULL);
    }

    pthread_mutex_destroy(&lock);
    sem_destroy(&sem);

    for (int i = 0; i < N; i++)
    {
        printf("Numero de ventas (%i): %d \n",i,Vendas[i]);
        totalventas += Vendas[i];
    }
    printf("Total de ventas: %d\n",totalventas);
    
    capaicity = totalventas + billDisp;
    printf("Capacidad calculada %d (45522?)\n",capaicity);
    return 0;
}

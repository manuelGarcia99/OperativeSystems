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

#define __mb__ asm volatile ("mfence":::"memory");
#define NUM_THREADS 10

pthread_mutex_t th;
sem_t s;
int level[NUM_THREADS] = {-1};
int last_to_enter[NUM_THREADS] = {-1};
volatile int bilDisp = 45522;
volatile int vendas[10] = {0};
volatile int flags[NUM_THREADS];
volatile int turn;
volatile int numt=0;
volatile int step[NUM_THREADS];

int semente;

int metodo;

void unlock(int self) {
    flags[self] = 0;
}

void lock(int self){
    flags[self] = 1; __mb__
    turn = 1- self; __mb__
   
    while(flags[1-self] == 1 && turn == 1-self) sched_yield(); 
}

void lock_init(){
    for(int i = 0 ; i< NUM_THREADS ; i++){
        flags[i] = 0;
    }
    turn =0;
}


int exists(int id, int j) {
    int k;
    for (k = 0; k < NUM_THREADS; k++) {
        if (k == id)
            continue;
        if (level[k] >= j)
            return 1;
    }
    return 0;
}

void *funcao4(void *args)
{
    puts("Debug1");   
    
    int id = *(int *)args;
    srand(semente + id);
    int b = 1+rand()%4;
    int j;
    
    srand(semente + id);
    
    while (1) {
         for (j = 0; j < NUM_THREADS - 1; j++) {
            level[id] = j;
            last_to_enter[j] = id;
            while ((last_to_enter[j] == id) && exists(id, j))
                continue;
        }
    }

    for (int i = 0; i < 1500; i++)
    {
        
        bilDisp -= b;
        vendas[numt] += b;
        
    }   
    step[id] = 0;
    pthread_exit(NULL);
    return (NULL   );
}   

void peterson(){
    pthread_t threads[NUM_THREADS];
    int i, ids[NUM_THREADS];
    
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i],NULL,funcao4, &ids[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i],NULL);
    }
    
    int total =0;
    for(i= 0; i<10; i++)
    {
        total += vendas[i];
    }    
    int capacidade = bilDisp + total; 
    
    fprintf(stderr, "Capacidade calculada %d (45522?)\n", capacidade);
}

void *funcao3(void *args)
{
    

    int id = *(int *)args;

    //printf("Thread %d\n", id);
    srand(semente + id);
    int numVendidos_na_Thread=0;
    while(numVendidos_na_Thread<1500){
         int b = 1 + rand() % 4;
         
         if(numVendidos_na_Thread + b > 1500){
            
            b = (1500 ) -(numVendidos_na_Thread );

         }
         
         numVendidos_na_Thread +=b;
         sem_wait(&s);
         bilDisp -= b;
         vendas[id] += b;
         sem_post(&s);
    }   
    
    pthread_exit(NULL);


    return (NULL);
}   


void semaforo(){
    pthread_t threads[NUM_THREADS];
    int i, ids[NUM_THREADS];
    sem_init(&s,0,1);
    for (i = 0; i < NUM_THREADS; i++) ids[i]=i;
    
    for(i=0;i < NUM_THREADS;i++)
         pthread_create(&threads[i], NULL, funcao3, &ids[i]);
    
     for(i=0;i < NUM_THREADS;i++) 
         pthread_join(threads[i],NULL);

    int total =0;
    for(i= 0; i<10; i++)
    {
        total += vendas[i];
    }    
    int capacidade = bilDisp + total; 
    
    fprintf(stderr, "Capacidade calculada %d (45522?)\n", capacidade);
}


void *funcao2(void *args)
{
    

    int id = *(int *)args;

    //printf("Thread %d\n", id);
    srand(semente + id);
    int numVendidos_na_Thread=0;
    while(numVendidos_na_Thread<1500){
         int b = 1 + rand() % 4;
         
         if(numVendidos_na_Thread + b > 1500){
            
            b = (1500 ) -(numVendidos_na_Thread );

         }
         numVendidos_na_Thread +=b;
         pthread_mutex_lock(&th);
         bilDisp -= b;
         vendas[id] += b;
         pthread_mutex_unlock(&th);
    }   
    
    pthread_exit(NULL);


    return (NULL);
}   

void mutex(){
    pthread_t threads[NUM_THREADS];
    int i, ids[NUM_THREADS];
    pthread_mutex_init(&th,NULL);
    for (i = 0; i < NUM_THREADS; i++) ids[i]=i;
    
    for(i=0;i < NUM_THREADS;i++)
         pthread_create(&threads[i], NULL, funcao2, &ids[i]);
    
     for(i=0;i < NUM_THREADS;i++) 
         pthread_join(threads[i],NULL);

    int total =0;
    for(i= 0; i<10; i++)
    {
        total += vendas[i];
    }    
    int capacidade = bilDisp + total; 
    
    fprintf(stderr, "Capacidade calculada %d (45522?)\n", capacidade);
}

void *funcao(void *args)
{
    

    int id = *(int *)args;

    //printf("Thread %d\n", id);
    srand(semente + id);
    int numVendidos_na_Thread=0;
    while(numVendidos_na_Thread<1500){
         int b = 1 + rand() % 4;
         
         if(numVendidos_na_Thread + b > 1500){
            
            b = (1500 ) -(numVendidos_na_Thread );

         }
         numVendidos_na_Thread +=b;
         bilDisp -= b;
         vendas[id] += b;
    }   
    
    pthread_exit(NULL);


    return (NULL);
}   
int main (int argc ,char * argv[])
{
    printf("\nBilheteira do Estádio de Anfield\n");
    semente = atoi(argv[1]);
    metodo = atoi(argv[2]);
    pthread_t threads[NUM_THREADS];
    int i, ids[NUM_THREADS];
    if(1== metodo) mutex();
    else if (2 == metodo) semaforo();
    else if(3 == metodo ) peterson();
   else{
    for (i = 0; i < NUM_THREADS; i++) ids[i]=i;
    
    for(i=0;i < NUM_THREADS;i++)
         pthread_create(&threads[i], NULL, funcao, &ids[i]);
    
     for(i=0;i < NUM_THREADS;i++) 
         pthread_join(threads[i],NULL);

    int total =0;
    for(i= 0; i<10; i++)
    {
        total += vendas[i];
    }    
    int capacidade = bilDisp + total; 
    
    fprintf(stderr, "Capacidade calculada %d (45522?)\n", capacidade);
    }
     return 0 ; 
}


#include <stdio.h>
#include <pthread.h>
pthread_mutex_t th;
volatile int x = 0;
//pthread
volatile char lock =0;
#define N 50
#define K 5000
void *incrementa(void *args)
{
    for (int i = 1; i <= K; i++)
        x++;

    pthread_exit(NULL);
}

void trancar(){
    label:
    char local = 1;
    char tmp = lock;
    lock = local;
    local =tmp;
    if(0 != local){
        goto label;
    }
}

void destrancar(){
    lock = 0;
}

void *incrementa3(void *args)
{

    for (int i = 1; i <= K; i++){
        trancar();
        x += 1;
        destrancar();
    }
    pthread_exit(NULL);
}

void *incrementa2(void *args)
{

    for (int i = 1; i <= K; i++){
        pthread_mutex_lock(&th);
        x += 1;
        pthread_mutex_unlock(&th);
    }
    pthread_exit(NULL);
}

int main()
{
    trancar();
    destrancar();

    pthread_t arrThread[N];

    //pthread_mutex_init
    

    for (int i = 0; i < N; i++)
    {
        pthread_create(&arrThread[i], NULL, incrementa2, NULL);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(arrThread[i], NULL);
    }
    printf("x= %d error= %d\n", x, N * K - x);

    return 0;
}
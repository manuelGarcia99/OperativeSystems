#include<stdio.h>
#include <sys/stat.h>
#define FIFO1 "/tmp/f1"
#define FIFO2 "/tmp/f2"
#define PERMS 0666

int pipe1[2];

void server(){
    int x,y,res;
    read(pipe1[1], &x,sizeof(int));
    read(pipe1[1], &y,sizeof(int));
    res = x + y;

    write(pipe1[0],&res, sizeof(int));

    return;
}

void cliente(){
    
    int x,y, res;

    scanf("%i %i", &x,&y);
    write(pipe1[1], &x, sizeof(int));
    write(pipe1[1], &y, sizeof(int));
    read(pipe1[0], &res, sizeof(int));
    
    printf("%d \n", res);
    
    return; 
}

int main()
{
    int pid;

    pipe(pipe1);
    pid = fork();

    if (0 == pid)
    {
        server();
    }
    else
        cliente();
    
    return 0;
}

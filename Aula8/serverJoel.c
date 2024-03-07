#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO1 "/tmp/f1"
#define FIFO2 "/tmp/f2"
#define PERMS 0666

int pipe1[2],pipe2[2];

void server(){
    int x,y,res;

    mknod(FIFO1, S_IFIFO | PERMS, 0);
    mknod(FIFO2, S_IFIFO | PERMS, 0);

    pipe1[0] = open(FIFO1,0); // 0 leitura
    pipe2[1] = open(FIFO2,1); // 1 escrita

    
    
    while (1){   
        read(pipe1[0], &x,sizeof(int));
        read(pipe1[0], &y,sizeof(int));
    
        res = x + y;

        write(pipe2[1],&res, sizeof(int));
    }

    return;
}

int main()
{
    server();
    return 0;
}

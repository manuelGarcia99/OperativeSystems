#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include<fcntl.h>
#include<stdio.h>
#include <sys/wait.h>
#include<stdio.h>


#define FIFO1 "/tmp/f1"
#define FIFO2 "/tmp/f2"
#define PERMS 0666

main (){
    int pipe1[2], pipe2[2];
    pipe1[1] = open(FIFO1,1);//read 
    pipe2[0] = open(FIFO2, 0);//write

    while(1)
    {
        int x , y ,res;
        scanf("%d %d", &x, &y);
        write(pipe1[1], &x , sizeof(int));///porque pipe1[1] é file descriptor
        write(pipe1[1], &y, sizeof(int));
        read(pipe2[0], &res, sizeof(int));
        printf("%d\n",res);
        
    }
    }

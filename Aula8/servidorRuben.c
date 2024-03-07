#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include<fcntl.h>
#include<stdio.h>
#include <sys/wait.h>

#define FIFO1 "/tmp/f1"
#define FIFO2 "/tmp/f2"
#define PERMS 0666

main(){
int pipe1[2], pipe2[2];

    mknod(FIFO1,S_IFIFO | PERMS,0);
    mknod(FIFO2,S_IFIFO | PERMS , 0);
    pipe(pipe1);
    pipe(pipe2);
        while (1){
            int x, y , res;
            read(pipe1[0], &x, sizeof(int));
            read(pipe1[0], &y, sizeof(int));
            res = x + y;
            write(pipe2[1], &x, sizeof(int));

        }
    
}
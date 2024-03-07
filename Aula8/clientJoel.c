#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define FIFO1 "/tmp/f1"
#define FIFO2 "/tmp/f2"
#define PERMS 0666

int pipe1[2], pipe2[2];


void cliente(){
    
    int x,y, res;

    pipe1[1] = open(FIFO1,1);
    pipe2[0] = open(FIFO2,0);
    while (1)
    {
        scanf("%i %i", &x,&y);
        write(pipe1[1], &x, sizeof(int));
        write(pipe1[1], &y, sizeof(int));
        read(pipe2[0], &res, sizeof(int));
        
        printf("%d \n", res);
    }

    return; 
}

int main()
{

    cliente();
    
    return 0;
}

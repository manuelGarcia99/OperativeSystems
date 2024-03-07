#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

short main(short argc , char * argv[]){
    short v[10];

    short f =open(argv[1] , O_RDONLY);
    if(f<0)
       printf("Error");
    read(f,v,sizeof(short) *10);
    
    for(short i =0;i<10;i++)
        printf("%d",v[i]);
    printf("\n");

    close(f);
    
    return 0;
}
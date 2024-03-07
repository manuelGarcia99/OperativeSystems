#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc , char * argv[]){
    int v[10];

    int f =open(argv[1] , O_RDONLY);
    if(f<0)
       printf("Error");
    read(f,v,sizeof(int) *10);
    
    for(int i =0;i<10;i++)
        printf("%d",v[i]);
    printf("\n");

    close(f);
    
    return 0;
}
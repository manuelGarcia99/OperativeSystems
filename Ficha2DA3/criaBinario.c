#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<errno.h>
int main() {
 srand(45500); //xxxx no aluno
 int vetor[100], inicio=rand(); 
 for ( int i=0; i <100 ; i++ ) vetor[i]=inicio+i;
 int fd = creat ( "ints.bin", (S_IRWXU|S_IRWXG | S_IRWXO));
 write(fd, vetor, 100*sizeof(int) );
}
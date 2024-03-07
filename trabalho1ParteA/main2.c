#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 101

int andvancefromi(int *file, int n)
{
    int offset = lseek(*file, n, SEEK_SET);
    return offset;
}

int returnfromf(int *file, int n)
{
    int offset = lseek(*file, -n, SEEK_END);
    return offset;
}

int recuar(int * endereçoDoFile, int numeroDeBytesARecuar){

    numeroDeBytesARecuar = 0 - numeroDeBytesARecuar;

    int offset=lseek(* endereçoDoFile, numeroDeBytesARecuar, SEEK_CUR);

    return offset;

}

char *  ler(char * buffer, int * file ,int numeroDeCaracteresAApender){
    char * apender = malloc(sizeof(char) *  (numeroDeCaracteresAApender +1));
    int n;
     n = read (*file, apender,sizeof(char)  * numeroDeCaracteresAApender  );
    
    apender[n] = '\0';
    char *ptr = strcat(buffer,apender);
    
    free(apender);

    return ptr;
    
}

void vaciarobuff(char * buffer){
    
    memset(buffer, '\0', BUFFER_SIZE);
    
}


int advance(int *file, int numberOfCharsToAdvance)
{
    int offset = lseek(*file,numberOfCharsToAdvance,SEEK_CUR);
    return offset;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        write(STDOUT_FILENO, "Binary file requiered\n",23 * sizeof(char));
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        write(STDOUT_FILENO, "Error opening file\n",20 * sizeof(char));
        return 1;
    }
    char input[6];
    char * buffer= malloc(BUFFER_SIZE);
    input[0] = '\0';
    char newLine[2] = "\n"; 
    while(strcmp("s 0", input) != 0)
    {
        scanf(" %[^\n]",input);
        char * number; 
        char space[2] = " ";
        number = strtok(input, space);
        number = strtok(NULL, space);
        
        int numBytes = atoi(number); 
        if(input[0] == '+')
        {
            advance(&fd , numBytes);
            
        }
        else if (input[0] == '-')
        {
            recuar(&fd, numBytes);
        }
        else if (input[0] == 'i')
        {
            andvancefromi(&fd, numBytes);
            
        }
        else if (input[0] == 'f')
        {
            returnfromf(&fd, numBytes);//...
        }
        else if (input[0] == 'r')
        {
            
            strcpy(buffer, ler(buffer,&fd,numBytes) ); 
            
        }
        else if (input[0] == 'l' && input[2] == '0')
        {
            vaciarobuff(buffer);
            
        }
        else{
            break;
        }
    }
    
    write(STDOUT_FILENO, buffer,BUFFER_SIZE);
    write(STDOUT_FILENO, newLine,2 *sizeof(char));
    free(buffer);
    
    close(fd);
    
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



void removeChar(char* fonte , char * destino , char a , char b, int blockSize){
    FILE *origem =fopen(fonte,"r");
    FILE *chegada =fopen(destino,"w");
    fseek(origem,0,SEEK_END);
    
    int tamanhoFich = ftell(origem);
    rewind(origem);
    char * buffer = malloc(blockSize + 1) ;
    for(int i=0 ; i<tamanhoFich; i+=blockSize){
        fread(buffer,1,blockSize,origem);
        int j=0 ;
        while(buffer[j]!= '\0' && j<blockSize)
        {
            if(buffer[j] == a){
                buffer[j] = b;
            }
            j++;
        }
        fwrite(buffer,1,(tamanhoFich>i+blockSize) ? blockSize :( tamanhoFich - i),chegada);
        memset(buffer,0,blockSize +1);
    }
    fclose(origem);
    fclose(chegada);
    free(buffer);
}

int main()
{
    removeChar("joel1.txt","joel3.txt",'e', 'm' ,5);
}
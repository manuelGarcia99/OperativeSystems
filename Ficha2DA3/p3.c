#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <unistd.h>

#define FILE_MODE (S_IRUSR | S_IWUSR)
int convert(int number);
int main(){

    char linha[200];

    do
    {
        char s1[3] = "", s2[100] = "";
        int a, b;
        fgets(linha, 200, stdin);
        strtok(linha ,"\n");
        sscanf(linha, "%s %d %d %s", s1, &a, &b, s2);///O S2 em vez de receber  o bin vai receber um ficheiro de output
        if(!strcmp(s1, "NG")){///Precisa sempre do ficheiro de output
            int pid = fork();
            if(pid == 0){
                int vetor[100];
                int file = open ("ints.bin",O_RDONLY);/*int file = open ("ints.bin",O_RDONLY);do{
                check = read(file, array ,100* sizeof(int));
                
                }while(check != 0);*/
                int check;
                if (access(s2, F_OK) == 0) {
                    if (unlink(s2) == -1) {
                        perror("Error deleting file");
                        return 1;
                    }
                }
        
                int output = creat(s2 , FILE_MODE );
                do{
                check = read(file, vetor ,100* sizeof(int));
                
                }while(check != 0);
             for(int i =a ;i <= b ; i++){
                    char elem [10];
                    
                    snprintf(elem,sizeof(elem) ,"%d",convert(vetor[i]));
                    write(output,elem ,sizeof(char) * strlen(elem) );
                    write(output," ", sizeof(" ") -1 );
                }
                printf("\n");
                exit(0);
            }
            printf("%s %d %d %s\n", s1, a, b, s2);
        }
        else if(!strcmp(s1, "NE")){///Para  o NE imprime no stdout
            int pid = fork();
            
            if(pid == 0){

                int vetor[100];
                int file = open ("ints.bin",O_RDONLY);
                
                int check;
                do{
                
                
                 check = read(file, vetor ,100* sizeof(int));
                
                
                }while(check != 0);
                for(int i =a ;i <= b ; i++)
                    printf("%4d ",convert(vetor[i]));
                printf("\n");
                exit(1);
            }
            wait(NULL);
            printf("%s %d %d %s\n", s1, a, b, s2);
        }
        else{
             if(strcmp(linha, "EX 0 0"))
                printf("Protocolo desconhecido\n");
             }
        
    }while ( (strcmp(linha, "EX 0 0")));

    return 0;
}

int convert(int n) {
    int temp , remainder, base =1 , decimal = 0;
   for(temp =n; temp > 0; temp = temp / 10)
    {
        remainder = temp % 10;
        decimal = decimal + remainder * base;
        base = base * 2;
    }

  return decimal;
}
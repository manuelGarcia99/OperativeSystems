// 45500 Manuel Garcia
//we use string.h library for strcmp we also use fclose fgets and fopen the function perror prints to our screen the content of stderr
//Everything else is basic arithmetic and logical operations
#include<stdio.h>
#include<string.h>

void streamCopy ( FILE * entrada, FILE * saida);
void changeTab (char * str, int size);
void inserir(char * str ,int tamanho , int indice, char value);
int main( int argc, char *argv[] ){
 if ( argc==1 ) 
 streamCopy ( stdin, stdout); 
 //else abrir ficheiros – exercício

 int t=0, n=0;
 FILE * ficheiros [argc-1];
 int numDeFicheiros=0;
 int indiceDoArg=1;
 char str[1000];
 
 while(numDeFicheiros< argc-1 && indiceDoArg < argc){
    if(strcmp(argv[indiceDoArg],"-T") != 0 && strcmp(argv[indiceDoArg],"-n")!=0){
        ficheiros[numDeFicheiros++] = fopen(argv[indiceDoArg], "r");
        if (ficheiros[numDeFicheiros] == NULL) {
            printf("Failed to open file %s\n", argv[indiceDoArg]);
            fprintf(stderr,"%s: Fatal Error", argv[indiceDoArg]);
            perror(NULL);
            return 1; // exit program with error code
        }
    }
    else if(strcmp(argv[indiceDoArg],"-T") == 0){
        t=1;
    }
    else{
        n = 1;
    }

    indiceDoArg++;
 }
 int index=0;
 while(index<numDeFicheiros){
    int numeroDaLinha=0;
    while(fgets(str,sizeof(str),ficheiros[index]) != NULL){
        if(t){
            
            changeTab(str,sizeof(str));
        }
        if(n)
            printf("%d: %s",++numeroDaLinha,str);
        else
             printf("%s",str);
    }
 index++;
 }
 for(int i =0 ;i < numDeFicheiros; i++)
 {
    
    fclose(ficheiros[i]);
 }
 
 return 0;
}
//function from professor Paul
void streamCopy ( FILE * entrada, FILE * saida ){
 int ch; 
 while ( (ch=fgetc(entrada)) != EOF ){
 fputc( ch, saida);
 }
}

//this function turns the '\t' special character int '^' character and then it calls the insert function
void changeTab(char * str, int size){
    for(int i=0;i<size;i++){
        if(str[i] == '\t'){
            str[i] ='^';
            inserir(str,size, i+1 ,'I');
        }
    }
}

//this function makes the array bigger and inserts the value character in the passed index
void inserir(char array[], int size, int index, char value) {

    if (index < 0 || index > size) {
        printf("Indice invalido\n");
        return;
    }

    for (int i = size - 1; i >= index; i--) {
        array[i + 1] = array[i];
    }


    array[index] = value;

}

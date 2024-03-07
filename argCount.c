#include <stdio.h>
int main( int argc, char *argv[] ){
 printf("Nome próprio é %s e nº de argumentos %d\n",*argv,argc);
 int i=0;
 while ( *argv != NULL ) 
 printf("%d : %s\n",i++,*argv++);
 return 0;
}
#include"shell.h"

int isjpg ( int fileDescriptor )  //esboço da função
{
	/* ficheiro tem que estar aberto */
   unsigned char b[4];
	int n = read(fileDescriptor,b,4);
   if (n) printf("É um ficheiro \n");
   else printf("Não é um ficheiro");
   //voltar ao início do ficheiro com lseek
	if ( b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0) 
     return 1;
	return 0;
}


#include "shell.h"


char prompt[100];



int main ()// Fazer o ultimo 4.7 da p4;;
{
  int len;
  char linha[1024];/* um comando */
  char *args[64];/* com um maximo de 64 argumentos */

  strcpy (prompt, "SOSHELL: Introduza um comando : prompt>");
  while (1)
  {
    printf ("%s", prompt);
    if (fgets (linha, 1023, stdin) == NULL)
    {
      printf ("\n");
      exit (0);
    }
    len = strlen (linha);
    if (1 == len)
      continue;/* linha é apenas \n */
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';
    int numargs =parse (linha, args);/* particiona a string em argumentos */

    if (!builtin (args, numargs))
      execute (args, numargs);/* executa o comando */
    }
    
  return 0;
}

int builtin (char **args, int numargs)
{
  if (strcmp (args[0], "sair") == 0)
  {
    exit (0);
    return 1;
  }
  if (strncmp (args[0], "42", 2) == 0)
  {
    printf ("42 is the answer to life the universe and everything\n");
    return 1;/* funcionalidade embutida */
  }
  if( 0==strcmp(args[0], "obterinfo") ){ 
    printf("SoShell 2022 versão 1.0\n"); 
    return 1 ; //comando embutido
  } 
  if( strlen(args[0])>4 && 0==strncmp(args[0], "PS1=",4) ){ 
    strcpy(prompt,args[0]+4); 
    return 1 ; //comando embutido
  }  
  if( 0==strcmp(args[0], "quemsoueu") ){ 
    system("id"); 
    return 1 ; //comando embutido
  }

  if (0 == strcmp(args[0], "cd")) {
    int err;
    if (NULL == args[1] || strcmp(args[1], "~") ==0)
     err=chdir( getenv("HOME") ) ;
    else 
      err = chdir( args[1] );
    if (err<0) perror ( args[1]);
      return 1 ; //comando embutido
  }

  if( 0==strcmp(args[0], "socp") ){ 
    socp( args[1], args[2] ); 
    return 1 ; //comando embutido
    }

  if(0== strcmp(args[0], "calc") ) {
    calc(args[1], args[2], args[3]);
    return 1;
  }
 if(0 == strcmp(args[0], "bits") ){

   bits(args[1], args[2], args[3]);
    return 1;
  }

  if(0 == strcmp(args[0],"isjpeg" ))
  {
    int file = open(args[1],O_RDONLY);
    if(isjpg(file))
      printf("JPG\n");
    else
      printf("No JPG\n");

    return 1;
  }

  if((strcmp(args[0],"maior")) == 0 && numargs == 3){
    struct stat s1, s2;
    stat(args[1], &s1);
    stat(args[2],&s2);
    double sz1 = s1.st_size / 1024.0;
    double sz2 = s2.st_size / 1024.0;
    if(s1.st_size > s2.st_size){
        printf("%s é maior %lfkb\n",args[1],sz1);
    } else {
        printf("%s é maior %lfkb\n",args[2],sz2);
    }

    return 1;
  }

  if(strcmp(args[0],"setx") == 0){
    struct stat s1;
    stat(args[1],&s1);
    mode_t t = s1.st_mode;
    t = t|S_IXUSR;
    chmod(args[1],t);
    return 1;
  }
  
  if(strcmp(args[0],"removerl")==0){
    struct stat s1;
    stat(args[1],&s1);
    mode_t t = s1.st_mode;
    t = t&~(S_IROTH | S_IRGRP) ;
    chmod(args[1],t);
    return 1;
  }

  if (strcmp(args[0],"sols") == 0)
  {
     DIR *dp;

      struct dirent *dirp;
      struct stat s1;
 

      if (numargs != 2)
          fprintf(stderr, "Usage: %s Um argumento é necessário\n", args[0]);

 

      if ((dp = opendir(args[1])) == NULL)

           fprintf(stderr, "Can’t open %s\n", args[1]);

 

      while ((dirp = readdir(dp)) != NULL) {
        stat(dirp->d_name,&s1);
       double sz1 = s1.st_size / 1024.0;

        ino_t t1 = s1.st_ino;

        printf("%-30s \t tamanho %6.1lf \t idnode %ld \n", dirp->d_name,sz1,(long) t1);
      }
        

 

      closedir(dp);
      return 1;
  }
  if(strcmp("aviso",args[0])==0 ){
    pthread_t th;
    aviso_t * ptr = (aviso_t *) malloc(sizeof(aviso_t));
    strcpy(ptr -> mensagem, args[1]);
    ptr -> tempo = atoi(args[2]);
    pthread_create(&th,NULL,avisoWrapper,(void *) ptr);

    return 1;
  }
  if(strcmp("socpth", args[0]) ==0 ){
      pthread_t th;
      copiar_t * ptr = (copiar_t *)malloc(sizeof(copiar_t));
      strcpy(ptr->fonte, args[1]);
     strcpy(ptr->destino, args[2]);
     pthread_create(&th, NULL, socpwrapper, (void *)ptr);
     return 1;
  }
  if(strcmp("tipo",args[0]) == 0){
    struct stat file_mode ;
    if(stat(args[1] , &file_mode == -1)){
      perror(NULL);
      return 1;
    }
    if(S_ISREG(file_mode.st_mode)){
      printf("É regular\n");
    }
    if(S_ISDIR(file_mode.st_mode)){
      printf("É diretoria\n");
    }
    printf("É outro tipo de ficheiro\n");
    return 1;
  }

  


  /* IMPORTANTE : 
   Devolver 0 para indicar que não existe comando embutido e que
   será executado usando exec() na função execute.c
  */
  return 0;
}
////ver do makefile
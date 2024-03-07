#include "shell.h"

#define FILE_MODE ( S_IRUSR | S_IWUSR )

//  redirects.c
//  redirects tratamento dos simbolos por ordem inversa:  i) 2>  ii) > OU  >  iii) <

int redirects(int numargs, char *args[])
{
  // i tratar do redirect do 2>  

  if ( numargs <3) return numargs;  //Guard the following section
  if ( strcmp(args[numargs -2] , "2>") ==0)  {
           int fd= creat  ( args[numargs -1], FILE_MODE ) ;
           if (fd<0)  { perror( NULL ) ; exit (1)  ; /*indicar um erro*/ }
          dup2(fd, STDERR_FILENO) ; 
          close(fd);
          args[numargs -2]=NULL ;
          numargs = numargs -2 ;
  }
  if (strcmp (args[numargs -2], "SAIDA")==0 || strcmp(args[numargs -2], ">>") ==0)
  {
    if(strcmp (args[numargs-2], "SAIDA") == 0)
    {
      
      int fd= creat (args[numargs -1 ],  FILE_MODE);
      if(fd < 0) {
        perror(NULL); exit (1) ;
      }
      
      dup2(fd,STDOUT_FILENO);
      close(fd);
        args[numargs - 2]= NULL;
        numargs = numargs -2;
    }
    else
    {
      int fd= open (args[numargs - 1 ],   O_APPEND|O_WRONLY);
      if(fd < 0) {
        perror(NULL); exit (1) ;
      }
      
      dup2(fd,STDOUT_FILENO);
      close(fd);
        args[numargs - 2]= NULL;
        numargs = numargs -2;
    }
  }
  
   if(strcmp (args[numargs-2], "ENTRADA")==0)
    {
            int fd= open (args[numargs-1], FILE_MODE);
            if(fd<0)
        {
            fprintf(stderr, "open error\n");
            exit(1);
        }
        
        dup2(fd,STDIN_FILENO);
        close(fd);
        args[numargs-2]=NULL;
        numargs=numargs-2;
        
    }

  //ii tratar do redirect do >
  //verificar  casos de (>) ou append (>>)
  //tratar do > creat  ou >>  open   O_WRONLY | O_APPEND
  
  // iii tratar do <    open   O_RDONLY

  return  numargs;  //devolver o numero de argumentos a passar para execvp
}

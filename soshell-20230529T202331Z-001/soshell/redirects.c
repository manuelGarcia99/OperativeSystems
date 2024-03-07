#include "shell.h"

int redirects (int numargs, char *args[])
{
   
    if (numargs< 3)
        return numargs;
    
    if(strcmp (args[numargs-2], "2>")==0)
    {
        int fd= creat(args[numargs-1], S_IRUSR|S_IWUSR);
        if(fd<0)
    {
        fprintf(stderr, "creat error\n");
        return (0);
    }
         dup2(fd,STDERR_FILENO);
        close(fd);
        args[numargs-2]=NULL;
        numargs-=2;
    }
    
     if (numargs< 3)
        return numargs;
    
    if(strcmp (args[numargs-2], ">>")==0)
    {
            int fd= open (args[numargs-1], O_WRONLY | O_APPEND);
            if(fd<0)
        {
            fprintf(stderr, "creat/open error\n");
            return (0);
        }
        
        dup2(fd,STDOUT_FILENO);
        close(fd);
        args[numargs-2]=NULL;
        numargs=numargs-2;
        
    }
  
    
   else if(strcmp (args[numargs-2], ">")==0)
    {
            int fd= creat (args[numargs-1], S_IRUSR|S_IWUSR);
            if(fd<0)
        {
            fprintf(stderr, "creat error\n");
            return (0);
        }
        
        dup2(fd,STDOUT_FILENO);
        close(fd);
        args[numargs-2]=NULL;
        numargs=numargs-2;
        
    }
    
    
     if (numargs< 3)
        return numargs;
    
    if(strcmp (args[numargs-2], "<")==0)
    {
            int fd= open (args[numargs-1], S_IRUSR|S_IWUSR);
            if(fd<0)
        {
            fprintf(stderr, "open error\n");
            return (0);
        }
        
        dup2(fd,STDIN_FILENO);
        close(fd);
        args[numargs-2]=NULL;
        numargs=numargs-2;
        
    }
    return 0;
    
}

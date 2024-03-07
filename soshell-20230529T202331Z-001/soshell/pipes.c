#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int containsPipe (int numArgs, char **args)
{
    int index;
    for(index=0; index<numArgs; index++)
    {
        if(args[index][0]=='|')
            return index;
    } 
        return -1;
}




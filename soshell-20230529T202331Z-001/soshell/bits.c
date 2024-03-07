#include "shell.h"

void bits(char *op1, char *op, char *op2)
{
    int opt1=atoi(op1);
    int opt2=atoi(op2);
    if(strcmp(op,"&")==0)
        printf("%d \n", opt1&opt2);
    else if(strcmp(op,"|")==0)
        printf("%d\n", opt1|opt2);
    else if(strcmp(op,"^")==0)
        printf("%d\n", opt1^opt2);
    
    else if (strcmp(op, ">>")==0)
         printf("%d\n", opt1>>opt2);
    
    else if (strcmp(op, "<<")==0)
         printf("%d\n", opt1<<opt2);
    
}

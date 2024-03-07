#include "shell.h"

void calc(char *value1, char *op, char *value2)
{
    float ch1=atof(value1);
    float ch2=atof (value2);
    if (strcmp(op,"+")==0)
        printf("O resultado é: %f \n", ch1+ch2);
    else if (strcmp(op,"-")==0)
        printf("O resultado é: %f \n", ch1-ch2);
    else  if (strcmp(op,"/")==0)
        printf("O resultado é: %f \n", ch1/ch2);
    else if (strcmp(op,"^")==0)
        printf("O resultado é: %f \n",powf(ch1,ch2));
    else if (strcmp(op,"*")==0)
        printf("O resultado é: %f \n", ch1*ch2);
}

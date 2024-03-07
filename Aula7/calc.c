#include"shell.h"

int stringENum(char* value){///melhorar para o caso de ter varios '.'
    if(*value == '\0'){
        return 1;
    }

    return (isdigit(*value) || *value=='.') && stringENum((value+1));
}

void calc(char* value1, char *op, char *value2)
{
    if(strlen(value1) == 0 || strlen(value2) ==0 || !stringENum(value1) || !stringENum(value2) ||strlen(op) != 1 || (*op != '-' && *op != '+' && 
    *op != '*' && *op != '/' && *op != '^'))
    {
        printf("Inputs errados");
    }
    else 
    {
        if(*op == '-')
            printf("%f\n",atof(value1) - atof(value2));
        else if(*op == '+')
            printf("%f\n",atof(value1) + atof(value2));
        else if(*op == '/')
            printf("%f\n",atof(value1) / atof(value2));
        else if(*op == '*')
            printf("%f\n",atof(value1) * atof(value2));
        else if (*op == '^')
            printf("%lf\n", pow((double) atof(value1), (double) atof(value2)));
    }   
}

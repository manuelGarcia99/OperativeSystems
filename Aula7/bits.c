#include"shell.h"

void bits(char* value1, char *op, char *value2)///Fazer condições de error em caso de erro
{
    switch(*op)
    {
        case '&' : printf("%d\n",atoi(value1) & atoi(value2));break;
        case '|' : printf("%d\n",atoi(value1) | atoi(value2));break;
        case '^' : printf("%d\n",atoi(value1) ^ atoi(value2));break;
        default : printf("Errou!\n");
    }
}
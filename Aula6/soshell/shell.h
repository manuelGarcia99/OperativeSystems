#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <wait.h>
#include <math.h>

void parse(char *buf, char **args);

void execute(char **args);

int builtin (char **args);

void calc(char* value1, char *op, char *value2);

void bits(char* value1, char *op, char *value2);

void socp(char * fonte , char * destino);

int isjpg ( int fileDescriptor );

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1

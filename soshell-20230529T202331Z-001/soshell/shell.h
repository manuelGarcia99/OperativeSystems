#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/wait.h>
#include <math.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
/*
#define err_sys(STR) fprintf(stderr, STR)
#define err_sys2(STR, XXX) fprintf(stderr, STR, XXX)
#define err_dump(XXX) fprintf(stderr, XXX)*/
#include <sys/stat.h>
#include <sys/errno.h>

//#define MKEY1 0x11
#define PERMS 0666
#define limitMsg 150

typedef struct
{
    long int msgType;
    char msgText[limitMsg];
    int msgLength;
} msg;

typedef struct
{
    char msg[100];
    int tempo;
} aviso_t;

typedef struct
{
    int in;
    int out;
} copiar_t;

int parse(char *buf, char **args);

void execute(char **args, int noArgs);

int builtin(char **args, int noArgs);

int socplow(int in, int out);

void *socp(void *args);

void calc(char *value1, char *op, char *value2);

void bits(char *op1, char *op, char *op2);

int isjpg(int fileDescriptor);

int redirects(int numargs, char *args[]);

int containsPipe(int numArgs, char **args);

int ultimo(char **args, int *noArgs);

void aviso(char *xmsg, int tempo);

void *avisowrapper(void *args);

void sendMessage(msg *mesgptr, int id);

int receiveMessage(msg *mesgptr, int id);

int server(int getId);

int client(char *inputId, char *msg);

void *startServidor();

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1

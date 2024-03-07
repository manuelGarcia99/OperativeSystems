#include "shell.h"
#define MYFLAGS S_IRUSR | S_IWUSR

msg menssagem;

int server(int getId)
{
    int n;
    menssagem.msgType = 1;
    n = receiveMessage(&menssagem, getId);

    if (n <= 0)
    {
        perror("erro no server");
    }
    else
    {

        menssagem.msgLength = n;
        menssagem.msgText[n] = '\0';

        fprintf(stdout, "\nThere's a new message!!!\n");
        fprintf(stdout, "%s\n", menssagem.msgText);
    }

    return 0;
}

int client(char *inputId, char *msg)
{
    int id;
    id = msgget(atoi(inputId), PERMS | IPC_CREAT);
    if (id < 0)
    {
        perror("erro no cliente");
    }

    strcpy(menssagem.msgText, msg);
    menssagem.msgLength = strlen(menssagem.msgText);
    sendMessage(&menssagem, id);

    return 1;
}

void *startServidor()
{
    int getId;
    int uid;
    uid = getuid();
    getId = msgget(uid, PERMS | IPC_CREAT);
    if (getId < 0)
    {
        perror("erro no startServidor");
    }

    while (1)
    {
        server(getId);
    }

    return 0;
}

void sendMessage(msg *ptr, int id)
{
    if (msgsnd(id, (char *)&(ptr->msgType), ptr->msgLength, 0) != 0)
        perror("erro no sendMessage");
}

int receiveMessage(msg *ptr, int id)
{
    int n;

    n = msgrcv(id, (char *)&(ptr->msgType), limitMsg, ptr->msgType, 0);
    ptr->msgLength = n;
    if (ptr->msgLength < 0)
        perror("erro no receiveMessage");

    return n;
}

char prompt[100];

int main()
{
    int len;
    char buf[1024]; /* um comando */
    char *args[64]; /* com um maximo de 64 argumentos */

    pthread_t threadServer;
    pthread_create(&threadServer, NULL, startServidor, NULL);

    strcpy(prompt, "SOSHELL: Introduza um comando : prompt>");

    while (1)
    {

        printf("%s", prompt);

        if (fgets(buf, 1023, stdin) == NULL)
        {
            printf("\n");
            exit(0);
        }
        len = strlen(buf);
        if (1 == len)
            continue;
        if (buf[len - 1] == '\n')
            buf[len - 1] = '\0';

        int noArgs = parse(buf, args);

        if (!builtin(args, noArgs))
            execute(args, noArgs); /* executa o comando */
    }
    return 0;
}

int builtin(char **args, int noArgs)
{
    if (strcmp(args[0], "sair") == 0 || strcmp(args[0], "exit") == 0)
    {
        exit(0);
        return 1;
    }

    if (strncmp(args[0], "42", 2) == 0)
    {
        printf("42 is the answer of the universe & everything!\n");
        return 1;
    }

    if (strcmp(args[0], "quemsoueu") == 0 || strcmp(args[0], "whoami") == 0)
    {
        system("id");
        return 1;
    }

    if (strcmp(args[0], "obterinfo") == 0)
    {
        printf("SoShell 2021 versão 7.0\n");
        return 1; // comando embutido
    }

    if (strncmp(args[0], "PS1=", 4) == 0)
    {
        strcpy(prompt, args[0] + 4);
        return 1;
    }

    if (strcmp(args[0], "socp") == 0)
    {
        if (noArgs != 3)
        {
            printf("Socp Fonte Destino \n");
            return 1;
        }

        int fdin = open(args[1], O_RDONLY);
        int fdout = creat(args[2], MYFLAGS);
        socplow(fdin, fdout);
        return 1;
    }

    if (0 == strcmp(args[0], "cd"))
    {
        int err;
        if (args[1] == NULL || strcmp(args[1], "~") == 0)
            err = chdir(getenv("HOME"));
        else
        {
            err = chdir(args[1]);
        }
        if (err < 0)
            perror("chdir failed");
        return 1;
    }

    if (0 == strcmp(args[0], "calc") && noArgs == 4)
    {
        calc(args[1], args[2], args[3]);
        return 1;
    }

    if (0 == strcmp(args[0], "bits") && noArgs == 4)
    {
        bits(args[1], args[2], args[3]);
        return 1;
    }

    if (0 == strcmp(args[0], "isjpg"))
    {
        if (isjpg(open(args[1], O_RDONLY)) == 1)
            printf("E um JPG\n");
        else
            printf("Nao e um JPG\n");

        return 1;
    }

    if (strcmp(args[0], "avisoTeste") == 0)
    {
        aviso(args[1], atoi(args[2]));
        return 1;
    }

    if (strcmp(args[0], "aviso") == 0)
    {
        pthread_t th;
        aviso_t *ptr = (aviso_t *)malloc(sizeof(aviso_t));
        strcpy(ptr->msg, args[1]);
        ptr->tempo = atoi(args[2]);
        pthread_create(&th, NULL, avisowrapper, (void *)ptr);
        return 1;
    }

    if (strcmp(args[0], "socpth") == 0)
    {
        if (noArgs < 3)
            return 1;
        pthread_t th;
        copiar_t *ptr = (copiar_t *)malloc(sizeof(copiar_t));
        int fdin = open(args[1], O_RDONLY);
        int fdout = creat(args[2], MYFLAGS);
        ptr->in = fdin;
        ptr->out = fdout;
        if (ptr->out < 0)
            return 1;
        pthread_create(&th, NULL, socp, (void *)ptr);

        return 1;
    }

    if (strcmp(args[0], "message") == 0)
    {
        client(args[1], args[2]); // args[1] -> id ; args[2] -> msg
        return 1;
    }

    //devolver 0 indique que não há comnando embutido

    return 0;
}

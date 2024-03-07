#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// #include <io.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct
{
	int             idAtm;
	int             idCliente;
	float           valor;
}               reg;

int  main(int argc, char *argv[])
{
	reg             v;
	int             i, j;
	int             fddados = creat("in.bin", S_IRUSR | S_IWUSR);
        const int ATM=10;
        const int CLI=20;

	for (j = 0; j < CLI; j++)
		for (i = 0; i < ATM; i++)
		{
			v.idAtm = i;
			v.idCliente = j;
			v.valor = rand() % 10 - 5;
			write(fddados, &v, sizeof(v));
		}
	for (i = 0; i < 200; i++)
	{
		v.idAtm = rand() % ATM;
		v.idCliente = rand() % CLI;
		v.valor = rand() % 10 - 5;
		write(fddados, &v, sizeof(v));
	}
return 0;
}

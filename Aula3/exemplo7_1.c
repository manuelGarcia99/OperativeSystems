#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
 int fd, i, vec[10];
 for (i=0;i <10; i++) 
 vec[i]=i+512;
 fd = creat("test.bin", S_IRUSR| S_IWUSR ) ;//O create devolve o descritor de ficheiro com o valor 3 porque o user pode ler e criar 1 +2
 write(fd, vec , sizeof(int)*10);
 return (0);
}
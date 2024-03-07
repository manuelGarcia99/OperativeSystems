#include"searcher.h"

/*Esta função retorna o offset que é a posição do apontador no ficheiro isso é tudo mais tarde envio a função 6*/

int advance(int *file, int numberOfCharsToAdvance)
{
    int offset = lseek(*file,SEEK_CUR,numberOfCharsToAdvance);
    return offset;
}

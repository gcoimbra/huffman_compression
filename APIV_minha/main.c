#include <stdio.h>
#include <stdlib.h>

#include "ArvoreBinaria.h"

int main()
{
    Stringzao table;
    stringzaoCria(&table);
    stringzaoGera(&table);

    No *raiz;
    treeCria(&raiz);
    stringzaoShow(&table);
    treeAlimenta(&raiz,&table,1);

    return EXIT_SUCCESS;
}
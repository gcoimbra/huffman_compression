#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include "Stringzao.h"

#define DEBUG

#define MAX_PAIS_SOLTOS 100


typedef struct No No;
typedef struct No
{
    union
    {
        struct Interno
        {
            No *direito, *esquerdo;
        } Interno;
        struct Externo
        {
            char palavra[MAX_PALAVRA];
        } Externo;
    } B;
    size_t soma;

    int is_internal;

} No;

void treeCria(No **raiz);

void treeAlimenta(No **raiz, Stringzao *table, size_t soma_alvo);
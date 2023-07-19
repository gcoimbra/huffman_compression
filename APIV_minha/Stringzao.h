#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define MAX_PALAVRA 50
#define MAX_PALAVRAS 1000
#define DEBUG

#define PATH_ARQUIVO "teste.txt"


typedef struct StringzaoItem
{
    char palavra[MAX_PALAVRA];
    int is_internal;
    size_t frequency;
} StringzaoItem;

typedef struct Stringzao
{
    StringzaoItem item[MAX_PALAVRAS];
    size_t size;
} Stringzao;

int stringzaoGera(Stringzao *table);

void stringzaoCria(Stringzao *table);

int stringzaoDel(Stringzao *table, const size_t index);
int stringzaoShow(const Stringzao *table);

void stringzaoSortConsideraNos(Stringzao *table);

int stringzaoAddNode(Stringzao *table, const size_t soma);
#include "Stringzao.h"

void stringzaoCria(Stringzao *table)
{
    assert(table != NULL);

    table->size = 0;
    for (int i = 0; i < MAX_PALAVRAS; ++i)
    {
        for (int j = 0; j < MAX_PALAVRA; ++j)
            table->item[i].palavra[j] = '\0';
        table->item[i].is_internal = 1;
        table->item[i].frequency = 0;
    }
}


int stringzaoShow(const Stringzao *table)
{
    assert(table != NULL);

    if(table->size == 0)
    {
        printf("stringzaoShow(): ERRO Tabela stringzao vazia!\n");
        return -1;
    }

    for (size_t i = 0; i < table->size; ++i)
    {
        if(table->item[i].is_internal == 0)
            printf("stringzaoShow(): Linha: %zu Palavra: %s\tFrequência: %zu\n", i, table->item[i].palavra,
                   table->item[i].frequency);
        else
            printf("stringzaoShow(): Linha: %zu No interno! \tFrequência: %zu\n", i,
                   table->item[i].frequency);
    }
    puts("stringzaoShow(): \\\\\\\\");
    return 0;
}


void stringzaoSortConsideraNos(Stringzao *table)
{
    size_t i, j;
    StringzaoItem aux;
    for (i = 1; i <= table->size; i++)
    {
        j = i;
        while (j > 0 && table->item[i - 1].frequency < table->item[i].frequency)
        {
            if(table->item[i - 1].is_internal == 0 && table->item[i].is_internal == 1)
            {
#ifdef DEBUG
                puts("stringzaoSortConsideraNos(): Não podemos passar no interno antes de nó externo!");
#endif
                return;
            }
            aux = table->item[i-1];
            table->item[i-1] = table->item[i];
            table->item[i] = aux;

            j--;
        }
    }
}

void stringzaoSort(Stringzao *table)
{
    size_t i, j;
    StringzaoItem aux;
    for (i = 1; i <= table->size; i++)
    {
        j = i;
        while (j > 0 && table->item[i - 1].frequency < table->item[i].frequency)
        {
            aux = table->item[i-1];
            table->item[i-1] = table->item[i];
            table->item[i] = aux;

            j--;
        }
    }
}

int stringzaoAdd(Stringzao *table, const char *palavra)
{
    assert(table != NULL);
    assert(palavra != NULL);

    for (size_t i = 0; i < table->size; ++i)
    {
        if(strcmp(table->item[i].palavra,palavra) == 0)
        {
#ifdef DEBUG
            printf("stringzaoAdd(): DEBUG palavra %s já existe, aumentando frequency...\n",palavra);
#endif
            table->item[i].frequency += 1;
            stringzaoSort(table);
//            Não pode ter mais de uma igual
            return 1;
        }
    }
    strcpy(table->item[table->size].palavra,palavra);
    table->item[table->size].frequency = 1;
    table->item[table->size].is_internal = 0;
    table->size += 1;

    return 0;
}

int stringzaoDel(Stringzao *table, const size_t index)
{
    assert(table != NULL);
    assert(index > 0);
    assert(index < table->size);

    table->item[index].frequency = 0;
    table->item[index].palavra[0] = '\0';
    table->size--;
    stringzaoSort(table);

    return 0;
}

int stringzaoGera(Stringzao *table)
{
    assert(table != NULL);

    FILE *arquivo = fopen(PATH_ARQUIVO,"r");
    if(arquivo != NULL)
    {
        char palavra_temp[MAX_PALAVRA];
        while(!feof(arquivo))
        {
            fscanf(arquivo,"%s",palavra_temp);
            stringzaoAdd(table,palavra_temp);
        }
    }
    else
    {
        printf("stringzaoGera(): ERRO FATAL Impossível abrir o arquivo!");
        exit(EXIT_FAILURE);
    }
}

int stringzaoAddNode(Stringzao *table, const size_t soma)
{
    assert(table != NULL);
    assert(soma > 1);

    table->item[table->size].is_internal = 1;
    table->item[table->size].frequency = soma;

    table->size++;
    return 0;
}
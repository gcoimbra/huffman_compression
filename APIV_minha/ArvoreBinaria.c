#include "ArvoreBinaria.h"

void treeCria(No **raiz)
{
    *raiz = NULL;
}


void treeAlimenta(No **raiz, Stringzao *table, size_t soma_alvo)
{
    assert(table != NULL);
    assert(soma_alvo > 0);

    int flag = 0;
    size_t index = table->size - 1;
    size_t qtd_pais_soltos = 0;
    No *pais_soltos[MAX_PAIS_SOLTOS];

    while (index > 0)
    {
        StringzaoItem second = table->item[index],
                first = table->item[index - 1];

        if(first.frequency == soma_alvo && second.frequency == soma_alvo)
        {
            flag = 1;
            No *pai = (No *) calloc(1, sizeof(No));
            No *filho_esquerdo = (No *) calloc(1, sizeof(No));
            No *filho_direito = (No *) calloc(1, sizeof(No));


            pai->is_internal = 1;
            pai->soma = first.frequency + second.frequency;

            if(first.is_internal == 1 && second.is_internal == 0)
            {
                filho_esquerdo->is_internal = 1;
                filho_esquerdo->soma = second.frequency;
                strcpy(filho_esquerdo->B.Externo.palavra, second.palavra);

                filho_esquerdo->is_internal = 1;
                filho_esquerdo->soma = first.frequency;
            } else if(first.is_internal == 0 && second.is_internal == 1)
            {
                filho_esquerdo->is_internal = 0;
                filho_esquerdo->soma = first.frequency;
                strcpy(filho_esquerdo->B.Externo.palavra, first.palavra);

                filho_esquerdo->is_internal = 1;
                filho_esquerdo->soma = second.frequency;
            } else if(first.is_internal == 1 && second.is_internal == 1)
            {
                filho_esquerdo->soma = first.frequency;
                filho_esquerdo->soma = second.frequency;
            } else /* Os dois são externos */
            {
                filho_esquerdo->is_internal = 0;
                filho_esquerdo->soma = first.frequency;
                strcpy(filho_esquerdo->B.Externo.palavra, first.palavra);

                filho_direito->is_internal = 0;
                filho_direito->soma = first.frequency;
                strcpy(filho_direito->B.Externo.palavra, first.palavra);
            }

            pai->B.Interno.esquerdo = filho_esquerdo;
            pai->B.Interno.direito = filho_direito;

            *raiz = pai;

            stringzaoDel(table, index);
            stringzaoDel(table, index - 1);
            stringzaoAddNode(table, pai->soma);
            stringzaoSortConsideraNos(table);
            stringzaoShow(table);


            pais_soltos[qtd_pais_soltos++] = pai;
        }
        //        Repete loop
        index -= 1;
    }

    index = table->size - 1;
    if(!flag)
    {
        StringzaoItem second = table->item[index],
                first = table->item[index - 1];

        No *pai = (No *) calloc(1, sizeof(No));
        No *filho_esquerdo = (No *) calloc(1, sizeof(No));
        No *filho_direito = (No *) calloc(1, sizeof(No));


        pai->is_internal = 1;
        pai->soma = first.frequency + second.frequency;

        if(first.is_internal == 1 && second.is_internal == 0)
        {
            filho_esquerdo->is_internal = 1;
            filho_esquerdo->soma = second.frequency;
            strcpy(filho_esquerdo->B.Externo.palavra, second.palavra);

            filho_esquerdo->is_internal = 1;
            filho_esquerdo->soma = first.frequency;
        }
        else if(first.is_internal == 0 && second.is_internal == 1)
        {
            filho_esquerdo->is_internal = 0;
            filho_esquerdo->soma = first.frequency;
            strcpy(filho_esquerdo->B.Externo.palavra, first.palavra);

            filho_esquerdo->is_internal = 1;
            filho_esquerdo->soma = second.frequency;
        }
        else if(first.is_internal == 1 && second.is_internal == 1)
        {
            filho_esquerdo->soma = first.frequency;
            filho_esquerdo->soma = second.frequency;
        }
        else /* Os dois são externos */
        {
            filho_esquerdo->is_internal = 0;
            filho_esquerdo->soma = first.frequency;
            strcpy(filho_esquerdo->B.Externo.palavra, first.palavra);

            filho_direito->is_internal = 0;
            filho_direito->soma = first.frequency;
            strcpy(filho_direito->B.Externo.palavra, first.palavra);
        }

        pai->B.Interno.esquerdo = filho_esquerdo;
        pai->B.Interno.direito = filho_direito;

        *raiz = pai;

        stringzaoDel(table, index);
        stringzaoDel(table, index - 1);
        stringzaoAddNode(table, pai->soma);
        stringzaoSortConsideraNos(table);
        stringzaoShow(table);
    }

    size_t i = 0;
    while (qtd_pais_soltos > 1 && flag)
    {
        No *avo = (No *) calloc(1, sizeof(No));
        avo->soma = pais_soltos[i]->soma + pais_soltos[i + 1]->soma;
        avo->is_internal = 1;

        if(pais_soltos[i]->soma >= pais_soltos[i + 1]->soma)
        {
            avo->B.Interno.esquerdo = pais_soltos[i];
            avo->B.Interno.direito = pais_soltos[i + 1];
        } else
        {
            avo->B.Interno.esquerdo = pais_soltos[i + 1];
            avo->B.Interno.direito = pais_soltos[i];
        }

        qtd_pais_soltos -= 1;
        i += 2;
        *raiz = avo;
    }

    treeAlimenta(raiz, table, soma_alvo + 1);
}
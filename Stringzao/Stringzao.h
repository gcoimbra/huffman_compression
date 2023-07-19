/* 
 * File:   Stringzao.h
 * Authors: Daniel Freitas Martins  -   2304
 *          Maria Dalila            -   3030
 *          Gabriel Teixeira Pinto  -   3044
 *
 * Created on June 29, 2018, 2:33 AM
 */

#ifndef STRINGZAO_H
#define	STRINGZAO_H

#define FALSO 0
#define VERDADEIRO 1

#define TAM_MAX_TEXTO 5000
#define TAM_MAX_PALAVRA 50
#define MAX_QTD_PALAVRAS_TEXTO 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef	__cplusplus
extern "C" {
#endif

    // ESTRUTURA DE ITEM
    typedef struct{
        char palavra[TAM_MAX_PALAVRA];
        int qtd_ocorrencias;
    } Stringzao;

    
    void ordenaStringzao(Stringzao *stringzao, int tam_distintos_stringzao);

#ifdef	__cplusplus
}
#endif

#endif	/* STRINGZAO_H */


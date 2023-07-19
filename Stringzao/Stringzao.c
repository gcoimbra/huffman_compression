/* 
 * File:   Stringzao.c
 * Authors: Daniel Freitas Martins  -   2304
 *          Maria Dalila            -   3030
 *          Gabriel Teixeira Pinto  -   3044
 *
 * Created on June 29, 2018, 2:34 AM
 */


#include "../Stringzao/Stringzao.h"

/**
 * Ordena os elementos do tipo Stringzao de acordo com a frequência (qtd_ocorrencias) das palavras, do maior para o menor.
 * @param stringzao - Vetor do tipo Stringzao para ser reordenado de forma decrescente.
 * @param tam_distintos_stringzao - Quantidade de elementos a serem considerados no vetor (serão considerados a partir da posição 0 até (tam_distintos_stringzao - 1))
 */
void ordenaStringzao(Stringzao *stringzao, int tam_distintos_stringzao){
    int i, j;
    Stringzao stringzao_troca;    
    
    for(i = 1; i < tam_distintos_stringzao; i++){
        j = i;
        while(j > 0 && stringzao[j-1].qtd_ocorrencias < stringzao[j].qtd_ocorrencias){ // "Borbulha" o maior até a posição em que deve ficar.
            stringzao_troca = stringzao[j];
            stringzao[j] = stringzao[j-1];
            stringzao[j-1] = stringzao_troca;
            j--;
        }
    }
}

/* 
 * File:   ArvoreBinaria.h
 * Authors: Daniel Freitas Martins  -   2304
 *          Maria Dalila            -   3030
 *          Gabriel Teixeira Pinto  -   3044
 *
 * Created on June 29, 2018, 1:47 AM
 */


#ifndef ARVOREBINARIA_H
#define	ARVOREBINARIA_H

#include "../Stringzao/Stringzao.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum{
        INTERNO, EXTERNO
    } MarcadorTipoNo;

    typedef struct ArvoreBinNo{
        MarcadorTipoNo marcadorTipoNo;
        int altura; // Necessário para montar árvore canônica
        union{
            struct{            
                int soma;
                struct ArvoreBinNo *esquerda, *direita;
            } EstruturaInternaDeLigacao;
            struct{
                Stringzao stringzao;
            } EstruturaExternaDeLigacao;
        } ConteudoNo;
    } ArvoreBinNo;

    typedef struct{
        char palavra[TAM_MAX_PALAVRA];
        char buffer[257];
    } PalavraEmBinario;


    void criaArvoreBin(ArvoreBinNo **raiz);
    void alimentaArvoreBin(ArvoreBinNo **tree, Stringzao *stringzao, int tam_distintos_stringzao, short int flag_canonica);
    int pesquisaArvoreBin(ArvoreBinNo *tree, PalavraEmBinario *peb);
    void pesquisaInversaArvoreBin(char *texto_resultante, char *charToBin, ArvoreBinNo *tree);
    void destroiArvore(ArvoreBinNo **tree);
    void destroiArvoreAux(ArvoreBinNo **tree);
    
    void reordenaBufferPalavraEmBinario(char *novo_texto, PalavraEmBinario *peb);

#ifdef	__cplusplus
}
#endif

#endif	/* ARVOREBINARIA_H */


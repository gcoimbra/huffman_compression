/* 
 * File:   Compression.h
 * Authors: Daniel Freitas Martins  -   2304
 *          Maria Dalila            -   3030
 *          Gabriel Teixeira Pinto  -   3044
 *
 * Created on June 29, 2018, 1:49 AM
 */


#ifndef COMPRESSION_H
#define	COMPRESSION_H

#define LIDO_COM_SUCESSO 1
#define FALHA_NA_LEITURA 0

#include "ArvoreBinaria/ArvoreBinaria.h"

#ifdef	__cplusplus
extern "C" {
#endif

    void compressao(Stringzao *palavras_texto, Stringzao *palavras_texto_distintas, ArvoreBinNo **tree, char *novo_texto, int qtd_palavras, int *qtd_distintos, short int flag_canonica);    
    void comprimeTexto(char *novo_texto, Stringzao *palavras_texto, ArvoreBinNo **tree, int qtd_palavras);
    void comprimeDeFato(char *texto_a_ser_comprimido_de_fato, char *novo_texto_ilegivel, int tam_texto_comprimido);
    void descomprimir(char *texto_resultante, char *texto_comprimido_de_fato, int tam_texto_comprimido, ArvoreBinNo *tree);
    
    void converteInteiroParaBinario(int numero, int mascara, char *str);
    int lerArquivoStringzao(Stringzao *palavras_texto, int *qtd_palavras, char *nome_arq);
    int lerArquivoNormal(char *texto_lido, char *nome_arq);
    void criarArquivoComprimido(char *resultado_compressao_de_fato, int flag_canonica, char *nome_arq_lido, char *nome_arq_gerado);

#ifdef	__cplusplus
}
#endif

#endif	/* COMPRESSION_H */

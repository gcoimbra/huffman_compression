/* 
 * File:   Compression.c
 * Authors: Daniel Freitas Martins  -   2304
 *          Maria Dalila            -   3030
 *          Gabriel Teixeira Pinto  -   3044
 *
 * Created on June 29, 2018, 1:50 AM
 */

#include "Compression.h"

/**
 *  Função responsável pela compressão do texto.
 * @param palavras_texto - Vetor do tipo Stringzao com as palavras do texto.
 * @param palavras_texto_distintas - Vetor do tipo Stringzao que irá armazenar as palavras distintas do texto.
 * @param tree - Endereço de um ponteiro para um elemento do tipo ArvoreBinNo. Representa a raiz da árvore, para o contexto principal.
 * @param novo_texto - String que irá armazenar o conteúdo do texto comprimido.
 * @param qtd_palavras - Quantidade de palavras presentes no vetor Stringzao.
 * @param qtd_distintos - Endereço da variável que irá armazenar a quantidade de palavras distintas no texto.
 * @param flag_canonica - 1 se a árvore a ser construída deve ser canônica; 0 caso contrário.
 */
void compressao(Stringzao *palavras_texto, Stringzao *palavras_texto_distintas, ArvoreBinNo **tree, char *novo_texto, int qtd_palavras, int *qtd_distintos, short int flag_canonica){
    int i, j;    
    
    *qtd_distintos = 0;
    
    ///////// Alimentando vetor de palavras distintas e contando quantas são...
    for(i = 0; i < qtd_palavras; i++){
        for(j = 0; j < *qtd_distintos; j++){
            if(strcmp(palavras_texto[i].palavra, palavras_texto_distintas[j].palavra) == 0){
                palavras_texto_distintas[j].qtd_ocorrencias++;
                break;
            }
        }
        if(j == *qtd_distintos){
            strcpy(palavras_texto_distintas[j].palavra, palavras_texto[i].palavra);
            palavras_texto_distintas[j].qtd_ocorrencias = 1;
            (*qtd_distintos)++;
        }
    }
    //////////
    ordenaStringzao(palavras_texto_distintas, *qtd_distintos); // Ordenando de forma decrescente com relação à frequência, respeitando a ordem de inserção.
    alimentaArvoreBin(tree, palavras_texto_distintas, *qtd_distintos, flag_canonica);
    comprimeTexto(novo_texto, palavras_texto, tree, qtd_palavras);   
}

/**
 * Função responsável por comprimir o texto e retornar sua representação em binário para a variável "novo_texto".
 * @param novo_texto - String que irá armazenar a sequência de 0's e 1's correspondente ao caminho percorrido na árvore para montar o texto.
 * @param palavras_texto - Endereço de um elemento do tipo Stringzao, contendo as palavras usadas no texto.
 * @param tree - Endereço de um ponteiro para um elemento do tipo ArvoreBinNo. Representa a raiz da árvore, para o contexto principal.
 * @param qtd_palavras - Quantidade de palavras presentes no vetor Stringzao.
 */
void comprimeTexto(char *novo_texto, Stringzao *palavras_texto, ArvoreBinNo **tree, int qtd_palavras){
    PalavraEmBinario peb;
    long unsigned int i, j;
    
    
    novo_texto[0] = '\0';
    
    for(i = 0; i < qtd_palavras; i++){
        
        strcpy(peb.palavra, palavras_texto[i].palavra);        
        pesquisaArvoreBin(*tree, &peb);
        
        // peb.buffer é dado de trás para frente. Portanto, é necessário inverter a string!!
        reordenaBufferPalavraEmBinario(novo_texto, &peb);
        peb.buffer[0] = '\0';
    }    
}

/**
 * Esta função irá realizar a compressão da sequência de 0's e 1's agrupando-os de 8 em 8 bits. Quando não for possível, será completado com 0's os bits menos significativos.
 * @param texto_a_ser_comprimido_de_fato - String com sequência de 0's e 1's que irá ser comprimida de fato.
 * @param novo_texto - String que irá armazenar o texto comprimido de fato (Observe que o texto gerado é ilegível!).
 * @param tam_texto_comprimido - Tamanho do texto a ser considerado, gerado após a compressão para representação binária e legível. Ou seja, é a quantidade de bits na representação binária legível.
 */
void comprimeDeFato(char *texto_a_ser_comprimido_de_fato, char *novo_texto_ilegivel, int tam_texto_comprimido){
    int i, j, k, inteiro_correspondente;
    i = 1;
    
    while(tam_texto_comprimido >= i*8){
        k = 0;
        inteiro_correspondente = 0;
        for(j = i*8 - 1; j >= (i-1)*8; j--){ // Varrendo um byte para transformar em inteiro (consequentemente, transforma em char).
            if(texto_a_ser_comprimido_de_fato[j] != '0'){
                inteiro_correspondente += pow(2, k);
            }
            k++;
        }
        novo_texto_ilegivel[(i-1)] = inteiro_correspondente;
        i++;
    }
    k = 0;
    inteiro_correspondente = 0;
    for(j = i*8 - 1; j >= (i-1)*8; j--){ // Última passada para tratar o problema de completar com 0's os bits menos significativos.
        // Observação: o valor de j inicialmente é maior ou igual a tam_texto_comprimido, e decai com as passadas...
        if(tam_texto_comprimido >= j){ // Quando j for menor ou igual a tam_texto_comprimido, considere os bits na operação...
            if(texto_a_ser_comprimido_de_fato[j] != '0'){
                inteiro_correspondente += pow(2, k);
            }
        }
        k++;
    }
    novo_texto_ilegivel[(i-1)] = inteiro_correspondente;
    novo_texto_ilegivel[i] = '\0';
}


/**
 * Função responsável por descomprimir um texto comprimido (de fato). Este texto passa por um processo de identificação dos bits de cada byte correspondente.
 * @param texto_resultante - String que irá armazenar o conteúdo do texto descomprimido.
 * @param texto_comprimido_de_fato - String que possui o texto comprimido (de fato: de forma ilegível / com caracteres que não possuem sentido ao se tentar ler).
 * @param tam_texto_comprimido - Tamanho do texto a ser considerado, gerado após a compressão para representação binária e legível. Ou seja, é a quantidade de bits na representação binária legível.
 * @param tree - Endereço de um ponteiro para um elemento do tipo ArvoreBinNo. Representa a raiz da árvore, para o contexto principal.
 */
void descomprimir(char *texto_resultante, char *texto_comprimido_de_fato, int tam_texto_comprimido, ArvoreBinNo *tree){
    char charToBin[TAM_MAX_TEXTO];
    int i, tam_novo_texto;    
    
    ///////////// "Decifrando" a sequência de caracteres (bytes) ilegíveis...
    tam_novo_texto = strlen(texto_comprimido_de_fato);
    charToBin[0] = '\0';
    for(i = 0; i < tam_novo_texto; i++){
        converteInteiroParaBinario((int) texto_comprimido_de_fato[i], 8, charToBin); // Transforma cada char (byte) para sua representação em binário de 8 bits e concatena em charToBin.
    }
    charToBin[(tam_texto_comprimido % 8) + (i-1)*8] = '\0'; // Tratando o problema do tamanho do texto comprimido não for um número divisível por 8.
    /////////////
    pesquisaInversaArvoreBin(texto_resultante, charToBin, tree); // Após a parte de decifrar o texto ilegível, basta montar o texto de acordo com o caminho gerado e a árvore
}

/** --- Código do primeiro TP de OC1 ---
 * Função responsável por converter um número inteiro para binário, armazenando o conteúdo binário em *str.
 * @param numero - Valor a ser convertido.
 * @param mascara - Limite de bits para o resultado da conversão. Exemplo: Mascara = 5 indica que existirão 5 bits na saída (XXXXX).
 * @param str - Ponteiro para a primeira posição da string.
 */
void converteInteiroParaBinario(int numero, int mascara, char *str){
    char binario[mascara+1];
    int deslocar, k;

    for(deslocar = mascara-1; deslocar >= 0; deslocar--){
        k = numero >> deslocar;

        if(k & 1){
            binario[mascara - 1 - deslocar] = '1';
        } else{
            binario[mascara - 1 - deslocar] = '0';
        }
    }
    binario[mascara] = '\0';
    strcat(str, binario);
}

/**
 * Função responsável pela leitura de um arquivo.
 * @param palavras_texto - Vetor do tipo Stringzao que armazenará as palavras do texto.
 * @param qtd_palavras - Endereço de uma variável que irá armazenar a quantidade de palavras lidas no texto.
 * @param nome_arq - Nome do arquivo a ser lido.
 * @return 1 se o arquivo foi lido com sucesso; 0 caso contrário.
 */
int lerArquivoStringzao(Stringzao *palavras_texto, int *qtd_palavras, char *nome_arq){
    FILE *arquivo = NULL;
    char palavra[TAM_MAX_PALAVRA];
    //int tam_palavra;
    
    if(nome_arq == NULL){
        return FALHA_NA_LEITURA;
    } // else
    
    *qtd_palavras = 0; // INICIALIZANDO qtd_palavras
    arquivo = fopen(nome_arq, "rt");
    if(arquivo != NULL){
        while(!feof(arquivo)){
            fscanf(arquivo, "%s", palavra);
            strcpy(palavras_texto[*qtd_palavras].palavra, palavra);
            
            (*qtd_palavras)++;
        }
        
        fclose(arquivo);
    } else{        
        //printf("FALHA AO ABRIR O ARQUIVO!\n");
        return FALHA_NA_LEITURA;
    }
    return LIDO_COM_SUCESSO;
}

/**
 * Função responsável pela leitura de um arquivo.
 * @param texto_lido - Variável String que irá armazenar o conteúdo lido do arquivo.
 * @param nome_arq - Nome do arquivo a ser lido.
 * @return 1 se o arquivo foi lido com sucesso; 0 caso contrário.
 */
int lerArquivoNormal(char *texto_lido, char *nome_arq){
    FILE *arquivo = NULL;
    char caract_lido;
    int index_caract;
    //int tam_palavra;
    
    if(nome_arq == NULL || texto_lido == NULL){
        return FALHA_NA_LEITURA;
    } // else
    
    texto_lido[0] = '\0';
    arquivo = fopen(nome_arq, "rt");
    index_caract = 0;
    if(arquivo != NULL){
        fscanf(arquivo, "%c", &caract_lido);
        while(!feof(arquivo)){
            texto_lido[index_caract++] = caract_lido;
            fscanf(arquivo, "%c", &caract_lido);            
        }
        texto_lido[index_caract] = '\0';
        fclose(arquivo);
    } else{
        return FALHA_NA_LEITURA;
    }
    return LIDO_COM_SUCESSO;
}

/**
 * Procedimento responsável por criar um arquivo .bin com o nome formado pelo prefixo "nome_arq_lido" e sufixos "flag_canonica" + "_" +"comprimido.bin"
 * @param resultado_compressao_de_fato - Texto formado por sequência de 0's e 1's.
 * @param flag_canonica - Indica se o arquivo resultante se refere à árvore canônica ou não.
 * @param nome_arq_lido - Nome do arquivo que foi lido para gerar o resultado da compressão (opcional).
 * @param nome_arq_gerado - Variável String que irá armazenar o nome do arquivo gerado.
 */
void criarArquivoComprimido(char *resultado_compressao_de_fato, int flag_canonica, char *nome_arq_lido, char *nome_arq_gerado){
    FILE *novo_arq;
    char nome_novo_arq[255], substring_nome_arq_lido[255];
    nome_novo_arq[0] = '\0';    
    if(nome_arq_lido != NULL){
        strcpy(substring_nome_arq_lido, nome_arq_lido);
        substring_nome_arq_lido[strlen(nome_arq_lido)-4] = '\0'; // Removendo a extensão do nome do arquivo...
        strcat(nome_novo_arq, substring_nome_arq_lido);
    }
    if(flag_canonica == VERDADEIRO){
        strcat(nome_novo_arq, "canonica_");
    } else{
        strcat(nome_novo_arq, "comum_");
    }
    
    strcat(nome_novo_arq, "comprimido.bin");
    novo_arq = fopen(nome_novo_arq, "w+t");
    
    if(novo_arq == NULL){
        if(nome_arq_gerado != NULL)
            nome_arq_gerado[0] = '\0';
        printf("(*) Erro ao criar o arquivo \"%s\"\n\n", nome_novo_arq);
    } else{
        if(nome_arq_gerado != NULL)
            strcpy(nome_arq_gerado, nome_novo_arq);
        fprintf(novo_arq, "%s", resultado_compressao_de_fato);
        printf("(*) Arquivo \"%s\" gerado com sucesso!\n\n", nome_novo_arq);
        fclose(novo_arq);
    }
}

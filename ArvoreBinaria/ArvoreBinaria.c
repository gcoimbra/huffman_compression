/* 
 * File:   ArvoreBinaria.c
 * Authors: Daniel Freitas Martins  -   2304
 *          Maria Dalila            -   3030
 *          Gabriel Teixeira Pinto  -   3044
 *
 * Created on June 29, 2018, 1:47 AM
 */

#include "ArvoreBinaria.h"

/**
 * Inicializa a árvore.
 * @param raiz - Endereço de um ponteiro para um elemento do tipo ArvoreBinNo, representando a raiz da árvore.
 */
void criaArvoreBin(ArvoreBinNo **raiz){
    (*raiz) = NULL;
}

/**
 * Função responsável por criar a árvore e organizar seus nós de acordo com o algoritmo visto em sala.
 * @param tree - Endereço de um ponteiro para um elemento do tipo ArvoreBinNo. Representa a raiz da árvore, para o contexto principal.
 * @param stringzao - Vetor do tipo Stringzao com as palavras do texto organizadas de forma decrescente pela frequência.
 * @param tam_distintos_stringzao - Quantidade de elementos a serem considerados no vetor (serão considerados a partir da posição 0 até (tam_distintos_stringzao - 1))
 * @param flag_canonica - 1 se a árvore a ser construída deve ser canônica; 0 caso contrário.
 */
void alimentaArvoreBin(ArvoreBinNo **tree, Stringzao *stringzao, int tam_distintos_stringzao, short int flag_canonica){
    ArvoreBinNo **nos_tabela, *troca_no, *novo_no_interno;
    int i;
    short int direita_eh_maior;
    
    /////// Criando a tabela de elementos De Trás para frente!
    nos_tabela = (ArvoreBinNo**) malloc(tam_distintos_stringzao * sizeof(ArvoreBinNo *));
    for(i = 0; i < tam_distintos_stringzao; i++){
        nos_tabela[i] = (ArvoreBinNo*) malloc(sizeof(ArvoreBinNo));
        nos_tabela[i]->marcadorTipoNo = EXTERNO;
        nos_tabela[i]->altura = 0;
        nos_tabela[i]->ConteudoNo.EstruturaExternaDeLigacao.stringzao = stringzao[i];
    }
    ////////////////////////
    
    while(tam_distintos_stringzao > 1){
        // A cada passada, sempre é criado um novo nó interno
        novo_no_interno = (ArvoreBinNo*) malloc(sizeof(ArvoreBinNo));
        novo_no_interno->marcadorTipoNo = INTERNO;
        direita_eh_maior = (nos_tabela[tam_distintos_stringzao - 1]->altura >= nos_tabela[tam_distintos_stringzao - 2]->altura);
        if(direita_eh_maior == 1 || flag_canonica == FALSO){ // Para garantir árvore canônica...
            novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.direita = nos_tabela[tam_distintos_stringzao - 1];
            novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.esquerda = nos_tabela[tam_distintos_stringzao - 2];
        } else{
            novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.direita = nos_tabela[tam_distintos_stringzao - 2];
            novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.esquerda = nos_tabela[tam_distintos_stringzao - 1];
        }
        if(direita_eh_maior || flag_canonica == VERDADEIRO){ // Estabelecendo coerência com a altura do novo nó...
            novo_no_interno->altura = 1 + novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.direita->altura;
        } else{
            novo_no_interno->altura = 1 + novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.esquerda->altura;
        }
        if(novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.direita->marcadorTipoNo == INTERNO){
            novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.soma = novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.direita->ConteudoNo.EstruturaInternaDeLigacao.soma;
        } else{ // EXTERNO
            novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.soma = novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.direita->ConteudoNo.EstruturaExternaDeLigacao.stringzao.qtd_ocorrencias;
        }
        if(novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.esquerda->marcadorTipoNo == INTERNO){
            novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.soma += novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.esquerda->ConteudoNo.EstruturaInternaDeLigacao.soma;
        } else{ // EXTERNO
            novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.soma += novo_no_interno->ConteudoNo.EstruturaInternaDeLigacao.esquerda->ConteudoNo.EstruturaExternaDeLigacao.stringzao.qtd_ocorrencias;
        }        
        
        nos_tabela[tam_distintos_stringzao - 2] = novo_no_interno; /*
                                                                        O novo nó é a junção de dois nós. Portanto, o nó "menos significativo" é ignorado e o novo nó 
                                                                        assume a posição do nó "mais significativo", reduzindo assim a altura da "tabela" em uma unidade. 
                                                                        Reordenamento precisará ser feito, caso seja necessário (veja a seguir).
                                                                    */
        
        
        //////// REORDENANDO
        i = tam_distintos_stringzao - 2; // i recebe a posição do novo nó criado, que é do tipo INTERNO.
        while
        (i > 0 && 
            (   // Checa-se inicialmente se o campo avaliado é de um nó interno (soma) ou nó externo (qtd_ocorrencias de stringzao). Depois, checa se o novo nó interno gerado deve "borbulhar" para cima.
                (nos_tabela[i - 1]->marcadorTipoNo == INTERNO)
                ? // Então
                (nos_tabela[i - 1]->ConteudoNo.EstruturaInternaDeLigacao.soma < nos_tabela[i]->ConteudoNo.EstruturaInternaDeLigacao.soma)
                : // Senão
                (nos_tabela[i - 1]->ConteudoNo.EstruturaExternaDeLigacao.stringzao.qtd_ocorrencias < nos_tabela[i]->ConteudoNo.EstruturaInternaDeLigacao.soma)
            )
        ){
            // Se entrou, o novo nó interno deve subir uma posição na tabela:
            troca_no = nos_tabela[i];
            nos_tabela[i] = nos_tabela[i-1];
            nos_tabela[i-1] = troca_no;   
            i--;
        }        
        //////////////////
        
        tam_distintos_stringzao -= 1; // Como dito, a quantidade de elementos na tabela se reduz em uma unidade devido à junção de dois nós em apenas um.
    }
    // Ao fim, todos os nós internos já se agruparam. O único nó restante só pode ser a raiz. Então, o parâmetro da raiz deverá receber o último nó criado.
    (*tree) = novo_no_interno;    
    
}

/**
 * Função responsável por encontrar um elemento na árvore e armazenar o caminho feito na variável "peb".
 * @param tree - Endereço de um ponteiro para um elemento do tipo ArvoreBinNo. Representa a raiz da árvore, para o contexto principal.
 * @param peb - Endereço de um elemento do tipo PalavraEmBinario, contendo a palavra a ser pesquisada e um buffer para guardar o caminho percorrido na árvore.
 * @return 1 se a palavra foi encontrada; 0 caso contrário.
 */
int pesquisaArvoreBin(ArvoreBinNo *tree, PalavraEmBinario *peb){    
    
    if(tree != NULL){
        if(tree->marcadorTipoNo == INTERNO){
            if(pesquisaArvoreBin(tree->ConteudoNo.EstruturaInternaDeLigacao.esquerda, peb)){
                strcat(peb->buffer, "0\0");
                return 1;
            } else{
                if(pesquisaArvoreBin(tree->ConteudoNo.EstruturaInternaDeLigacao.direita, peb)){
                    strcat(peb->buffer, "1\0");
                    return 1;
                }
            }            
        } else{
            peb->buffer[0] = '\0';
            if(strcmp(tree->ConteudoNo.EstruturaExternaDeLigacao.stringzao.palavra, peb->palavra) == 0){
                return 1;
            } else{
                return 0;
            }
        }        
    }
    return 0;
}

/**
 * Realiza a pesquisa inversa na árvore: Dado o caminho de bits (variável "charToBin"), encontra a palavra.
 * @param texto_resultante - String que irá armazenar o texto formado..
 * @param charToBin - String com a sequência de 0's e 1's a ser percorrida de modo a formar um texto.
 * @param tree - Endereço de um elemento do tipo ArvoreBinNo. Representa a Raíz para o contexto principal.
 */
void pesquisaInversaArvoreBin(char *texto_resultante, char *charToBin, ArvoreBinNo *tree){
    ArvoreBinNo *encontra_ocorrencia;
    int varre_texto_bin, tam_texto_bin;
    
    varre_texto_bin = 0;
    tam_texto_bin = strlen(charToBin);
    texto_resultante[0] = '\0';
    
    while(varre_texto_bin < tam_texto_bin){
        encontra_ocorrencia = tree;
        while(encontra_ocorrencia->marcadorTipoNo != EXTERNO){
            if(charToBin[varre_texto_bin] == '1'){
                encontra_ocorrencia = encontra_ocorrencia->ConteudoNo.EstruturaInternaDeLigacao.direita;
            } else{
                encontra_ocorrencia = encontra_ocorrencia->ConteudoNo.EstruturaInternaDeLigacao.esquerda;
            }
            varre_texto_bin++;
        }
        strcat(texto_resultante, encontra_ocorrencia->ConteudoNo.EstruturaExternaDeLigacao.stringzao.palavra);
        if(varre_texto_bin != tam_texto_bin)
            strcat(texto_resultante, " \0");
    }
}

/**
 * Função responsável por destruir a árvore.
 * @param tree - Endereço para um ponteiro de ArvoreBinNo. Representa a raíz da árvore.
 */
void destroiArvore(ArvoreBinNo **tree){
    destroiArvoreAux(tree);
}

/**
 * Procedimento auxiliar para destruir a árvore.
 * @param tree - Endereço para um ponteiro de ArvoreBinNo. Representa a raíz da árvore.
 */
void destroiArvoreAux(ArvoreBinNo **tree){
    ArvoreBinNo *removedor;
    if(*tree != NULL){
        if((*tree)->marcadorTipoNo == INTERNO){
            if((*tree)->ConteudoNo.EstruturaInternaDeLigacao.direita != NULL)
                destroiArvoreAux(&(*tree)->ConteudoNo.EstruturaInternaDeLigacao.direita);

            if((*tree)->ConteudoNo.EstruturaInternaDeLigacao.esquerda != NULL)
                destroiArvoreAux(&(*tree)->ConteudoNo.EstruturaInternaDeLigacao.direita);
        }
        
        removedor = *tree;
        free(removedor);        
    }
}

/**
 * Função responsável por reordenar o buffer retornado pela pesquisa na árvore. (A pesquisa retorna o buffer ao contrário)
 * @param novo_texto - String que irá armazenar o valor do buffer reordenado; NULL caso queira reordenar apenas o "peb".
 * @param peb - Endereço de um elemento do tipo PalavraEmBinario.
 */
void reordenaBufferPalavraEmBinario(char *novo_texto, PalavraEmBinario *peb){
    long unsigned int j, tam_peb_buffer;
    char caract_troca;
    
    tam_peb_buffer = strlen(peb->buffer);
    for(j = 0; j < tam_peb_buffer/2; j++){
        caract_troca = peb->buffer[j];
        peb->buffer[j] = peb->buffer[tam_peb_buffer - j - 1];
        peb->buffer[tam_peb_buffer - j - 1] = caract_troca;
    }
    if(novo_texto != NULL)
        strcat(novo_texto, peb->buffer);    
}
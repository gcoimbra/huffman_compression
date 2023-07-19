/* 
 * File:   main.c
 * Authors: Daniel Freitas Martins  -   2304
 *          Maria Dalila            -   3030
 *          Gabriel Teixeira Pinto  -   3044
 *
 * Created on June 26, 2018, 11:27 PM
 */

#include "Compression.h"

void pausarTemporariamente(){
    printf("(*) Pressione qualquer tecla para continuar...");
    getchar();
}

/*
 * 
 */
int main(int argc, char** argv) {

    ArvoreBinNo *raiz_canonica, *raiz_comum; // raiz_comum == Árvore não canônica
    Stringzao palavras_texto[MAX_QTD_PALAVRAS_TEXTO];
    Stringzao palavras_texto_distintas[MAX_QTD_PALAVRAS_TEXTO];
    char texto[TAM_MAX_TEXTO];
    char novo_texto_canonica[TAM_MAX_TEXTO], novo_texto_comum[TAM_MAX_TEXTO];
    char novo_texto_canonica_ilegivel[TAM_MAX_TEXTO], novo_texto_comum_ilegivel[TAM_MAX_TEXTO];
    char texto_resultante_canonica[TAM_MAX_TEXTO], texto_resultante_comum[TAM_MAX_TEXTO];
    char nome_arq_texto[255], nome_arq_gerado_canonica[255], nome_arq_gerado_comum[255], arquivo_ilegivel_a_ser_lido[255];
    int tam_texto_comprimido_canonica, tam_texto_comprimido_comum, tam_texto_normal;
    int qtd_palavras, qtd_distintos_stringzao;
    int i, op, op2;
    float razao_compressao_canonica, razao_compressao_comum;
    PalavraEmBinario *tabela_huffman_canonica, *tabela_huffman_comum;

    criaArvoreBin(&raiz_canonica);
    criaArvoreBin(&raiz_comum);
    nome_arq_texto[0] = '\0';
    nome_arq_gerado_canonica[0] = '\0';
    nome_arq_gerado_comum[0] = '\0';
    
    do{
        printf("     ############################################\n");
        printf("     ######### Huffman Compression Test #########\n");
        printf("     ############################################\n\n");
        printf("(*) Escolha uma opcao:\n");
        printf("   1 - Ler arquivo e realizar compressao;\n");
        printf("   2 - Exibir informacoes obtidas pela arvore canonica;\n");
        printf("   3 - Exibir informacoes obtidas pela arvore comum (nao canonica).\n");
        printf("   4 - Descomprimir arquivo gerado pela compressao resultante da arvore canonica.\n");
        printf("   5 - Descomprimir arquivo gerado pela compressao resultante da arvore comum (nao canonica).\n\n");
        printf("   0 - Sair\n\n-> ");
        scanf("%d", &op);
        getchar(); // desbugando buffer...
        
        switch(op){
            case 1:
                printf("Informe o nome do arquivo a ser lido com sua extensao: ");
                scanf("%[^\n]254", nome_arq_texto);
                getchar();
                if(raiz_canonica != NULL && raiz_comum != NULL){
                    destroiArvore(&raiz_canonica);
                    destroiArvore(&raiz_comum);
                }
                criaArvoreBin(&raiz_canonica);
                criaArvoreBin(&raiz_comum);
                
                if(lerArquivoStringzao(palavras_texto, &qtd_palavras, nome_arq_texto) == LIDO_COM_SUCESSO){
                    ///////// Montando o texto em uma variavel
                    texto[0] = '\0';
                    tam_texto_normal = 0;
                    for(i = 0; i < qtd_palavras; ){
                        strcat(texto, palavras_texto[i].palavra);
                        tam_texto_normal += strlen(palavras_texto[i].palavra);
                        i++;
                        if(i != qtd_palavras)
                            strcat(texto, " \0");
                    }
                    ////////////////////
                    
                    compressao(palavras_texto, palavras_texto_distintas, &raiz_canonica, novo_texto_canonica, qtd_palavras, &qtd_distintos_stringzao, 1);
                    compressao(palavras_texto, palavras_texto_distintas, &raiz_comum, novo_texto_comum, qtd_palavras, &qtd_distintos_stringzao, 0);

                    tabela_huffman_canonica = (PalavraEmBinario*) malloc(qtd_distintos_stringzao * sizeof(PalavraEmBinario));
                    tabela_huffman_comum = (PalavraEmBinario*) malloc(qtd_distintos_stringzao * sizeof(PalavraEmBinario));
                    
                    tam_texto_comprimido_canonica = strlen(novo_texto_canonica);
                    tam_texto_comprimido_comum = strlen(novo_texto_comum);

                    comprimeDeFato(novo_texto_canonica, novo_texto_canonica_ilegivel, tam_texto_comprimido_canonica);
                    comprimeDeFato(novo_texto_comum, novo_texto_comum_ilegivel, tam_texto_comprimido_comum);      
                    
                    criarArquivoComprimido(novo_texto_canonica_ilegivel, VERDADEIRO, nome_arq_texto, nome_arq_gerado_canonica);
                    criarArquivoComprimido(novo_texto_comum_ilegivel, FALSO, nome_arq_texto, nome_arq_gerado_comum);
                    
                } else{
                    printf("(*) Falha ao ler o arquivo!\n\n");
                }
                break;
            case 2:
                if(raiz_canonica == NULL){
                    printf("Nao existe arvore canonica inicializar! Efetue a operacao 1 antes de efetuar esta...");
                    break;
                }
                printf("------------- INFORMACOES OBTIDAS PELA ARVORE CANONICA -------------\n");
                printf("       Tabela de Huffman\n");
                for(i = 0; i < qtd_distintos_stringzao; i++){
                    strcpy(tabela_huffman_canonica[i].palavra, palavras_texto_distintas[i].palavra);
                    pesquisaArvoreBin(raiz_canonica, &(tabela_huffman_canonica[i]));
                    reordenaBufferPalavraEmBinario(NULL, &(tabela_huffman_canonica[i]));
                    printf("%s\t\t%s\n", tabela_huffman_canonica[i].palavra, tabela_huffman_canonica[i].buffer);
                }
                printf("\nTexto original: \"%s\"\nTexto comprimido (legivel): \"%s\"\n\n", texto, novo_texto_canonica);
                printf("Texto comprimido (De fato | ilegivel): \"%s\"\n\n", novo_texto_canonica_ilegivel);                
                razao_compressao_canonica = (float)tam_texto_comprimido_canonica/(tam_texto_normal*8);                
                printf("Razao de compressao (canonica): %d/%d = %.4f = %.2f%%\n", tam_texto_comprimido_canonica, (tam_texto_normal*8), razao_compressao_canonica, (razao_compressao_canonica*100));                
                break;
            case 3:
                if(raiz_comum == NULL){
                    printf("Nao existe arvore comum inicializar! Efetue a operacao 1 antes de efetuar esta...");
                    break;
                }
                printf("------------- INFORMACOES OBTIDAS PELA ARVORE COMUM -------------\n");
                printf("       Tabela de Huffman\n");
                for(i = 0; i < qtd_distintos_stringzao; i++){
                    strcpy(tabela_huffman_comum[i].palavra, palavras_texto_distintas[i].palavra);
                    pesquisaArvoreBin(raiz_comum, &(tabela_huffman_comum[i]));
                    reordenaBufferPalavraEmBinario(NULL, &(tabela_huffman_comum[i]));
                    printf("%s\t\t%s\n", tabela_huffman_comum[i].palavra, tabela_huffman_comum[i].buffer);
                }
                printf("\nTexto original: \"%s\"\nTexto comprimido (legivel): \"%s\"\n\n", texto, novo_texto_comum);
                printf("Texto comprimido (De fato | ilegivel): \"%s\"\n\n", novo_texto_comum_ilegivel);     
                razao_compressao_comum = (float)tam_texto_comprimido_comum/(tam_texto_normal*8);
                printf("Razao de compressao (comum): %d/%d = %.4f = %.2f%%\n\n", tam_texto_comprimido_comum, (tam_texto_normal*8), razao_compressao_comum, (razao_compressao_comum*100));
                break;
            case 4:
                if(raiz_canonica == NULL){
                    printf("Nao existe arvore canonica inicializar! Efetue a operacao 1 antes de efetuar esta...");
                    break;
                }
                printf("Escolha uma opcao:\n");
                printf("   1 - Utilizar arquivo gerado pela compressao;\n");
                printf("   2 - Informar um arquivo para ser descomprimido.\n\n-> ");
                scanf("%d", &op2);
                getchar();
                switch(op2){
                    case 1:
                        strcpy(arquivo_ilegivel_a_ser_lido, nome_arq_gerado_canonica);
                        break;
                    case 2:
                        printf("\nInforme o nome do arquivo a ser descomprimido: ");
                        scanf("%[^\n]254", arquivo_ilegivel_a_ser_lido);
                        getchar();
                        
                        break;
                }
                if(lerArquivoNormal(novo_texto_canonica_ilegivel, arquivo_ilegivel_a_ser_lido)){
                    descomprimir(texto_resultante_canonica, novo_texto_canonica_ilegivel, tam_texto_comprimido_canonica, raiz_canonica);
                    printf("\n\n-> Arquivo lido: \"%s\"\n",arquivo_ilegivel_a_ser_lido);
                    printf("Texto descomprimido (canonica): \"%s\"\n\n", texto_resultante_canonica);
                } else{
                    printf("(*) Nao foi possivel ler o arquivo!");
                }                     
                
                break;
            case 5:
                if(raiz_comum == NULL){
                    printf("Nao existe arvore comum inicializar! Efetue a operacao 1 antes de efetuar esta...");
                    break;
                }
                printf("Escolha uma opcao:\n");
                printf("   1 - Utilizar arquivo gerado pela compressao;\n");
                printf("   2 - Informar um arquivo para ser descomprimido.\n\n-> ");
                scanf("%d", &op2);
                getchar();
                switch(op2){
                    case 1:
                        strcpy(arquivo_ilegivel_a_ser_lido, nome_arq_gerado_comum);
                        break;
                    case 2:
                        printf("\nInforme o nome do arquivo a ser descomprimido: ");
                        scanf("%[^\n]254", arquivo_ilegivel_a_ser_lido);
                        getchar();
                        
                        break;
                }
                if(lerArquivoNormal(novo_texto_comum_ilegivel, arquivo_ilegivel_a_ser_lido)){
                    descomprimir(texto_resultante_comum, novo_texto_comum_ilegivel, tam_texto_comprimido_comum, raiz_comum);
                    printf("\n\n-> Arquivo lido: \"%s\"\n",arquivo_ilegivel_a_ser_lido);
                    printf("Texto descomprimido (comum): \"%s\"\n\n", texto_resultante_comum);
                } else{
                    printf("(*) Nao foi possivel ler o arquivo!");
                }
                break;
            case 0:
                printf("(*) Volte sempre!\n\n");
        }
        printf("\n\n");
        pausarTemporariamente();
        printf("\n\n\n\n\n\n\n");
    }while(op != 0);

    return (EXIT_SUCCESS);
}
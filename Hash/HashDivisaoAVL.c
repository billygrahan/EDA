#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../AVL/AVL.h"

// Função hash (divisão)
int hashDivisao(int chave, int tamanho)
{
    return chave % tamanho;
}

// Inserção na tabela hash com AVL
void adicionarNo(No **tabela, int chave, int tamanho)
{
    int indice = hashDivisao(chave, tamanho);
    char h = 'F';
    inserir(&tabela[indice], chave, &h); // Usa a função AVL
}

// Busca na tabela hash com AVL
int buscarNo(No **tabela, int chave, int tamanho)
{
    int indice = hashDivisao(chave, tamanho);
    No *atual = tabela[indice];
    while (atual != NULL)
    {
        if (atual->valor == chave)
            return 1;
        if (chave < atual->valor)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    return 0;
}



// Impressão in-ordem de cada AVL da tabela
void imprimirTabela(No **tabela, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("Indice %d: ", i);
        print_inordem(tabela[i]);
        printf("NULL\n");
    }
}

// gcc -Wall -Wextra -g3 /home/billy/EDA/Hash/HashDivisaoAVL.c /home/billy/EDA/AVL/AVL.c -o /home/billy/EDA/Hash/output/HashDivisaoAVL
int main()
{
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock();

    int n = 250000;
    int tamanho = 200000;
    int max_val = 2000000000;

    No **tabela = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++)
        tabela[i] = NULL;

    // Gerar vetor de valores únicos para inserir
    int *valores = malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        valores[i] = (rand() % (max_val - n)) + 1 + i;

    embaralhar(valores, n);

    // Inserir os n valores na tabela hash (AVL)
    for (int i = 0; i < n; i++)
        adicionarNo(tabela, valores[i], tamanho);

    // Imprimir a tabela hash
    imprimirTabela(tabela, tamanho);
    
    // Buscar 1.000.000 de chaves aleatórias existentes
    int buscas = 1000000;
    int achadas = 0;
    for (int i = 0; i < buscas; i++)
    {
        int idx = rand() % n;
        if (buscarNo(tabela, valores[idx], tamanho))
            achadas++;
    }

    printf("Chaves encontradas: %d de %d buscas\n", achadas, buscas);

    // Liberação de memória das AVLs
    for (int i = 0; i < tamanho; i++)
        liberar(tabela[i]);
    free(tabela);
    free(valores);

    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../AVL/AVL.h"

// Função hash de dobra decimal (soma dos pedaços)
int hashDobraDecimal(int chave, int tamanho)
{
    int base = tamanho;
    int soma = 0;
    while (chave > 0)
    {
        soma += chave % base;
        chave /= base;
    }
    return soma % tamanho;
}

// Inserção na tabela hash com AVL
void adicionarNo(No **tabela, int chave, int tamanho)
{
    int indice = hashDobraDecimal(chave, tamanho);
    char h = 'F';
    inserir(&tabela[indice], chave, &h); // Usa AVL
}

// Busca na tabela hash com AVL
int buscarNo(No **tabela, int chave, int tamanho)
{
    int indice = hashDobraDecimal(chave, tamanho);
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

// Teste para Hash Dobra Decimal com AVL
void DobraDecimal()
{
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock();

    int n = 250000;
    int tamanho = 200000;
    int max_val = 2000000000;
    int buscas = 1000000;

    No **tabela = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++)
        tabela[i] = NULL;

    int *valores = malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        valores[i] = (rand() % (max_val - n)) + 1 + i;
    embaralhar(valores, n);

    for (int i = 0; i < n; i++)
        adicionarNo(tabela, valores[i], tamanho);

    int achadas = 0;
    for (int i = 0; i < buscas; i++)
    {
        int idx = rand() % n;
        if (buscarNo(tabela, valores[idx], tamanho))
            achadas++;
    }

    printf("Hash Dobra Decimal (AVL): Chaves encontradas: %d de %d buscas\n", achadas, buscas);

    for (int i = 0; i < tamanho; i++)
        liberar(tabela[i]);
    free(tabela);
    free(valores);

    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);
}

// gcc -Wall -Wextra -g3 /home/billy/EDA/Hash/HashDobraDecimalAVL.c /home/billy/EDA/AVL/AVL.c -o /home/billy/EDA/Hash/output/HashDobraDecimalAVL
/// home/billy/EDA/Hash/output/HashDobraDecimalAVL
int main()
{
    DobraDecimal();
    return 0;
}
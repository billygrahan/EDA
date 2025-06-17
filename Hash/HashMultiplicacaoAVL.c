#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../AVL/AVL.h"

double A = 0.6180339887;

int hashMultiplicacao(int chave, int tamanho)
{
    double val = chave * A;
    double frac = val - (int)val;
    return (int)(tamanho * frac);
}

void adicionarNo(No **tabela, int chave, int tamanho)
{
    int indice = hashMultiplicacao(chave, tamanho);
    char h = 'F';
    inserir(&tabela[indice], chave, &h); 
}

int buscarNo(No **tabela, int chave, int tamanho)
{
    int indice = hashMultiplicacao(chave, tamanho);
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

void embaralhar(int *vet, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int tmp = vet[i];
        vet[i] = vet[j];
        vet[j] = tmp;
    }
}

void MultiplicacaoAVL()
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

    printf("Hash Multiplicação (AVL): Chaves encontradas: %d de %d buscas\n", achadas, buscas);

    for (int i = 0; i < tamanho; i++)
        liberar(tabela[i]);
    free(tabela);
    free(valores);

    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);
}

int main()
{
    MultiplicacaoAVL();
    return 0;
}
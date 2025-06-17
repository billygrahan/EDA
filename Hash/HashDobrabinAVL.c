#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../AVL/AVL.h"

// Funções hash de dobra binária
int hashDobraE(int chave, int tamanho)
{
    int parte1 = chave & 0xFFFF;
    int parte2 = (chave >> 16) & 0xFFFF;
    int resultado = parte1 & parte2;
    return resultado & (tamanho - 1);
}

int hashDobraOU(int chave, int tamanho)
{
    int parte1 = chave & 0xFFFF;
    int parte2 = (chave >> 16) & 0xFFFF;
    int resultado = parte1 | parte2;
    return resultado & (tamanho - 1);
}

int hashDobraXOR(int chave, int tamanho)
{
    int parte1 = chave & 0xFFFF;
    int parte2 = (chave >> 16) & 0xFFFF;
    int resultado = parte1 ^ parte2;
    return resultado & (tamanho - 1);
}

// Inserção na tabela hash com AVL
void adicionarNo(No **tabela, int chave, int tamanho, int hashFunc)
{
    int indice;
    if (hashFunc == 1)
        indice = hashDobraE(chave, tamanho);
    else if (hashFunc == 2)
        indice = hashDobraOU(chave, tamanho);
    else // hashFunc == 3
        indice = hashDobraXOR(chave, tamanho);

    char h = 'F';
    inserir(&tabela[indice], chave, &h); // Usa AVL
}

// Busca na tabela hash com AVL
int buscarNo(No **tabela, int chave, int tamanho, int hashFunc)
{
    int indice;
    if (hashFunc == 1)
        indice = hashDobraE(chave, tamanho);
    else if (hashFunc == 2)
        indice = hashDobraOU(chave, tamanho);
    else // hashFunc == 3
        indice = hashDobraXOR(chave, tamanho);

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

// Teste para Hash Dobra E com AVL
void DobraE()
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
        adicionarNo(tabela, valores[i], tamanho, 1);

    int achadas = 0;
    for (int i = 0; i < buscas; i++)
    {
        int idx = rand() % n;
        if (buscarNo(tabela, valores[idx], tamanho, 1))
            achadas++;
    }

    printf("Hash Dobra E (AVL): Chaves encontradas: %d de %d buscas\n", achadas, buscas);

    for (int i = 0; i < tamanho; i++)
        liberar(tabela[i]);
    free(tabela);
    free(valores);

    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);
}

// Teste para Hash Dobra OU com AVL
void DobraOU()
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
        adicionarNo(tabela, valores[i], tamanho, 2);

    int achadas = 0;
    for (int i = 0; i < buscas; i++)
    {
        int idx = rand() % n;
        if (buscarNo(tabela, valores[idx], tamanho, 2))
            achadas++;
    }

    printf("Hash Dobra OU (AVL): Chaves encontradas: %d de %d buscas\n", achadas, buscas);

    for (int i = 0; i < tamanho; i++)
        liberar(tabela[i]);
    free(tabela);
    free(valores);

    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);
}

// Teste para Hash Dobra XOR com AVL
void DobraXOR()
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
        adicionarNo(tabela, valores[i], tamanho, 3);

    int achadas = 0;
    for (int i = 0; i < buscas; i++)
    {
        int idx = rand() % n;
        if (buscarNo(tabela, valores[idx], tamanho, 3))
            achadas++;
    }

    printf("Hash Dobra XOR (AVL): Chaves encontradas: %d de %d buscas\n", achadas, buscas);

    for (int i = 0; i < tamanho; i++)
        liberar(tabela[i]);
    free(tabela);
    free(valores);

    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);
}

// gcc -Wall -Wextra -g3 /home/billy/EDA/Hash/HashDobrabinAVL.c /home/billy/EDA/AVL/AVL.c -o /home/billy/EDA/Hash/output/HashDobrabinAVL
/// home/billy/EDA/Hash/output/HashDobrabinAVL
int main()
{
    // Descomente o(s) teste(s) que deseja rodar:
    // DobraE();
    // DobraOU();
    DobraXOR();

    return 0;
}
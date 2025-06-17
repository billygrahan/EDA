#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No
{
    int valor;
    struct No *prox;
} No;

int hashDivisao(int chave, int tamanho)
{
    return chave % tamanho;
}

void adicionarNo(No **tabela, int chave, int tamanho)
{
    int indice = hashDivisao(chave, tamanho);
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = chave;
    novoNo->prox = tabela[indice];
    tabela[indice] = novoNo;
}

int buscarNo(No **tabela, int chave, int tamanho)
{
    int indice = hashDivisao(chave, tamanho);
    No *atual = tabela[indice];
    while (atual != NULL)
    {
        if (atual->valor == chave)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

// Função para embaralhar um vetor
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

void imprimirTabela(No **tabela, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        No *atual = tabela[i];
        printf("Indice %d: ", i);
        while (atual != NULL)
        {
            printf("%d -> ", atual->valor);
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}

int main()
{
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock(); // Marca o início


    int n = 250000; // quantidade de nós a inserir
    int tamanho = 200000;
    int max_val = 2000000000;
    int colisoes = 0;

    No **tabela = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++)
        tabela[i] = NULL;

    // Gerar vetor de valores únicos para inserir
    int *valores = malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        valores[i] = (rand() % (max_val - n)) + 1 + i; // valores únicos

    embaralhar(valores, n);

    // adiciona os nós e verifica colisões
    for (int i = 0; i < n; i++)
    {
        int indice = hashDivisao(valores[i], tamanho);
        if (tabela[indice] != NULL)
            colisoes++;
        adicionarNo(tabela, valores[i], tamanho);
    }

    imprimirTabela(tabela, tamanho);

    // Buscar 1.000.000 de chaves aleatórias existentes
    int buscas = 1000000;
    int achadas = 0;
    for (int i = 0; i < buscas; i++)
    {
        int idx = rand() % n; // pega um índice de valor já inserido
        if (buscarNo(tabela, valores[idx], tamanho))
            achadas++;
    }

    printf("Chaves encontradas: %d de %d buscas\n", achadas, buscas);
    printf("Colisões: %d\n", colisoes);

    // Liberação de memória
    for (int i = 0; i < tamanho; i++)
    {
        No *atual = tabela[i];
        while (atual != NULL)
        {
            No *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }


    free(tabela);
    free(valores);

    fim = clock(); // Marca o fim
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);

    return 0;
}

// int main()
// {
//     int tamanho = 13;
//     No **tabela = (No **)malloc(tamanho * sizeof(No *));
//     for (int i = 0; i < tamanho; i++)
//     {
//         tabela[i] = NULL;
//     }

//     int chaves[] = {153, 72, 31, 11, 9, 52, 2, 84, 6, 44, 13, 27};
//     int numChaves = sizeof(chaves) / sizeof(chaves[0]);
//     for (int i = 0; i < numChaves; i++)
//     {
//         int chave = chaves[i];
//         adicionarNo(tabela, chave, tamanho);
//     }

//     imprimirTabela(tabela, tamanho);

//     free(tabela);
//     return 0;
// }
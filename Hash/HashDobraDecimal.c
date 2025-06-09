#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *prox;
} No;

int hashDobraSoma(int chave, int tamanho)
{
    int parte, soma = 0;
    int base = tamanho;
    while (chave > 0)
    {
        parte = chave % base;
        soma += parte;
        chave /= base;
    }
    return soma % tamanho;
}

void adicionarNo(No **tabela, int chave, int tamanho)
{
    int indice = hashDobraSoma(chave, tamanho);
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = chave;
    novoNo->prox = tabela[indice];
    tabela[indice] = novoNo;
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
    int tamanho = 10;
    No **tabela = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++)
    {
        tabela[i] = NULL;
    }

    int chaves[] = {153, 72, 31, 11, 9, 52, 2, 84, 6, 44, 13, 27};
    int numChaves = sizeof(chaves) / sizeof(chaves[0]);
    for (int i = 0; i < numChaves; i++)
    {
        int chave = chaves[i];
        adicionarNo(tabela, chave, tamanho);
    }

    imprimirTabela(tabela, tamanho);

    free(tabela);
    return 0;
}
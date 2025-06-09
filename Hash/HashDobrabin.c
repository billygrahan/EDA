#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *prox;
} No;

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

void adicionarNo(No **tabela, int chave, int tamanho, int hashFunc)
{
    int indice;
    if (hashFunc == 1)
        indice = hashDobraE(chave, tamanho);
    else if(hashFunc == 2)
        indice = hashDobraOU(chave, tamanho);
    else if(hashFunc == 3)
        indice = hashDobraXOR(chave, tamanho);

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
    int tamanho = 16; // potência de 2
    No **tabela_1 = (No **)malloc(tamanho * sizeof(No *));
    No **tabela_2 = (No **)malloc(tamanho * sizeof(No *));
    No **tabela_3 = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++)
    {
        tabela_1[i] = NULL;
    }

    int chaves[] = {153, 72, 31, 11, 9, 52, 2, 84, 6, 44, 13, 27};
    int numChaves = sizeof(chaves) / sizeof(chaves[0]);
    for (int i = 0; i < numChaves; i++)
    {
        int chave = chaves[i];
        adicionarNo(tabela_1, chave, tamanho, 1);
    }
    for (int i = 0; i < numChaves; i++)
    {
        int chave = chaves[i];
        adicionarNo(tabela_2, chave, tamanho, 2);
    }
    for (int i = 0; i < numChaves; i++)
    {
        int chave = chaves[i];
        adicionarNo(tabela_3, chave, tamanho, 3);
    }

    printf("Tabela com Hash Dobra E:\n");
    imprimirTabela(tabela_1, tamanho);

    printf("Tabela com Hash Dobra OU:\n");
    imprimirTabela(tabela_2, tamanho);

    printf("Tabela com Hash Dobra XOR:\n");
    imprimirTabela(tabela_3, tamanho);

    free(tabela_1);
    free(tabela_2);
    free(tabela_3);
    return 0;
}
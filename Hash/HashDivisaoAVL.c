#include <stdio.h>
#include <stdlib.h>
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
    int tamanho = 13;
    No **tabela = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++)
        tabela[i] = NULL;

    int chaves[] = {153, 72, 31, 11, 9, 52, 2, 84, 6, 44, 13, 27};
    int numChaves = sizeof(chaves) / sizeof(chaves[0]);
    for (int i = 0; i < numChaves; i++)
        adicionarNo(tabela, chaves[i], tamanho);

    imprimirTabela(tabela, tamanho);

    // Libere as AVLs
    for (int i = 0; i < tamanho; i++)
        liberar(tabela[i]);
    free(tabela);
    return 0;
}
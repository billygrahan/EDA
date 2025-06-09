#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct No
{
    int valor;
    struct No *prox;
} No;

int hashAnaliseDigitos(int chave, int numDigitos)
{
    int base = 1;
    for (int i = 0; i < numDigitos; i++)
        base *= 10;
    return chave % base;
}

void adicionarNo(No **tabela, int chave, int numDigitos, int tamanho)
{
    int indice = hashAnaliseDigitos(chave, numDigitos);
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

void calcularDesvios(No **tabela, int tamanho, int numChaves)
{
    int ni[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        ni[i] = 0;
        No *atual = tabela[i];
        while (atual != NULL)
        {
            ni[i]++;
            atual = atual->prox;
        }
    }
    double esperado = (double)numChaves / tamanho;
    double desvioQuadratico = 0;
    double desvioAbsoluto = 0;
    for (int i = 0; i < tamanho; i++)
    {
        desvioQuadratico += (ni[i] - esperado) * (ni[i] - esperado);
        desvioAbsoluto += fabs(ni[i] - esperado);
    }
    printf("Desvio quadrático: %.2lf\n", desvioQuadratico);
    printf("Desvio absoluto: %.2lf\n", desvioAbsoluto);
}

int main()
{
    int tamanho = 10;   // potência de 10
    int numDigitos = 1; // usar o último dígito
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
        adicionarNo(tabela, chave, numDigitos, tamanho);
    }

    imprimirTabela(tabela, tamanho);
    calcularDesvios(tabela, tamanho, numChaves);

    // Liberação de memória dos nós
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
    return 0;
}
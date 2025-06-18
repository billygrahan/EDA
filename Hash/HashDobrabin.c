#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No
{
    int valor;
    struct No *prox;
} No;

// dividi em 4 chaves de 8 bits, faz o AND entre elas e retorna o resultado
int hashDobraE(int chave, int tamanho)
{
    int bloco1 = (chave >> 0) & 0xFF;  // bits  0-7
    int bloco2 = (chave >> 8) & 0xFF;  // bits  8-15
    int bloco3 = (chave >> 16) & 0xFF; // bits 16-23
    int bloco4 = (chave >> 24) & 0xFF; // bits 24-31

    int resultado = bloco1 & bloco2 & bloco3 & bloco4;
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
    else if (hashFunc == 2)
        indice = hashDobraOU(chave, tamanho);
    else // hashFunc == 3
        indice = hashDobraXOR(chave, tamanho);

    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = chave;
    novoNo->prox = tabela[indice];
    tabela[indice] = novoNo;
}

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

void DobraE(){
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock();

    int n = 250000;
    int tamanho = 1 << 18; // 262144
    int max_val = 2000000000;
    int buscas = 1000000;
    int colisoes = 0;

    // Aloca tabelas para cada função hash
    No **tabelaE = (No **)malloc(tamanho * sizeof(No *));
    // No **tabelaOU = (No **)malloc(tamanho * sizeof(No *));
    // No **tabelaXOR = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++)
    {
        tabelaE[i] = NULL;
        // tabelaOU[i] = NULL;
        // tabelaXOR[i] = NULL;
    }

    // Gera valores únicos
    int *valores = malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        valores[i] = (rand() % (max_val - n)) + 1 + i;
    embaralhar(valores, n);

    // Insere nas três tabelas
    for (int i = 0; i < n; i++)
    {
        int indice = hashDobraE(valores[i], tamanho);
        if (tabelaE[indice] != NULL)
            colisoes++;
        adicionarNo(tabelaE, valores[i], tamanho, 1);
    }

    imprimirTabela(tabelaE, tamanho);

    // Busca 1.000.000 de chaves aleatórias existentes em cada tabela
    int achadasE = 0, achadasOU = 0, achadasXOR = 0;
    for (int i = 0; i < buscas; i++)
    {
        int idx = rand() % n;
        if (buscarNo(tabelaE, valores[idx], tamanho, 1))
            achadasE++;
        // if (buscarNo(tabelaOU, valores[idx], tamanho, 2))
        //     achadasOU++;
        // if (buscarNo(tabelaXOR, valores[idx], tamanho, 3))
        //     achadasXOR++;
    }

    printf("Hash Dobra E:   Chaves encontradas: %d de %d buscas\n", achadasE, buscas);
    printf("Colisões: %d\n", colisoes);

    // Liberação de memória
    for (int i = 0; i < tamanho; i++)
    {
        No *atual;
        while ((atual = tabelaE[i]) != NULL)
        {
            tabelaE[i] = atual->prox;
            free(atual);
        }
    }

    free(tabelaE);
    free(valores);

    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);
}

void DobraOU()
{
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock();

    int n = 250000;
    int tamanho = 1 << 18; // 262144
    int max_val = 2000000000;
    int buscas = 1000000;
    int colisoes = 0;

    // Aloca tabelas para cada função hash
    No **tabelaOU = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++)
    {
        tabelaOU[i] = NULL;
        // tabelaXOR[i] = NULL;
    }

    // Gera valores únicos
    int *valores = malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        valores[i] = (rand() % (max_val - n)) + 1 + i;
    embaralhar(valores, n);

    // Insere nas três tabelas
    for (int i = 0; i < n; i++)
    {
        int indice = hashDobraOU(valores[i], tamanho);
        if (tabelaOU[indice] != NULL)
            colisoes++;
        adicionarNo(tabelaOU, valores[i], tamanho, 2);
    }

    imprimirTabela(tabelaOU, tamanho);

    // Busca 1.000.000 de chaves aleatórias existentes em cada tabela
    int achadasE = 0, achadasOU = 0, achadasXOR = 0;
    for (int i = 0; i < buscas; i++)
    {
        int idx = rand() % n;
        if (buscarNo(tabelaOU, valores[idx], tamanho, 2))
            achadasOU++;
        // if (buscarNo(tabelaXOR, valores[idx], tamanho, 3))
        //     achadasXOR++;
    }

    printf("Hash Dobra OU:  Chaves encontradas: %d de %d buscas\n", achadasOU, buscas);
    printf("Colisões: %d\n", colisoes);

    // Liberação de memória
    for (int i = 0; i < tamanho; i++)
    {
        No *atual;
        while ((atual = tabelaOU[i]) != NULL)
        {
            tabelaOU[i] = atual->prox;
            free(atual);
        }
        // while ((atual = tabelaXOR[i]) != NULL)
        // {
        //     tabelaXOR[i] = atual->prox;
        //     free(atual);
        // }
    }
    free(tabelaOU);
    // free(tabelaXOR);
    free(valores);

    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);
}

void DobraXOR()
{
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock();

    int n = 250000;
    int tamanho = 1 << 18;
    int max_val = 2000000000;
    int buscas = 1000000;
    int colisoes = 0;

    // Aloca tabelas para cada função hash
    No **tabelaXOR = (No **)malloc(tamanho * sizeof(No *));
    for (int i = 0; i < tamanho; i++)
    {
        tabelaXOR[i] = NULL;
    }

    // Gera valores únicos
    int *valores = malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        valores[i] = (rand() % (max_val - n)) + 1 + i;
    embaralhar(valores, n);

    // Insere nas três tabelas
    for (int i = 0; i < n; i++)
    {
        int indice = hashDobraXOR(valores[i], tamanho);
        if (tabelaXOR[indice] != NULL)
            colisoes++;
        adicionarNo(tabelaXOR, valores[i], tamanho, 3);
    }

    imprimirTabela(tabelaXOR, tamanho);

    // Busca 1.000.000 de chaves aleatórias existentes em cada tabela
    int achadasE = 0, achadasOU = 0, achadasXOR = 0;
    for (int i = 0; i < buscas; i++)
    {
        int idx = rand() % n;
        if (buscarNo(tabelaXOR, valores[idx], tamanho, 3))
            achadasXOR++;
    }

    printf("Hash Dobra XOR: Chaves encontradas: %d de %d buscas\n", achadasXOR, buscas);
    printf("Colisões: %d\n", colisoes);

    // Liberação de memória
    for (int i = 0; i < tamanho; i++)
    {
        No *atual;
        while ((atual = tabelaXOR[i]) != NULL)
        {
            tabelaXOR[i] = atual->prox;
            free(atual);
        }
    }

    free(tabelaXOR);
    free(valores);

    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);
}

// gcc -Wall -Wextra -g3 /home/billy/EDA/Hash/HashDobrabin.c -o /home/billy/EDA/Hash/output/HashDobrabin
// mkdir -p /home/billy/EDA/Hash/output
// /home/billy/EDA/Hash/output/HashDobrabin
int main()
{
    //DobraE();
    //DobraOU();
    DobraXOR();

    return 0;
}

// int main()
// {
//         int tamanho = 16; // potência de 2
//         No **tabela_1 = (No **)malloc(tamanho * sizeof(No *));
//         No **tabela_2 = (No **)malloc(tamanho * sizeof(No *));
//         No **tabela_3 = (No **)malloc(tamanho * sizeof(No *));
//         for (int i = 0; i < tamanho; i++)
//         {
//                 tabela_1[i] = NULL;
//             }
        
//             int chaves[] = {153, 72, 31, 11, 9, 52, 2, 84, 6, 44, 13, 27};
//             int numChaves = sizeof(chaves) / sizeof(chaves[0]);
//             for (int i = 0; i < numChaves; i++)
//             {
//                     int chave = chaves[i];
//                     adicionarNo(tabela_1, chave, tamanho, 1);
//                 }
//                 for (int i = 0; i < numChaves; i++)
//                 {
//                         int chave = chaves[i];
//                         adicionarNo(tabela_2, chave, tamanho, 2);
//                     }
//                     for (int i = 0; i < numChaves; i++)
//                     {
//                             int chave = chaves[i];
//                             adicionarNo(tabela_3, chave, tamanho, 3);
//                         }
                    
//                         printf("Tabela com Hash Dobra E:\n");
//                         imprimirTabela(tabela_1, tamanho);
                    
//                         printf("Tabela com Hash Dobra OU:\n");
//                         imprimirTabela(tabela_2, tamanho);
                    
//                         printf("Tabela com Hash Dobra XOR:\n");
//                         imprimirTabela(tabela_3, tamanho);
                    
//                         free(tabela_1);
//                         free(tabela_2);
//                         free(tabela_3);
//                         return 0;
//                     }
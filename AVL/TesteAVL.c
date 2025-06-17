#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../AVL/AVL.h"

// gcc -Wall -Wextra -g3 /home/billy/EDA/AVL/TesteAVL.c /home/billy/EDA/AVL/AVL.c -o /home/billy/EDA/AVL/output/TesteAVL
/// home/billy/EDA/AVL/output/TesteAVL
int main()
{
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock(); // Marca o início

    int num_inserir = 10000;
    int num_remover = 1000;
    int max_val = 100000;

    No *raiz = NULL;
    char h;

    // 1. Gerar vetor de valores únicos para inserir
    int *valores = malloc(max_val * sizeof(int));
    for (int i = 0; i < max_val; i++)
        valores[i] = i + 1;
    srand(time(NULL));
    embaralhar(valores, max_val);

    // 2. Inserir os 10000 primeiros valores embaralhados
    for (int i = 0; i < num_inserir; i++)
        inserir(&raiz, valores[i], &h);

    // 3. Verificar se é AVL
    if (arvoreEhAVL(raiz))
        printf("Após inserção: A árvore está balanceada (AVL).\n");
    else
        printf("Após inserção: A árvore NÃO está balanceada!\n");

    // 4. Remover 1000 valores aleatórios dos já inseridos
    embaralhar(valores, num_inserir); // embaralha os 10000 inseridos
    char is_modified_heigth;
    for (int i = 0; i < num_remover; i++)
        removeAVL(valores[i], &raiz, &is_modified_heigth);

    // 5. Verificar se restaram 9000 nós
    int total = contar_nos(raiz);
    printf("Após remoção: A árvore possui %d nós (esperado: 9000).\n", total);

    // 6. Verificar novamente se é AVL
    if (arvoreEhAVL(raiz))
        printf("Após remoção: A árvore está balanceada (AVL).\n");
    else
        printf("Após remoção: A árvore NÃO está balanceada!\n");

    // Libera memória
    liberar(raiz);
    free(valores);

    fim = clock(); // Marca o fim
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.4f segundos\n", tempo_gasto);
    
    return 0;
}
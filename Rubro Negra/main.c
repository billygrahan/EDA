#include <stdio.h>
#include <stdlib.h>
#include "RB.h"

// gcc -Wall -Wextra -g3 main.c RB.c -o output/RBTest
// ./output/RBTest
int main()
{

    // cria uma rubro negra adicionando 10.000 números aleatórios e remove 343 deles
    // por algum motivi quando tento remover o 344º número, o programa trava Segmentation Fault
    RB_test(10000, 343);


    // cria 1000 Rubro Negras com 10.000 números e 0 remoções
    // for (int i = 0; i < 1000; i++)
    // {
    //     RB_test(10000, 0);
    // }

    return 0;
}

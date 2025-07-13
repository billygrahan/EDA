#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void rotate_insert(Node *z, Node **root, Node *external)
{
    while (z->pai->color == RED)
    {
        if (z->pai == z->pai->pai->esq)
        {
            Node *y = z->pai->pai->dir;
            if (y->color == RED)
            {
                z->pai->color = BLACK;
                y->color = BLACK;
                z->pai->pai->color = RED;
                z = z->pai->pai;
            }
            else
            {
                if (z == z->pai->dir)
                {
                    z = z->pai;
                    left_rotate(z, &(*root), external);
                }
                z->pai->color = BLACK;
                z->pai->pai->color = RED;
                right_rotate(z->pai->pai, &(*root), external);
            }
        }
        else
        {
            Node *y = z->pai->pai->esq;
            if (y->color == RED)
            {
                z->pai->color = BLACK;
                y->color = BLACK;
                z->pai->pai->color = RED;
                z = z->pai->pai;
            }
            else
            {
                if (z == z->pai->esq)
                {
                    z = z->pai;
                    right_rotate(z, &(*root), external);
                }
                z->pai->pai->color = RED;
                z->pai->color = BLACK;
                left_rotate(z->pai->pai, &(*root), external);
            }
        }
    }
    (*root)->color = BLACK;
}

void left_rotate(Node *x, Node **root, Node *external)
{
    Node *y = x->dir;
    x->dir = y->esq;
    if (y->esq != external)
        y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == external)
        *root = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

void right_rotate(Node *x, Node **root, Node *external)
{
    Node *y = x->esq;
    x->esq = y->dir;
    if (y->dir != external)
        y->dir->pai = x;

    y->pai = x->pai;

    if (x->pai == external)
        *root = y;
    else if (x == x->pai->dir)
        x->pai->dir = y;
    else
        x->pai->esq = y;
    y->dir = x;
    x->pai = y;
}

Node *create_external()
{
    Node *external = calloc(1, sizeof(Node));
    external->color = BLACK;
    external->pai = NULL;
    external->esq = NULL;
    external->dir = NULL;
    external->value = 0;

    return external;
}

Node *create_node(int value, Node *external)
{
    Node *node = calloc(1, sizeof(Node));
    node->esq = external;
    node->dir = external;
    node->pai = external;
    node->value = value;
    node->color = RED;

    return node;
}

void insert_RB(int value, Node **root, Node *external)
{
    Node *y = external, *x = *root;

    while (x != external)
    {
        y = x;
        if (value == x->value)
        {
            y = NULL;
            x = external;
        }
        else if (value < x->value)
            x = x->esq;
        else
            x = x->dir;
    }
    if (y != NULL)
    {
        Node *z = create_node(value, external);
        z->pai = y;
        if (y == external)
            *root = z;
        else if (z->value < y->value)
            y->esq = z;
        else
            y->dir = z;
        rotate_insert(z, &(*root), external);
    }
}

void pre_order(Node *root, Node *external)
{
    if (root != external)
    {
        if (root->color == RED)
            printf("\033[1;31m%d\033[0m\n", root->value);
        else
            printf("\033[1;30m%d\033[0m\n", root->value);
    }
    if (root->esq != external)
        pre_order(root->esq, external);
    if (root->dir != external)
        pre_order(root->dir, external);
}

int count_nodes(Node *root, Node *external, int *nodes)
{
    if (root->esq != external)
        count_nodes(root->esq, external, nodes);

    if (root->dir != external)
        count_nodes(root->dir, external, nodes);

    *nodes = *nodes + 1;
    return *nodes;
}

void fill_vector(int *vector, int size)
{

    int i, j;
    for (i = 0, j = 0; i < size; i++, j += (rand() % 100) + 1)
    {
        vector[i] = j;
    }
}



void free_RB(Node **root, Node *external)
{
    if ((*root)->esq != external)
        free_RB(&(*root)->esq, external);
    if ((*root)->dir != external)
        free_RB(&(*root)->dir, external);

    free(*root);
}

void move_pai(Node *u, Node *v, Node **root, Node *external)
{
    if (u->pai == external)
        (*root) = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    v->pai = u->pai;
}

void remove_node(int value, Node **root, Node *external)
{
    Node *z = search(value, *root, external);
    if (z != external)
    {
        Node *y = z;
        Node *x;
        Color old_color = y->color;
        if (z->esq == external)
        {
            x = z->dir;
            move_pai(z, z->dir, &(*root), external);
        }
        else if (z->dir == external)
        {
            x = z->esq;
            move_pai(z, z->esq, &(*root), external);
        }
        else
        {
            y = successor(z->dir, external);
            old_color = y->color;
            x = y->dir;

            if (y->pai == z)
                x->pai = y;
            else
            {
                move_pai(y, y->dir, &(*root), external);

                y->dir = z->dir;
                y->dir->pai = y;
            }

            move_pai(z, y, &(*root), external);
            y->esq = z->esq;
            y->esq->pai = y;
            y->color = z->color;
        }

        if (old_color == BLACK)
            rotate_remove(x, root, external);

        free(z);
    }
    else
        puts("Value not found");
}

Node *successor(Node *z, Node *external)
{
    Node *aux = z;
    while (aux->esq != external)
    {
        aux = aux->esq;
    }
    return aux;
}

Node *search(int value, Node *root, Node *external)
{
    while (root != external)
    {
        if (value < root->value)
            root = root->esq;
        else if (value > root->value)
            root = root->dir;
        else
            return root;
    }
    return external;
}

void rotate_remove(Node *x, Node **root, Node *external)
{
    Node *w = NULL;
    while (x != (*root) && x->color == BLACK)
    {
        if (x->pai->esq == x)
        {
            w = x->pai->dir;

            if (w->color == RED)
            {
                w->color = BLACK;
                x->pai->color = RED;
                left_rotate(x->pai, &(*root), external);
                w = x->pai->dir;
            }
            if (w->esq->color == BLACK && w->dir->color == BLACK)
            {
                w->color = RED;
                x = x->pai;
            }
            else
            {
                if (w->dir->color == BLACK)
                {
                    w->esq->color = BLACK;
                    w->color = RED;
                    right_rotate(w, &(*root), external);
                    w = x->pai->dir;
                }
                w->color = x->pai->color;
                x->pai->color = BLACK;
                w->dir->color = BLACK;
                left_rotate(x->pai, &(*root), external);
                x = (*root);
            }
        }
        else
        {
            w = x->pai->esq;

            if (w->color == RED)
            {
                w->color = BLACK;
                x->pai->color = RED;
                right_rotate(x->pai, &(*root), external);
                w = x->pai->esq;
            }
            if (w->dir->color == BLACK && w->esq->color == BLACK)
            {
                w->color = RED;
                x = x->pai;
            }
            else
            {
                if (w->esq->color == BLACK)
                {
                    w->dir->color = BLACK;
                    w->color = RED;
                    left_rotate(w, &(*root), external);
                    w = x->pai->esq;
                }
                w->color = x->pai->color;
                x->pai->color = BLACK;
                w->esq->color = BLACK;
                right_rotate(x->pai, &(*root), external);
                x = (*root);
            }
        }
    }
    (*root)->color = BLACK;
}

int black_height(Node *root, Node *external)
{
    if (root == external)
        return 0;

    int hl = black_height(root->esq, external);
    int hr = black_height(root->dir, external);

    if (root->color == BLACK)
        return (hl > hr ? hl : hr) + 1;
    else
        return hl > hr ? hl : hr;
}

bool He_RB(Node *root, Node *external)
{
    if (root == external)
        return true;

    int black_height_esq = black_height(root->esq, external);
    int black_height_dir = black_height(root->dir, external);

    return black_height_esq == black_height_dir;
}

void embaralhar(int *v, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }
}

void RB_test(int n, int y)
{
    Node *external = create_external();
    Node *root = external;

    // Prepara vetor de valores únicos e embaralha
    int *valores = malloc(n * sizeof(int));
    fill_vector(valores, n);
    embaralhar(valores, n);

    // Inserção
    for (int i = 0; i < n; i++)
        insert_RB(valores[i], &root, external);

    // Verificações após inserção
    int nodes = 0;
    count_nodes(root, external, &nodes);
    printf("Após inserção: nós = %d, esperado = %d\n", nodes, n);
    if (nodes == n)
        printf("Contagem de nós OK\n");
    else
        printf("Contagem de nós ERRADA\n");

    if (He_RB(root, external))
        printf("Árvore é rubro-negra após inserção: OK\n");
    else
        printf("Árvore NÃO é rubro-negra após inserção!\n");

    // Remoção dos y primeiros valores inseridos
    //printf("Removendo valores...\n");
    for (int i = 0; i < y; i++)
        remove_node(valores[i], &root, external);
    //printf("Remoção concluída.\n");

    // Verificações após remoção
    nodes = 0;
    count_nodes(root, external, &nodes);
    printf("Após remoção: nós = %d, esperado = %d\n", nodes, n - y);
    if (nodes == n - y)
        printf("Contagem de nós OK\n");
    else
        printf("Contagem de nós ERRADA\n");

    if (He_RB(root, external))
        printf("Árvore é rubro-negra após remoção: OK\n");
    else
        printf("Árvore NÃO é rubro-negra após remoção!\n");

    free(valores);
    free_RB(&root, external);
    free(external);
}

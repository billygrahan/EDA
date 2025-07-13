#include <stdbool.h>

typedef enum
{
    RED,
    BLACK

} Color;

typedef struct Node
{
    int value;
    struct Node *pai;
    struct Node *esq;
    struct Node *dir;
    Color color;
} Node;

// ------------------------- Funções de Inserção -------------------------------
void insert_RB(int value, Node **root, Node *external);
void rotate_insert(Node *z, Node **root, Node *external);

// ------------------------------- Funções de Remoção -------------------------------
void remove_node(int value, Node **root, Node *external);
void move_pai(Node *u, Node *v, Node **root, Node *external);
void rotate_remove(Node *x, Node **root, Node *external);



void left_rotate(Node *x, Node **root, Node *external);
void right_rotate(Node *x, Node **root, Node *external);

// ------------------------------- Funções Auxiliares -------------------------------
Node *successor(Node *z, Node *external);
Node *search(int value, Node *root, Node *external);
int count_nodes(Node *root, Node *external, int *nodes);
void free_RB(Node **root, Node *external);
void fill_vector(int *vector, int size);
Node *create_external();
Node *create_node(int value, Node *external);
void embaralhar(int *v, int n);

// ------------------------------- Funções de Validação -------------------------------
int black_height(Node *root, Node *external);
bool He_RB(Node *root, Node *external);

// Teste
void RB_test(int n, int y);

// ------------------------------- Função de Impressão -------------------------------
void pre_order(Node *root, Node *external);
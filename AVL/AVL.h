#ifndef AVL_h
#define AVL_h
typedef struct No
{
    int bal;
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No *Criar_No(int value);
void rotate_esq(No **pt, char *h);
void rotate_dir(No **pt, char *h);
void inserir(No **pt, int value, char *h);
int verificaAVL(No *raiz, int *ok);
void removeAVL(int value, No **pt, char *is_modified);
int arvoreEhAVL(No *raiz);
void rotate_esq_remove(No **pt, char *is_modified);
void rotate_dir_remove(No **pt, char *is_modified);
void swap(No **pt, No **pt2);
void balance(No **pt, char where, char *is_modified);
int contar_nos(No *raiz);
void embaralhar(int *v, int n);
void print_inordem(No *raiz);
int altura(No *raiz);
void liberar(No *raiz);


#endif
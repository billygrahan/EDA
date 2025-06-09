#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No
{
    int bal;
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No *Criar_No(int value)
{
    No *no = malloc(sizeof(No));
    no->esq = NULL;
    no->dir = NULL;
    no->valor = value;
    no->bal = 0;
    return no;
}

// ------------------------ inserir ------------------------
// Rotação simples à esquerda e direita
void rotate_esq(No **pt, char *h) {
    No *ptu = (*pt)->esq;
    if (ptu->bal == -1) {
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        (*pt)->dir->bal = 0;
    } else {
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);

        if (ptv->bal == 1) {
            (*pt)->bal = 0;
            ptu->bal = -1;
        } else if (ptv->bal == 0) {
            (*pt)->bal = 0;
            ptu->bal = 0;
        } else { 
            (*pt)->bal = 1;
            ptu->bal = 0;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = 'F';
}



void rotate_dir(No **pt, char *h) {
    No *ptu = (*pt)->dir;
    if (ptu->bal == 1) {
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;
        (*pt)->esq->bal = 0;
    } else {
        No *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);

        if (ptv->bal == -1) {
            (*pt)->bal = 0;
            ptu->bal = 1;
        } else if (ptv->bal == 0) {
            (*pt)->bal = 0;
            ptu->bal = 0;
        } else { 
            (*pt)->bal = -1;
            ptu->bal = 0;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = 'F';
}

// ------------------------ inserir ------------------------
int inserir(No **pt, int value, char *h) {
    if (*pt == NULL) {
        *pt = Criar_No(value);
        *h = 'V';
        return 1;
    }
    else{
        if (value == (*pt)->valor)
        {
            return 0;
        }
        if (value < (*pt)->valor)
        {
            inserir(&(*pt)->esq, value, h);
            if (*h == 'V')
            {
                switch ((*pt)->bal)
                {
                case 1:
                    (*pt)->bal = 0;
                    *h = 'F';
                    break;
                case 0:
                    (*pt)->bal = -1;
                    *h = 'V';
                    break;
                case -1:
                    rotate_esq(pt, h);
                    break;
                }
            }
        }
        else
        {
            inserir(&(*pt)->dir, value, h);
            if (*h == 'V')
            {
                switch ((*pt)->bal)
                {
                case -1:
                    (*pt)->bal = 0;
                    *h = 'F';
                    break;
                case 0:
                    (*pt)->bal = 1;
                    *h = 'V';
                    break;
                case 1:
                    rotate_dir(pt, h);
                    break;
                }
            }
        }
        return 1;
    }
    
}



// Função auxiliar para verificar AVL e calcular altura
int verificaAVL(No *raiz, int *ok)
{
    if (raiz == NULL)
        return 0;
    int alt_esq = verificaAVL(raiz->esq, ok);
    int alt_dir = verificaAVL(raiz->dir, ok);
    int bal_calc = alt_dir - alt_esq;
    if (bal_calc < -1 || bal_calc > 1)
        *ok = 0;
    if (raiz->bal != bal_calc)
        *ok = 0;
    return (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
}

// Função principal para chamar a verificação
int arvoreEhAVL(No *raiz)
{
    int ok = 1;
    verificaAVL(raiz, &ok);
    return ok;
}

int altura(No *raiz)
{
    if (raiz == NULL)
        return 0;
    int alt_esq = altura(raiz->esq);
    int alt_dir = altura(raiz->dir);
    return (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
}


void print_inordem(No *raiz) {
    if (raiz == NULL) return;
    print_inordem(raiz->esq);
    printf("%d ", raiz->valor);
    print_inordem(raiz->dir);
}

void rotate_esq_remove(No **pt, char *is_modified_heigth)
{
    if (*pt == NULL || (*pt)->esq == NULL)
    {
        return;
    }
    No *ptu = (*pt)->esq;

    if (ptu->bal <= 0)
    {
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        if (ptu->bal == -1)
        {
            ptu->bal = (*pt)->dir->bal = 0;
            *is_modified_heigth = 'V';
        }
        else
        {
            ptu->bal = 1;
            (*pt)->dir->bal = -1;
            *is_modified_heigth = 'F';
        }
    }
    else
    {
        No *ptv = ptu->dir;

        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);
        (*pt) = ptv;
        switch (ptv->bal)
        {
        case -1:
            ptu->bal = 0;
            (*pt)->dir->bal = 1;
            break;
        case 0:
            ptu->bal = 0;
            (*pt)->dir->bal = 0;
            break;
        case 1:
            ptu->bal = -1;
            (*pt)->dir->bal = 0;
            break;
        }
        (*pt)->bal = 0;
        *is_modified_heigth = 'V';
    }
}

void rotate_dir_remove(No **pt, char *is_modified_heigth)
{
    if (*pt == NULL || (*pt)->dir == NULL)
    {
        return;
    }

    No *ptu = (*pt)->dir;

    if (ptu->bal >= 0)
    {
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;

        if (ptu->bal == 1)
        {
            (*pt)->esq->bal = 0;
            (*pt)->bal = 0;
            *is_modified_heigth = 'V';
        }
        else
        {
            (*pt)->esq->bal = 1;
            (*pt)->bal = -1;
            *is_modified_heigth = 'F';
        }
    }
    else
    {
        No *ptv = ptu->esq;

        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);
        (*pt) = ptv;

        switch (ptv->bal)
        {
        case -1:
            (*pt)->esq->bal = 0;
            ptu->bal = 1;
            break;
        case 0:
            (*pt)->esq->bal = 0;
            ptu->bal = 0;
            break;
        case 1:
            (*pt)->esq->bal = -1;
            ptu->bal = 0;
            break;
        }
        (*pt)->bal = 0;
        *is_modified_heigth = 'V';
    }
}

void balance(No **pt, char where, char *is_modified_heigth)
{
    if (*is_modified_heigth == 'V')
    {
        if (where == 'R')
        {
            switch ((*pt)->bal)
            {
            case 1:
                (*pt)->bal = 0;
                break;
            case 0:
                (*pt)->bal = -1;
                *is_modified_heigth = 'F';
                break;
            case -1:
                rotate_esq_remove(pt, is_modified_heigth);
                break;
            }
        }
        else
        {
            switch ((*pt)->bal)
            {
            case -1:
                (*pt)->bal = 0;
                break;
            case 0:
                (*pt)->bal = 1;
                *is_modified_heigth = 'F';
                break;
            case 1:
                rotate_dir_remove(pt, is_modified_heigth);
                break;
            }
        }
    }
}

void swap(No **pt, No **fatherS)
{
    if (*pt == NULL || *fatherS == NULL)
    {
        return;
    }

    // Troca os nós completos, incluindo seus filhos e fatores de balanceamento
    No *temp = *pt;
    *pt = *fatherS;
    *fatherS = temp;

    // Ajusta os filhos para manter a estrutura da árvore consistente
    No *tempesq = (*pt)->esq;
    No *tempRight = (*pt)->dir;

    (*pt)->esq = (*fatherS)->esq;
    (*pt)->dir = (*fatherS)->dir;

    (*fatherS)->esq = tempesq;
    (*fatherS)->dir = tempRight;
}

void removeAVL(int value, No **pt, char *is_modified_heigth)
{
    if ((*pt) == NULL)
    {
        puts("element does not exists");
        *is_modified_heigth = 'F';
    }
    else
    {
        if (value < (*pt)->valor)
        {
            removeAVL(value, &(*pt)->esq, is_modified_heigth);
            balance(pt, 'L', is_modified_heigth);
        }
        else
        {
            if (value > (*pt)->valor)
            {
                removeAVL(value, &(*pt)->dir, is_modified_heigth);
                balance(pt, 'R', is_modified_heigth);
            }
            else
            {
                No *aux = (*pt);

                if ((*pt)->esq == NULL)
                {
                    (*pt) = (*pt)->dir;
                    *is_modified_heigth = 'V';
                }
                else
                {
                    if ((*pt)->dir == NULL)
                    {
                        (*pt) = (*pt)->esq;
                        *is_modified_heigth = 'V';
                    }
                    else
                    {
                        No *s = (*pt)->dir;

                        if (s->esq == NULL)
                        {
                            s->esq = (*pt)->esq;
                            s->bal = (*pt)->bal;
                            (*pt) = s;
                            *is_modified_heigth = 'V';
                        }
                        else
                        {
                            No *fatherS;
                            while (s->esq != NULL)
                            {
                                fatherS = s;
                                s = s->esq;
                            }
                            swap(pt, &fatherS->esq);
                            removeAVL(value, &(*pt)->dir, is_modified_heigth);
                        }
                        balance(pt, 'R', is_modified_heigth);
                    }
                    free(aux);
                }
            }
        }
    }
}

int contar_nos(No *raiz)
{
    if (raiz == NULL)
        return 0;
    return 1 + contar_nos(raiz->esq) + contar_nos(raiz->dir);
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

void liberar(No *raiz)
{
    if (raiz == NULL)
        return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
}
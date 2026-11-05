#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

static int altura_no(const NoAVL *n) { return n ? n->altura : 0; }
static int maior(int a, int b)       { return a > b ? a : b; }

static void atualizar(NoAVL *n)
{
    n->altura = 1 + maior(altura_no(n->esq), altura_no(n->dir));
}

static NoAVL *rot_dir(AVL *t, NoAVL *y)
{
    NoAVL *x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    atualizar(y);
    atualizar(x);
    t->rotacoes++;
    return x;
}

static NoAVL *rot_esq(AVL *t, NoAVL *x)
{
    NoAVL *y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    atualizar(x);
    atualizar(y);
    t->rotacoes++;
    return y;
}

static NoAVL *inserir_no(AVL *t, NoAVL *no, const Registro *r, int *inseriu)
{
    if (!no) {
        NoAVL *n = malloc(sizeof *n);
        if (!n) { fprintf(stderr, "avl: sem memoria\n"); exit(1); }
        n->reg = r; n->esq = n->dir = NULL; n->altura = 1;
        *inseriu = 1;
        return n;
    }

    t->comparacoes++;
    if (r->id < no->reg->id)      no->esq = inserir_no(t, no->esq, r, inseriu);
    else if (r->id > no->reg->id) no->dir = inserir_no(t, no->dir, r, inseriu);
    else return no;                                   /* id repetido */

    atualizar(no);
    int fb = altura_no(no->esq) - altura_no(no->dir);

    if (fb > 1) {                                     /* pesado a esquerda */
        if (altura_no(no->esq->esq) < altura_no(no->esq->dir))
            no->esq = rot_esq(t, no->esq);            /* caso esquerda-direita */
        return rot_dir(t, no);
    }
    if (fb < -1) {                                    /* pesado a direita */
        if (altura_no(no->dir->dir) < altura_no(no->dir->esq))
            no->dir = rot_dir(t, no->dir);            /* caso direita-esquerda */
        return rot_esq(t, no);
    }
    return no;
}

void avl_init(AVL *t)
{
    t->raiz = NULL; t->tamanho = 0; t->comparacoes = 0; t->rotacoes = 0;
}

int avl_inserir(AVL *t, const Registro *r)
{
    int inseriu = 0;
    t->raiz = inserir_no(t, t->raiz, r, &inseriu);
    if (inseriu) t->tamanho++;
    return inseriu;
}

const Registro *avl_buscar(AVL *t, int id)
{
    NoAVL *n = t->raiz;
    while (n) {
        t->comparacoes++;
        if (id == n->reg->id) return n->reg;
        n = (id < n->reg->id) ? n->esq : n->dir;
    }
    return NULL;
}

int avl_altura(const AVL *t) { return altura_no(t->raiz); }

static void liberar_no(NoAVL *n)
{
    if (!n) return;
    liberar_no(n->esq);
    liberar_no(n->dir);
    free(n);
}

void avl_liberar(AVL *t)
{
    liberar_no(t->raiz);
    t->raiz = NULL; t->tamanho = 0;
}

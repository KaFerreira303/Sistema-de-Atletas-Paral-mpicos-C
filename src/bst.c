#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

static void rot_esq(ArvoreRB *t, NoRB *x)
{
    NoRB *y = x->dir;
    x->dir = y->esq;
    if (y->esq != t->nil) y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == t->nil)       t->raiz = y;
    else if (x == x->pai->esq)  x->pai->esq = y;
    else                        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
    t->rotacoes++;
}

static void rot_dir(ArvoreRB *t, NoRB *x)
{
    NoRB *y = x->esq;
    x->esq = y->dir;
    if (y->dir != t->nil) y->dir->pai = x;
    y->pai = x->pai;
    if (x->pai == t->nil)       t->raiz = y;
    else if (x == x->pai->dir)  x->pai->dir = y;
    else                        x->pai->esq = y;
    y->dir = x;
    x->pai = y;
    t->rotacoes++;
}

static void corrigir_insercao(ArvoreRB *t, NoRB *z)
{
    while (z->pai->cor == VERMELHO) {
        NoRB *avo = z->pai->pai;
        if (z->pai == avo->esq) {
            NoRB *tio = avo->dir;
            if (tio->cor == VERMELHO) {               /* caso 1: recolorir */
                z->pai->cor = PRETO;
                tio->cor    = PRETO;
                avo->cor    = VERMELHO;
                z = avo;
            } else {
                if (z == z->pai->dir) {               /* caso 2: vira caso 3 */
                    z = z->pai;
                    rot_esq(t, z);
                }
                z->pai->cor      = PRETO;             /* caso 3 */
                z->pai->pai->cor = VERMELHO;
                rot_dir(t, z->pai->pai);
            }
        } else {
            NoRB *tio = avo->esq;
            if (tio->cor == VERMELHO) {
                z->pai->cor = PRETO;
                tio->cor    = PRETO;
                avo->cor    = VERMELHO;
                z = avo;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rot_dir(t, z);
                }
                z->pai->cor      = PRETO;
                z->pai->pai->cor = VERMELHO;
                rot_esq(t, z->pai->pai);
            }
        }
    }
    t->raiz->cor = PRETO;
}

void rb_init(ArvoreRB *t)
{
    t->nil = calloc(1, sizeof *t->nil);
    if (!t->nil) { fprintf(stderr, "rb: sem memoria\n"); exit(1); }
    t->nil->cor = PRETO;
    t->nil->esq = t->nil->dir = t->nil->pai = t->nil;
    t->raiz = t->nil;
    t->tamanho = 0; t->comparacoes = 0; t->rotacoes = 0;
}

int rb_inserir(ArvoreRB *t, const Registro *r)
{
    NoRB *y = t->nil, *x = t->raiz;
    while (x != t->nil) {
        y = x;
        t->comparacoes++;
        if (r->id < x->reg->id)      x = x->esq;
        else if (r->id > x->reg->id) x = x->dir;
        else return 0;                                /* id repetido */
    }

    NoRB *z = malloc(sizeof *z);
    if (!z) { fprintf(stderr, "rb: sem memoria\n"); exit(1); }
    z->reg = r; z->cor = VERMELHO;
    z->esq = z->dir = t->nil;
    z->pai = y;

    if (y == t->nil)              t->raiz = z;
    else if (r->id < y->reg->id)  y->esq = z;
    else                          y->dir = z;

    t->tamanho++;
    corrigir_insercao(t, z);
    return 1;
}

const Registro *rb_buscar(ArvoreRB *t, int id)
{
    NoRB *n = t->raiz;
    while (n != t->nil) {
        t->comparacoes++;
        if (id == n->reg->id) return n->reg;
        n = (id < n->reg->id) ? n->esq : n->dir;
    }
    return NULL;
}

static int altura_no(const ArvoreRB *t, const NoRB *n)
{
    if (n == t->nil) return 0;
    int e = altura_no(t, n->esq), d = altura_no(t, n->dir);
    return 1 + (e > d ? e : d);
}

int rb_altura(const ArvoreRB *t) { return altura_no(t, t->raiz); }

static void liberar_no(ArvoreRB *t, NoRB *n)
{
    if (n == t->nil) return;
    liberar_no(t, n->esq);
    liberar_no(t, n->dir);
    free(n);
}

void rb_liberar(ArvoreRB *t)
{
    liberar_no(t, t->raiz);
    free(t->nil);
    t->nil = t->raiz = NULL;
    t->tamanho = 0;
}

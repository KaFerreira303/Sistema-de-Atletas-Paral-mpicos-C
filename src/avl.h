#ifndef AVL_H
#define AVL_H

#include "registro.h"

typedef struct NoAVL {
    const Registro *reg;
    struct NoAVL   *esq, *dir;
    int             altura;      /* altura do no (folha = 1) */
} NoAVL;

typedef struct {
    NoAVL *raiz;
    int    tamanho;
    long   comparacoes;          /* nos visitados em insercoes/buscas */
    long   rotacoes;             /* rotacoes simples (dupla = 2) */
} AVL;

void           avl_init(AVL *t);
int            avl_inserir(AVL *t, const Registro *r);  /* 1 = inseriu, 0 = id repetido */
const Registro *avl_buscar(AVL *t, int id);             /* NULL se nao achar */
int            avl_altura(const AVL *t);
void           avl_liberar(AVL *t);

#endif

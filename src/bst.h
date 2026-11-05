#ifndef BST_H
#define BST_H

/* Arvore de busca binaria balanceada do tipo RUBRO-NEGRA.
 * (Os arquivos se chamam bst.* conforme a estrutura do repositorio.) */

#include "registro.h"

typedef enum { VERMELHO, PRETO } Cor;

typedef struct NoRB {
    const Registro *reg;
    Cor             cor;
    struct NoRB    *esq, *dir, *pai;
} NoRB;

typedef struct {
    NoRB *raiz;
    NoRB *nil;                   /* sentinela preta */
    int   tamanho;
    long  comparacoes;
    long  rotacoes;
} ArvoreRB;

void            rb_init(ArvoreRB *t);
int             rb_inserir(ArvoreRB *t, const Registro *r);  /* 1 = inseriu, 0 = id repetido */
const Registro *rb_buscar(ArvoreRB *t, int id);
int             rb_altura(const ArvoreRB *t);
void            rb_liberar(ArvoreRB *t);

#endif

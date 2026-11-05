/* Testes de corretude da AVL e da Rubro-Negra. */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "registro.h"
#include "avl.h"
#include "bst.h"

static int falhas = 0;
#define CHECK(cond, msg) do { \
    if (cond) printf("  [ok]    %s\n", msg); \
    else { printf("  [FALHA] %s\n", msg); falhas++; } } while (0)

/* Retorna a altura; marca *ok = 0 se violar ordem BST, balanceamento ou altura gravada. */
static int avl_valida(const NoAVL *n, int lo, int hi, int *ok)
{
    if (!n) return 0;
    int id = n->reg->id;
    if (id <= lo || id >= hi) *ok = 0;
    int he = avl_valida(n->esq, lo, id, ok);
    int hd = avl_valida(n->dir, id, hi, ok);
    if (abs(he - hd) > 1) *ok = 0;
    int h = 1 + (he > hd ? he : hd);
    if (n->altura != h) *ok = 0;
    return h;
}

/* Retorna a altura-negra; verifica as propriedades da rubro-negra. */
static int rb_valida(const ArvoreRB *t, const NoRB *n, int lo, int hi, int *ok)
{
    if (n == t->nil) return 1;
    int id = n->reg->id;
    if (id <= lo || id >= hi) *ok = 0;
    if (n->cor == VERMELHO && (n->esq->cor == VERMELHO || n->dir->cor == VERMELHO)) *ok = 0;
    int be = rb_valida(t, n->esq, lo, id, ok);
    int bd = rb_valida(t, n->dir, id, hi, ok);
    if (be != bd) *ok = 0;
    return be + (n->cor == PRETO);
}

static Registro *sintetico(int n, int embaralhar)
{
    Registro *v = calloc((size_t)n, sizeof *v);
    for (int i = 0; i < n; i++) { v[i].id = i + 1; snprintf(v[i].nome, TAM_NOME, "Atleta %d", i + 1); }
    if (embaralhar) {
        unsigned long long s = 12345;
        for (int i = n - 1; i > 0; i--) {
            s = s * 6364136223846793005ULL + 1442695040888963407ULL;
            int j = (int)((s >> 33) % (unsigned long long)(i + 1));
            Registro t = v[i]; v[i] = v[j]; v[j] = t;
        }
    }
    return v;
}

static void testar(const char *titulo, Registro *v, int n)
{
    printf("\n%s (n = %d)\n", titulo, n);
    AVL a; ArvoreRB r;
    avl_init(&a); rb_init(&r);

    for (int i = 0; i < n; i++) { avl_inserir(&a, &v[i]); rb_inserir(&r, &v[i]); }

    int ok = 1;
    avl_valida(a.raiz, 0, INT_MAX, &ok);
    CHECK(ok, "AVL: ordem BST, fator de balanceamento e alturas validos");
    ok = 1;
    int raiz_preta = (r.raiz->cor == PRETO);
    rb_valida(&r, r.raiz, 0, INT_MAX, &ok);
    CHECK(ok && raiz_preta, "RB: raiz preta, sem vermelho-vermelho, altura-negra uniforme");

    CHECK(a.tamanho == n && r.tamanho == n, "tamanho das duas arvores == n");

    int achou = 1;
    for (int i = 0; i < n; i++) {
        const Registro *x = avl_buscar(&a, v[i].id), *y = rb_buscar(&r, v[i].id);
        if (x != &v[i] || y != &v[i]) { achou = 0; break; }
    }
    CHECK(achou, "todas as chaves inseridas sao encontradas");

    CHECK(!avl_buscar(&a, 0) && !rb_buscar(&r, 0) &&
          !avl_buscar(&a, n + 1) && !rb_buscar(&r, n + 1), "chaves inexistentes retornam NULL");

    CHECK(!avl_inserir(&a, &v[0]) && !rb_inserir(&r, &v[0]) &&
          a.tamanho == n && r.tamanho == n, "id duplicado e rejeitado");

    double lg = log2((double)n + 2.0);
    CHECK(avl_altura(&a) <= 1.4405 * lg, "AVL: altura <= 1,44 * log2(n+2)");
    CHECK(rb_altura(&r)  <= 2.0 * log2((double)n + 1.0), "RB: altura <= 2 * log2(n+1)");

    printf("  altura AVL = %d | altura RB = %d | rotacoes AVL = %ld | rotacoes RB = %ld\n",
           avl_altura(&a), rb_altura(&r), a.rotacoes, r.rotacoes);

    avl_liberar(&a); rb_liberar(&r);
}

int main(void)
{
    Registro *v1 = sintetico(5000, 1); testar("Insercao aleatoria", v1, 5000);  free(v1);
    Registro *v2 = sintetico(5000, 0); testar("Insercao crescente (pior caso da BST simples)", v2, 5000); free(v2);

    Registro *csv = NULL;
    int n = registro_ler_csv("dataset/ocorrencias.csv", &csv);
    if (n > 0) { testar("Dataset real (ocorrencias.csv)", csv, n); free(csv); }
    else printf("\n(dataset/ocorrencias.csv nao encontrado - teste com dados reais ignorado)\n");

    printf("\n%s\n", falhas ? "RESULTADO: HA FALHAS" : "RESULTADO: todos os testes passaram");
    return falhas ? 1 : 0;
}

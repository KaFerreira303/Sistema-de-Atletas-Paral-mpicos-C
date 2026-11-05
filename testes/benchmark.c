/* Compara AVL x Rubro-Negra com o dataset de atletas paraolimpicos.
 * Uso (a partir da raiz do repositorio):
 *   benchmark [dataset/ocorrencias.csv] [resultados]
 * Gera resultados/avl_resultados.csv e resultados/bst_resultados.csv */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "registro.h"
#include "avl.h"
#include "bst.h"

#define REPETICOES 5

static const int TAMANHOS[] = {1000, 5000, 10000, 25000, 50000};
static const char *ORDENS[] = {"aleatoria", "crescente", "decrescente"};

typedef struct {
    double t_ins_ms;      long comp_ins;     long rotacoes;
    int    altura;        double t_busca_ms; double comp_busca_media;
} Medicao;

static double ms(clock_t a, clock_t b) { return 1000.0 * (double)(b - a) / CLOCKS_PER_SEC; }

static int altura_minima(int n) { int h = 0; while (((1L << h) - 1) < n) h++; return h; }

static Medicao medir_avl(const Registro *ins, const Registro *busca, int n)
{
    Medicao m = {0};
    double tins = 0, tbus = 0;
    for (int rep = 0; rep < REPETICOES; rep++) {
        AVL t; avl_init(&t);
        clock_t a = clock();
        for (int i = 0; i < n; i++) avl_inserir(&t, &ins[i]);
        clock_t b = clock();
        tins += ms(a, b);
        m.comp_ins = t.comparacoes; m.rotacoes = t.rotacoes; m.altura = avl_altura(&t);

        t.comparacoes = 0;
        int achados = 0;
        a = clock();
        for (int i = 0; i < n; i++) if (avl_buscar(&t, busca[i].id)) achados++;
        b = clock();
        tbus += ms(a, b);
        if (achados != n) fprintf(stderr, "AVL: busca falhou (%d/%d)\n", achados, n);
        m.comp_busca_media = (double)t.comparacoes / n;
        avl_liberar(&t);
    }
    m.t_ins_ms = tins / REPETICOES; m.t_busca_ms = tbus / REPETICOES;
    return m;
}

static Medicao medir_rb(const Registro *ins, const Registro *busca, int n)
{
    Medicao m = {0};
    double tins = 0, tbus = 0;
    for (int rep = 0; rep < REPETICOES; rep++) {
        ArvoreRB t; rb_init(&t);
        clock_t a = clock();
        for (int i = 0; i < n; i++) rb_inserir(&t, &ins[i]);
        clock_t b = clock();
        tins += ms(a, b);
        m.comp_ins = t.comparacoes; m.rotacoes = t.rotacoes; m.altura = rb_altura(&t);

        t.comparacoes = 0;
        int achados = 0;
        a = clock();
        for (int i = 0; i < n; i++) if (rb_buscar(&t, busca[i].id)) achados++;
        b = clock();
        tbus += ms(a, b);
        if (achados != n) fprintf(stderr, "RB: busca falhou (%d/%d)\n", achados, n);
        m.comp_busca_media = (double)t.comparacoes / n;
        rb_liberar(&t);
    }
    m.t_ins_ms = tins / REPETICOES; m.t_busca_ms = tbus / REPETICOES;
    return m;
}

static void linha(FILE *csv, const char *nome, int n, const char *ordem, const Medicao *m)
{
    fprintf(csv, "%d,%s,%.3f,%ld,%ld,%d,%d,%.3f,%.3f\n",
            n, ordem, m->t_ins_ms, m->comp_ins, m->rotacoes, m->altura,
            altura_minima(n), m->t_busca_ms, m->comp_busca_media);
    printf("%-3s n=%-6d %-12s ins=%8.3f ms  rot=%-7ld altura=%-3d (min %-2d)  busca=%7.3f ms  comp/busca=%.2f\n",
           nome, n, ordem, m->t_ins_ms, m->rotacoes, m->altura, altura_minima(n),
           m->t_busca_ms, m->comp_busca_media);
}

int main(int argc, char **argv)
{
    const char *caminho = argc > 1 ? argv[1] : "dataset/ocorrencias.csv";
    const char *pasta   = argc > 2 ? argv[2] : "resultados";

    Registro *todos = NULL;
    int total = registro_ler_csv(caminho, &todos);
    if (total <= 0) { fprintf(stderr, "erro ao ler %s\n", caminho); return 1; }
    printf("%d registros lidos de %s\n\n", total, caminho);

    char p_avl[512], p_rb[512];
    snprintf(p_avl, sizeof p_avl, "%s/avl_resultados.csv", pasta);
    snprintf(p_rb,  sizeof p_rb,  "%s/bst_resultados.csv", pasta);
    FILE *f_avl = fopen(p_avl, "w"), *f_rb = fopen(p_rb, "w");
    if (!f_avl || !f_rb) { fprintf(stderr, "nao foi possivel criar os CSVs em %s\n", pasta); return 1; }

    const char *cab = "n,ordem_insercao,tempo_insercao_ms,comparacoes_insercao,rotacoes,"
                      "altura,altura_minima,tempo_busca_ms,comparacoes_por_busca\n";
    fputs(cab, f_avl); fputs(cab, f_rb);

    for (size_t k = 0; k < sizeof TAMANHOS / sizeof *TAMANHOS; k++) {
        int n = TAMANHOS[k];
        if (n > total) continue;

        Registro *asc = malloc((size_t)n * sizeof *asc);
        Registro *desc = malloc((size_t)n * sizeof *desc);
        memcpy(asc, todos, (size_t)n * sizeof *asc);
        qsort(asc, (size_t)n, sizeof *asc, registro_comparar_id);
        for (int i = 0; i < n; i++) desc[i] = asc[n - 1 - i];

        const Registro *ordens[] = {todos, asc, desc};   /* aleatoria = ordem do arquivo */
        for (int o = 0; o < 3; o++) {
            Medicao ma = medir_avl(ordens[o], todos, n);
            Medicao mr = medir_rb (ordens[o], todos, n);
            linha(f_avl, "AVL", n, ORDENS[o], &ma);
            linha(f_rb,  "RB",  n, ORDENS[o], &mr);
        }
        printf("\n");
        free(asc); free(desc);
    }
    fclose(f_avl); fclose(f_rb);
    free(todos);
    printf("Resultados salvos em %s e %s\n", p_avl, p_rb);
    return 0;
}

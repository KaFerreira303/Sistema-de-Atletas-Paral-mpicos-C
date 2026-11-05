#include <stdio.h>
#include <stdlib.h>
#include "registro.h"

int registro_ler_csv(const char *caminho, Registro **saida)
{
    FILE *f = fopen(caminho, "r");
    if (!f) return -1;

    int cap = 1024, n = 0;
    Registro *v = malloc((size_t)cap * sizeof *v);
    if (!v) { fclose(f); return -1; }

    char linha[256];
    if (!fgets(linha, sizeof linha, f)) { free(v); fclose(f); return -1; } /* cabecalho */

    while (fgets(linha, sizeof linha, f)) {
        Registro r;
        int lidos = sscanf(linha,
            "%d,%63[^,],%3[^,],%39[^,],%7[^,],%d,%7[^,\r\n]",
            &r.id, r.nome, r.pais, r.modalidade, r.classe, &r.ano, r.medalha);
        if (lidos != 7) continue;               /* ignora linha malformada */

        if (n == cap) {
            cap *= 2;
            Registro *t = realloc(v, (size_t)cap * sizeof *v);
            if (!t) { free(v); fclose(f); return -1; }
            v = t;
        }
        v[n++] = r;
    }
    fclose(f);
    *saida = v;
    return n;
}

void registro_imprimir(const Registro *r)
{
    printf("#%d | %s | %s | %s (%s) | %d | %s\n",
           r->id, r->nome, r->pais, r->modalidade, r->classe, r->ano, r->medalha);
}

int registro_comparar_id(const void *a, const void *b)
{
    int x = ((const Registro *)a)->id, y = ((const Registro *)b)->id;
    return (x > y) - (x < y);
}

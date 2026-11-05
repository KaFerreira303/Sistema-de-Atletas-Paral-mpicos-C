#ifndef REGISTRO_H
#define REGISTRO_H

#define TAM_NOME       64
#define TAM_PAIS        4
#define TAM_MODALIDADE 40
#define TAM_CLASSE      8
#define TAM_MEDALHA     8

/* Uma "ocorrencia" = participacao de um atleta paraolimpico em uma edicao.
 * A chave usada nas arvores e o campo id (unico). */
typedef struct {
    int  id;
    char nome[TAM_NOME];
    char pais[TAM_PAIS];
    char modalidade[TAM_MODALIDADE];
    char classe[TAM_CLASSE];
    int  ano;
    char medalha[TAM_MEDALHA];
} Registro;

/* Le o CSV (com cabecalho) e aloca o vetor em *saida.
 * Retorna a quantidade de registros lidos, ou -1 em caso de erro.
 * O chamador deve dar free(*saida). */
int  registro_ler_csv(const char *caminho, Registro **saida);

void registro_imprimir(const Registro *r);

/* Comparador para qsort (ordem crescente de id). */
int  registro_comparar_id(const void *a, const void *b);

#endif

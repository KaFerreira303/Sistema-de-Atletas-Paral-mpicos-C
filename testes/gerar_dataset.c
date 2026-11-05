/* Gera dataset/ocorrencias.csv com ocorrencias de atletas paraolimpicos.
 * Uso: gerar_dataset [quantidade=50000] [saida=dataset/ocorrencias.csv]
 * Semente fixa: o mesmo arquivo e gerado em qualquer maquina. */
#include <stdio.h>
#include <stdlib.h>

#define QTD(a) ((int)(sizeof(a) / sizeof((a)[0])))

static unsigned long long estado = 88172645463325252ULL;
static unsigned rnd(void)                     /* xorshift64 */
{
    estado ^= estado << 13;
    estado ^= estado >> 7;
    estado ^= estado << 17;
    return (unsigned)(estado >> 32);
}

static const char *PRIMEIROS[] = {
    "Ana","Bruno","Carlos","Daniel","Eduardo","Fernanda","Gabriel","Helena","Igor","Julia",
    "Lucas","Marina","Natalia","Otavio","Paula","Rafael","Sofia","Thiago","Vitor","Yasmin",
    "Alex","Brian","Chen","David","Emma","Fatima","Giorgio","Hiro","Ivan","Jonas",
    "Kofi","Liam","Mia","Noor","Oleg","Pedro","Quinn","Rosa","Samir","Tariq"
};
static const char *SOBRENOMES[] = {
    "Silva","Santos","Oliveira","Souza","Lima","Pereira","Costa","Ribeiro","Almeida","Carvalho",
    "Smith","Johnson","Brown","Wang","Li","Zhang","Muller","Schmidt","Dubois","Martin",
    "Rossi","Ferrari","Garcia","Lopez","Tanaka","Sato","Kim","Park","Ivanov","Kowalski",
    "Nowak","Petrov","Hassan","Khan","Mensah","Okafor","Van Dijk","Jansen","Andersen","Nilsen"
};
static const char *PAISES[] = {
    "BRA","CHN","GBR","USA","UKR","NED","GER","FRA","ESP","ITA",
    "AUS","JPN","CAN","RSA","IRI","MEX","ARG","COL","POL","KEN"
};

static const char *CL_ATLETISMO[]  = {"T11","T12","T13","T20","T35","T37","T38","T44","T47","T54","F11","F20","F32","F41","F46","F57"};
static const char *CL_NATACAO[]    = {"S3","S5","S6","S7","S8","S9","S10","S11","S13","S14","SB4","SM7"};
static const char *CL_BASQUETE[]   = {"1.0","2.0","3.0","4.0","4.5"};
static const char *CL_JUDO[]       = {"B1","B2","B3"};
static const char *CL_TENIS_MESA[] = {"TT3","TT5","TT8","TT10","TT11"};
static const char *CL_HALTERO[]    = {"Unica"};
static const char *CL_GOALBALL[]   = {"B1","B2","B3"};
static const char *CL_ARCO[]       = {"W1","W2","ST","VI"};
static const char *CL_ESGRIMA[]    = {"A","B"};
static const char *CL_REMO[]       = {"PR1","PR2","PR3"};
static const char *CL_CICLISMO[]   = {"C1","C3","C5","H2","H4","T1","T2","B"};

typedef struct { const char *nome; const char **classes; int n; } Modalidade;
static const Modalidade MODS[] = {
    {"Atletismo",                    CL_ATLETISMO,  QTD(CL_ATLETISMO)},
    {"Natacao",                      CL_NATACAO,    QTD(CL_NATACAO)},
    {"Basquete em cadeira de rodas", CL_BASQUETE,   QTD(CL_BASQUETE)},
    {"Judo",                         CL_JUDO,       QTD(CL_JUDO)},
    {"Tenis de mesa",                CL_TENIS_MESA, QTD(CL_TENIS_MESA)},
    {"Halterofilismo",               CL_HALTERO,    QTD(CL_HALTERO)},
    {"Goalball",                     CL_GOALBALL,   QTD(CL_GOALBALL)},
    {"Tiro com arco",                CL_ARCO,       QTD(CL_ARCO)},
    {"Esgrima em cadeira de rodas",  CL_ESGRIMA,    QTD(CL_ESGRIMA)},
    {"Remo",                         CL_REMO,       QTD(CL_REMO)},
    {"Ciclismo",                     CL_CICLISMO,   QTD(CL_CICLISMO)}
};

int main(int argc, char **argv)
{
    int n = (argc > 1) ? atoi(argv[1]) : 50000;
    const char *saida = (argc > 2) ? argv[2] : "dataset/ocorrencias.csv";
    if (n <= 0) { fprintf(stderr, "quantidade invalida\n"); return 1; }

    /* ids 1..n embaralhados (Fisher-Yates): arquivo em ordem aleatoria */
    int *ids = malloc((size_t)n * sizeof *ids);
    if (!ids) return 1;
    for (int i = 0; i < n; i++) ids[i] = i + 1;
    for (int i = n - 1; i > 0; i--) {
        int j = (int)(rnd() % (unsigned)(i + 1));
        int t = ids[i]; ids[i] = ids[j]; ids[j] = t;
    }

    FILE *f = fopen(saida, "w");
    if (!f) { perror(saida); free(ids); return 1; }
    fprintf(f, "id,nome,pais,modalidade,classe,ano,medalha\n");

    for (int i = 0; i < n; i++) {
        const Modalidade *m = &MODS[rnd() % QTD(MODS)];
        int ano = 1960 + 4 * (int)(rnd() % 17);          /* 1960..2024 */
        unsigned p = rnd() % 100;
        const char *medalha = p < 8 ? "Ouro" : p < 16 ? "Prata" : p < 26 ? "Bronze" : "Nenhuma";

        fprintf(f, "%d,%s %s %s,%s,%s,%s,%d,%s\n",
                ids[i],
                PRIMEIROS[rnd() % QTD(PRIMEIROS)],
                SOBRENOMES[rnd() % QTD(SOBRENOMES)],
                SOBRENOMES[rnd() % QTD(SOBRENOMES)],
                PAISES[rnd() % QTD(PAISES)],
                m->nome, m->classes[rnd() % (unsigned)m->n],
                ano, medalha);
    }
    fclose(f);
    free(ids);
    printf("%d registros gerados em %s\n", n, saida);
    return 0;
}

# Resultados

Gerados por `make run` (`testes/benchmark.c`) sobre `dataset/ocorrencias.csv` (50.000 registros).
Arquivos: `avl_resultados.csv` (AVL) e `bst_resultados.csv` (Rubro-Negra).

## Colunas

| coluna | significado |
|---|---|
| `n` | quantidade de registros inseridos |
| `ordem_insercao` | `aleatoria` (ordem do arquivo), `crescente` ou `decrescente` por id |
| `tempo_insercao_ms` | tempo médio para inserir os n registros (5 repetições) |
| `comparacoes_insercao` | nós visitados durante todas as inserções |
| `rotacoes` | rotações simples realizadas (rotação dupla conta 2) |
| `altura` | altura final (nº de níveis) |
| `altura_minima` | altura mínima teórica de uma árvore binária com n nós, ⌈log₂(n+1)⌉ |
| `tempo_busca_ms` | tempo médio para buscar os n ids (todos existentes) |
| `comparacoes_por_busca` | média de nós visitados por busca |

## Resumo para n = 50.000

| ordem | árvore | inserção (ms) | rotações | altura | comparações/busca |
|---|---|---|---|---|---|
| aleatória | AVL | 29,469 | 34.753 | 19 | 14,94 |
| aleatória | Rubro-Negra | 18,496 | 29.166 | 19 | 14,97 |
| crescente | AVL | 6,196 | 49.984 | 16 | 14,69 |
| crescente | Rubro-Negra | 5,632 | 49.971 | 29 | 15,10 |
| decrescente | AVL | 5,286 | 49.984 | 16 | 14,69 |
| decrescente | Rubro-Negra | 4,022 | 49.971 | 29 | 15,10 |

*(Tempos variam conforme a máquina; contagens de rotações, alturas e comparações são determinísticas.)*

## Análise

- **Altura:** com inserção aleatória as duas ficam iguais (19 níveis para 50 mil nós, mínimo teórico 16).
  Com inserção ordenada, a AVL mantém altura quase ótima (16), enquanto a rubro-negra chega a 29,
  perto do limite teórico de 2·log₂(n+1) ≈ 32. Isso acontece porque a AVL é balanceada de forma mais rígida.
- **Busca:** como a AVL é mais baixa, ela faz um pouco menos comparações por busca em dados ordenados
  (14,69 contra 15,10). Em dados aleatórios a diferença é desprezível.
- **Inserção e rotações:** a rubro-negra faz menos rotações em inserções aleatórias (29.166 contra 34.753),
  porque parte do rebalanceamento é feita só com recoloração. Por isso costuma inserir mais rápido.
- **Conclusão:** a AVL favorece cargas com muita **busca**; a rubro-negra favorece cargas com muita
  **inserção/remoção**. Ambas garantem O(log n) no pior caso — uma árvore binária de busca comum
  degeneraria para altura 50.000 com os dados em ordem crescente.

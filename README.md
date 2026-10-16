# Sistema de Atletas Paralímpicos - C

# Entrega 1 da disciplina Estruturas de Dados II

# Universidade Cidade de São Paulo (UNICID)

# Prof. Cid Rodrigues de Andrade

# 👥 Integrantes do Grupo

# Cauã F. Rios de Carvalho — 42672007

# Derick Gomes de Oliveira — 42921121

# Felipe Alves da Silva — 43516599

# Gabriela Dias Santos Barros — 43902227

# Ingrid Pereira dos Santos — 42664004

 # 1. Dataset
 
1.1 Descrição e Volume
O dataset utilizado no projeto baseia-se em informações de atletas dos Jogos Paralímpicos, abrangendo competições realizadas entre 1960 e 2024. Os dados contemplam informações detalhadas de atletas, países, esportes, eventos e medalhas conquistadas.
A base original possui aproximadamente 27.000 registros reais. Como o escopo do projeto abrange faixas de volume robustas para testes de eficiência de árvores auto-balanceadas, o grupo utilizará a base real diretamente para os testes e análises de desempenho, garantindo a fidelidade e o cumprimento dos requisitos de robustez exigidos para estruturas de dados em grande escala. 

# 1.2 Fonte do Dataset

Base Real: Dados oficiais históricos dos Jogos Paralímpicos obtidos por meio de bases públicas estruturadas do International Paralympic Committee (IPC) e repositórios abertos associados de eventos esportivos multiesportivos internacionais (como Kaggle/IPC Historical Results Dataset).
Consistência dos Dados: Como os dados originais já cobrem o volume ideal para testes práticos de árvore de busca, não há necessidade de geração sintética de massa artificial, preservando assim a integridade estatística e os padrões reais de distribuição de chaves (como concentração de medalhas por atletas de elite e grande volume de atletas sem medalhas).

# 1.3 Estrutura dos Dados e Chave Composta

Os principais campos utilizados na estrutura do registro (struct AtletaRegistro) em linguagem C são:

id (int): Identificador único do registro/atleta.

nome (char[]): Nome completo do atleta.

pais (char[]): País representado.

ano (int): Ano da competição.

esporte (char[]): Modalidade esportiva.

evento (char[]): Evento específico de participação.

medalha (char[] ou int): Tipo ou contagem de medalha conquistada (Ouro, Prata, Bronze, Nenhuma).

posicao (int): Posição obtida no evento.

tipo (char[]): Participação individual ou por equipe.

Padronização da Chave Composta nas Árvores AVL e Rubro-Negra
Para permitir uma comparação justa de desempenho e evitar ambiguidades com chaves repetidas (visto que múltiplos atletas possuem a mesma quantidade de medalhas ou IDs isolados), ambas as árvores utilizarão a mesma chave composta:

Chave Composta: (Total de Medalhas + ID do Atleta) ou (Ano + ID).

Regra de Organização: A ordenação principal ocorre pelo número total de medalhas acumuladas pelo atleta; em caso de empate (muito comum no dataset), o critério de desempate aplicado de forma determinística é o id do atleta em ordem crescente. Isso garante unicidade na árvore, evita sobreposição de nós e permite um percurso em-ordem perfeitamente ordenado e não-decrescente.

# 1.4 Justificativa da Escolha do Dataset

O dataset foi escolhido por sua relevância temática e pelas características inerentes de distribuição de dados, que testam rigorosamente o comportamento das árvores:

Tratamento de Duplicatas e Distribuição Desbalanceada: O fato de muitos atletas possuírem zero medalhas ou o mesmo número de conquistas exige um tratamento robusto de chaves compostas e colisões lógicas.

Desempenho sob Inserções Reais: Inserir dados históricos reais (que já possuem uma ordem natural de anos e IDs) permite observar como as árvores AVL e Rubro-Negra lidam com o fator de balanceamento e reagem a entradas quase ordenadas, cenário que degrada árvores binárias comuns (BST) para O(n).

# 2. Estrutura(s) de Árvore Escolhida(s)

# 2.1 Estruturas Utilizadas

  Árvore AVL: Árvore de busca binária auto-balanceada rigorosa baseada na manutenção do fator de balanceamento ($FB \in \{-1, 0, 1\}$) através de rotações simples e duplas.
  
Árvore Rubro-Negra (Red-Black Tree): Árvore de busca binária auto-balanceada por coloração de nós e regras estritas de altura negra, priorizando menores custos de rebalanceamento (menos rotações) em inserções massivas em comparação à AVL.

# 2.2 Justificativa Técnica e Comparativa

As estruturas foram selecionadas para confrontar duas filosofias distintas de auto-balanceamento aplicadas ao mesmo dataset de atletas paralímpicos:

Árvore AVL: Como é mais rigidamente balanceada, sua altura máxima é estritamente menor, garantindo buscas extremamente rápidas ($O(\log n)$ puro). No entanto, exige mais rotações durante inserções e remoções.

Árvore Rubro-Negra: Permite desbalanceamentos temporários controlados por cores, resultando em menor número de rotações e melhor performance de escrita (inserções/remoções frequentes), embora sua altura possa ser ligeiramente superior à da AVL.

Objetivo da Comparação: Avaliar empiricamente o trade-off entre o custo de rebalanceamento da AVL versus a flexibilidade da Rubro-Negra utilizando exatamente a mesma chave composta em ambas.

# 2.3 Operações Implementadas

Inserção com suporte a chave composta e tratamento de duplicatas.
Remoção (nós folha, com 1 filho e com 2 filhos / raiz).

Busca exata por chave composta.

Percursos (Pré-ordem, Em-ordem e Pós-ordem).

Auto-balanceamento automático (Rotações e Recolorações).

# 2.4 Complexidade Computacional

 Operação			Melhor Caso				Caso Médio 			Pior caso 
 
  Inserção			o(log n)				o(log n) 			o(log n)
 
 Busca				o(1)					o(log n)			o(log n)
 
 Remoção 			o(log n)				o(log n ) 			o(log n )
 
# 3. Plano e Casos de Teste

# 3.1 Objetivo dos Testes

Verificar a corretude lógica das operações de inserção, busca, remoção e percursos, avaliando o desempenho temporal (com relógio de alta resolução), contagem de rotações/recolorações e a manutenção da altura das árvores AVL e Rubro-Negra sob diferentes tamanhos de entrada da base real de atletas paralímpicos.

# 3.2 Condições de Medição e Metodologia

 Ambiente Controlado: Os testes de desempenho de tempo serão executados no mesmo computador, logo após a inicialização do sistema operacional e sem aplicações concorrentes pesadas em segundo plano.
 
 Tamanhos de Entrada Escalonados: Para validar a complexidade logarítmica, os testes serão executados com blocos de tamanhos fixos: $5.000$, $10.000$, $20.000$ e o total da base real ($\approx 27.000$ registros).
 
 Repetições: Cada medição de tempo será repetida 5 vezes consecutivas, registrando-se a média ou mediana dos resultados obtidos.

# 3.3 Casos Extremos (Edge Cases)

Árvore Vazia: Tentar realizar buscas, remoções ou percursos em uma árvore recém-inicializada (ponteiro raiz nulo), garantindo que o programa não apresente falha de segmentação (Segmentation Fault).

Árvore com Único Elemento: Inserção de apenas um registro, seguida de busca com sucesso, busca sem sucesso e remoção desse único nó (retornando a árvore ao estado vazio).

Chaves Duplicadas (Mesmo número de medalhas): Inserção de atletas com métricas de medalhas idênticas. O sistema deve aplicar corretamente a regra de desempate via ID na chave composta, posicionando o novo nó de forma consistente sem corromper a árvore.

Dados em Ordem Crescente/Decrescente: Inserção de registros ordenados por ano/ID para testar a eficiência agressiva dos mecanismos de rotação e recoloração (pior cenário para árvores BST comuns).

# 4. Cenários de Teste
   
# Cenário 1: Inserção Massiva e Busca (AVL e Rubro-Negra)

Objetivo: Validar a integridade estrutural durante o povoamento em larga escala e comprovar a exatidão das buscas para dados existentes e inexistentes.

Fases de Teste:

 1.Inserção Massiva: Carga de blocos de dados utilizando a chave composta (medalhas + id). Registro quantitativo de rotações simples/duplas (na AVL) e recolorações/rotações (na Rubro-Negra), certificando-se de que o fator de balanceamento e as propriedades de cor são respeitados.
 
 2. Busca por Chaves Existentes (Sucesso): Consulta por $1.000$ chaves sorteadas presentes no dataset.
    
     Resultado Esperado: Retorno imediato do ponteiro para o registro completo do atleta em tempo compatível com $O(\log n)$.
    
    3. Busca por Chaves Inexistentes (Falha Controlada): Consulta por chaves inválidas (ex: ID negativo ou inexistente no topo do limite).
       
    Resultado Esperado: Retorno gracioso de ponteiro nulo (NULL) acompanhado de mensagem tratada ("Atleta não encontrado"), sem travamento da aplicação.

# Cenário 2: Remoção (Três Casos Clássicos de Exclusão)

Objetivo: Verificar se o algoritmo de remoção preserva as propriedades das árvores e reorganiza ponteiros e balanceamento após a exclusão em diferentes níveis.

Casos de Teste:

Caso 01 (Remoção de Nó Folha - Grau 0): Exclusão de um nó sem filhos.

Resultado Esperado: Desalocação segura de memória, atualização do ponteiro do pai para NULL e reavaliação do balanceamento subindo até a raiz.

Caso 02 (Remoção de Nó com Apenas Um Filho - Grau 1): Exclusão de nó com estritamente uma subárvore.

Resultado Esperado: Promoção direta do único filho para a posição do pai removido com religamento correto de ponteiros.

Caso 03 (Remoção de Nó com Dois Filhos ou Raiz - Grau 2): Exclusão de nós complexos, incluindo a raiz da árvore.

Resultado Esperado: Identificação do sucessor em-ordem (menor valor da subárvore direita), cópia dos dados para o nó alvo, exclusão física do nó sucessor original e disparo dos rebalanceamentos necessários.

# Cenário 3: Percursos (Validação e Ordenação das Chaves)

Objetivo: Confirmar a topologia e assegurar que as chaves mantêm a relação de ordem correta através do caminhamento.

Casos de Teste:
Percurso Em-Ordem (In-Order: $E \rightarrow R \rightarrow D$):

Resultado Esperado: Geração de uma sequência de saída onde todas as chaves compostas aparecem de forma estritamente ordenada (não-decrescente), comprovando a corretude da árvore de busca binária.

Percurso Pré-Ordem (Pre-Order: $R \rightarrow E \rightarrow D$):

Resultado Esperado: Mapeamento estruturado útil para clonagem, serialização ou reconstrução exata da árvore.

Percurso Pós-Ordem (Post-Order: $E \rightarrow D \rightarrow R$):

Resultado Esperado: 

Garantia de liberação segura e recursiva da memória alocada (desalocação de baixo para cima) sem perda de referências.



# 5.Referências

CORMEN, Thomas H. et al. Algoritmos: Teoria e Prática. 3ª ed. Rio de Janeiro: Elsevier Campus, 2012.

INTERNATIONAL PARALYMPIC COMMITTEE (IPC). Historical Paralympic Results and Database. Disponível em acervos e repositórios esportivos oficiais abertos.

WEISS, Mark Allen. Data Structures and Algorithm Analysis in C. 2nd ed. Addison-Wesley, 1996.

# Sistema-de-Atletas-Paral-mpicos-C
Entrega 1 da disciplina Estruturas de Dados II 

Sistema de Atletas Paralímpicos

Universidade Cidade de São Paulo (UNICID) 

Prof. Cid Rodrigues de Andrade


# 👥 Integrantes do Grupo
Nome completo	com o RGM

Cauã F. Rios de Carvalho	42672007

Derick Gomes de Oliveira	42921121

Felipe Alves da Silva	43516599

Gabriela Dias Santos Barros	43902227

Ingrid Pereira dos Santos	4266404
________________________________________
# 1. Dataset

1.1 Descrição
O dataset utilizado no projeto será baseado em informações de atletas dos Jogos Paralímpicos, abrangendo competições realizadas entre 1960 e 2024.
Os dados possuem informações relacionadas aos atletas, países, esportes, eventos e medalhas conquistadas.
A base original possui aproximadamente 27 mil registros. Como o trabalho exige um volume entre 50 mil e 1 milhão de registros, serão gerados registros adicionais seguindo a mesma estrutura e características dos dados originais, formando uma base de testes com pelo menos 50 mil registros.
Dessa forma, o projeto poderá utilizar dados reais como base e, ao mesmo tempo, atender ao requisito de volume necessário para os testes das estruturas de dados.
O arquivo utilizado será disponibilizado em formato CSV.

1.2 Fonte
O dataset utilizado como base contém informações dos Jogos Paralímpicos de 1960 a 2024 e possui como fonte o International Paralympic Committee (IPC).
Os registros adicionais utilizados para atingir o volume mínimo de 50 mil registros serão gerados pelo grupo com base na estrutura dos dados originais.

1.3 Estrutura dos dados
Os principais campos utilizados no projeto serão:

id: identificador único do registro/atleta.
nome: nome do atleta.
pais: país representado pelo atleta.
ano: ano da competição.
esporte: modalidade esportiva.
evento: evento em que o atleta participou.
medalha: medalha conquistada, podendo ser ouro, prata ou bronze.
posição: posição obtida pelo atleta no evento.
tipo: identificação se a participação é individual ou por equipe.

Para a árvore AVL, o campo id será utilizado como chave principal para as operações de inserção, busca e remoção.
Para a árvore Rubro-Negra, será utilizada a quantidade de medalhas como chave de organização dos atletas.

1.4 Justificativa da escolha
O dataset foi escolhido por estar diretamente relacionado ao tema do projeto, que é o Sistema de Atletas Paralímpicos.
A presença de informações sobre atletas, esportes, eventos e medalhas permite utilizar diferentes critérios para testar as estruturas de árvores.
Na árvore AVL, os atletas serão organizados pelo ID, possibilitando realizar operações de inserção, busca e remoção.
Na árvore Rubro-Negra, os atletas vão ser organizados de acordo com a quantidade de medalhas.
Além disso, o volume original de aproximadamente 27 mil registros será ampliado para pelo menos 50 mil registros para atender ao requisito do trabalho e permitir testes com uma quantidade maior de dados.

 # 2. Estrutura(s) de Árvore Escolhida(s)

2.1 Estrutura(s)
Serão utilizadas duas árvores de busca binária auto-balanceadas:
Árvore AVL
Árvore Rubro-Negra

2.2 Justificativa técnica
As árvores AVL e Rubro-Negra foram escolhidas por serem estruturas de busca binária auto-balanceadas.
A árvore AVL será utilizada para organizar os atletas pelo ID, permitindo realizar operações de inserção, busca e remoção mantendo a árvore balanceada.
A árvore Rubro-Negra será utilizada para organizar os atletas pela quantidade de medalhas.
A utilização das duas estruturas também permitirá comparar seus mecanismos de balanceamento e observar as rotações realizadas durante a inserção dos dados.

2.3 Operações implementadas (Para Entrega 2)
	Inserção
	Remoção
	Busca
	Percursos (pré-ordem, em ordem, pós-ordem)
	Balanceamento (se aplicável)
	Outra: ______

2.4 Complexidade

Operação |     Melhor caso |      Caso médio |    Pior caso

Inserção |               O(log n)  |       O(log n)   |        O(log n)

   Busca    |                   O(1)    |        O(log n)   |         O(log n)

   Remoção	 |                   O(log n)  |        O(log n)   |           O(log n)


Como as árvores utilizadas são estruturas auto-balanceadas, a altura das árvores é mantida de forma controlada, garantindo operações de busca, inserção e remoção em ordem logarítmica.

# 3. Plano de teste 

 3.1 Os testes têm como objetivo verificar a correção das operações implementadas (inserção, busca, remoção e percursos) e avaliar o comportamento e o desempenho das árvores AVL e Rubro-Negra sob diferentes ordens de entrada e volumes de dados.
Será analisada a eficiência dos mecanismos de auto-balanceamento, observando a ocorrência de rotações, a manutenção da altura das árvores e o tempo de execução nas operações principais com a base ampliada de pelo menos 50.000 registros.

3.2 Objetivo dos testes
Os testes terão como objetivo verificar a corretude das operações implementadas e o comportamento das árvores AVL e Rubro-Negra com diferentes quantidades e ordens de dados.
Serão avaliadas as operações de inserção, busca, remoção, percursos e balanceamento.
Também será verificado o comportamento das árvores quando os registros forem inseridos em diferentes ordens, permitindo observar as rotações realizadas pelas estruturas.

3.3 Casos extremos (edge cases)
Liste casos como: árvore vazia, único elemento, dados duplicados, dados em ordem crescente/decrescente (pior caso para BST), volume máximo do dataset, etc.

# 4. Cenários de teste

 # Cenário 1
Inserção e Busca (AVL e Rubro-Negra)Objetivo:Validar a integridade estrutural das árvores durante o povoamento massivo e comprovar a exatidão dos algoritmos de busca para dados presentes e ausentes.Fases de Teste:

Inserção Massiva (50.000+ registros):Árvore AVL (Chave = id): Inserção de registros com IDs aleatórios e sequenciais. Deve-se registrar o quantitativo de rotações simples (à esquerda e à direita) e duplas (esquerda-direita e direita-esquerda) executadas para manter o Fator de Balanceamento $FB \in \{-1, 0, 1\}$.Árvore Rubro-Negra (Chave Composta = medalhas + id):

Inserção garantindo o tratamento de chaves duplicadas (atletas com o mesmo número de medalhas). Registro do número de recolorações de nós e rotações necessárias para garantir as propriedades das cores vermelho/preto.Busca por Chaves Existentes (Sucesso):Procedimento: Consulta por 1.000 IDs sorteados e quantidades de medalhas conhecidas no dataset.Resultado Esperado:

Retorno imediato do ponteiro para o nó correspondente contendo a estrutura completa do atleta, executado em tempo limite $O(\log n)$.Busca por Chaves Inexistentes (Falha Controlada):

Procedimento: Consulta por chaves negativas (ex: ID = -1), valores zerados inválidos ou limites superiores além do dataset (ex: ID = 999999).Resultado Esperado: Retorno gracioso de ponteiro nulo (NULL / None) ou mensagem tratada de "Atleta não encontrado", sem interrupção abrupta da aplicação.

 # Cenário 2:
Remoção (Três Casos Clássicos de Exclusão)Objetivo:Verificar se o algoritmo de remoção preserva as propriedades de Árvore Binária de Busca e reorganiza corretamente os ponteiros e o balanceamento após a exclusão de nós em diferentes níveis da árvore.Casos de Teste:Caso 

 Remoção de Nó Folha (grau 0):Procedimento: Localizar um nó sem subárvores à esquerda ou à direita e disparar a exclusão.Resultado Esperado: Desalocação da memória do nó, atualização do ponteiro do nó pai para NULL e reavaliação do balanceamento da árvore subindo da folha excluída até a raiz.
 Caso1:
 Remoção de Nó com Apenas Um Filho (grau 1):
Procedimento: Selecionar um nó interno que possua estritamente uma subárvore (apenas filho esquerdo ou apenas filho direito).
Caso 2:
resultado Esperado.Promoção direta do único filho para a posição do nó pai removido, garantindo o religamento correto dos ponteiros.
Caso 3:
Remoção de Nó com Dois Filhos (grau 2):
Procedimento: Selecionar nós internos complexos, incluindo a raiz, que possuam ambas as subárvores.Resultado Esperado:Identificação do sucessor em-ordem (menor valor da subárvore direita) ou antecessor em-ordem (maior valor da subárvore esquerda).Cópia das chaves e dados do sucessor/antecessor para o nó alvo da remoção.Exclusão física do nó doador (que cairá no Caso 1 ou Caso 2).Disparo dos rebalanceamentos necessários (rotações na AVL e ajuste de duplo-preto/recolorações na Rubro-Negra).

 #  Cenário 3 
 Percursos (Validação e Ordenação das Chaves)Objetivo:Confirmar a integridade da topologia da árvore e assegurar que as chaves mantêm a relação de ordem correta através do caminhamento por todos os nós.Casos de Teste:Percurso Em-Ordem (In-Order Traversal):
Mecanismo: Visita a subárvore esquerda, depois a raiz e por fim a subárvore direita ($E \rightarrow R \rightarrow D$).Resultado Esperado: Impressão ou geração de um array de saída onde todas as chaves (id na AVL e medalhas na Rubro-Negra) aparecem de forma estritamente crescente e ordenada.Percurso Pré-Ordem (Pre-Order Traversal):Mecanismo: Visita a raiz primeiro, seguida da subárvore esquerda e da subárvore direita ($R \rightarrow E \rightarrow D$).Resultado Esperado: Mapeamento útil para operações de clonagem, serialização ou reconstrução exata da estrutura da árvore.Percurso Pós-Ordem (Post-Order Traversal):Mecanismo: Visita as subárvores esquerda e direita antes de processar a raiz ($E \rightarrow D \rightarrow R$).Resultado Esperado: Garantia de liberação segura de memória (desalocação de baixo para cima) ou cálculo de propriedades estruturais agregadas sem referências perdidas.

# 5. Referências
Livros-texto de Estrutura de Dados: Fundamentação teórica para as árvores AVL e Rubro-Negra, complexidade assintótica $O(\log n)$ e balanceamento.
Fonte Oficial do Dataset: Documentação da origem dos dados reais dos Jogos Paralímpicos (International Paralympic Committee).

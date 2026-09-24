# Sistema-de-Atletas-Paral-mpicos-C
Sistema de Atletas Paralímpicos
Entrega 1 de trabalho da disciplina Estruturas de Dados II — UNICID Prof. Cid Rodrigues de Andrade


👥 Integrantes do Grupo
Nome completo	com o RA
Cauã F. Rios de Carvalho	42672007
Derick Gomes de Oliveira	42921121
Felipe Alves da Silva	43516599
Gabriela Dias Santos Barros	43902227
Ingrid Pereira dos Santos	4266404
________________________________________
1. Dataset

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

2. Estrutura(s) de Árvore Escolhida(s)

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
Operação | Melhor caso | Caso médio | Pior caso
Inserção |   O(log n)  | O(log n)   | O(log n)
Busca    |     O(1)    | O(log n)   | O(log n)
Remoção	 |   O(log n)  | O(log n)   | O(log n)

Como as árvores utilizadas são estruturas auto-balanceadas, a altura das árvores é mantida de forma controlada, garantindo operações de busca, inserção e remoção em ordem logarítmica.

3. Plano de Testes

3.1 Objetivo dos testes
Os testes terão como objetivo verificar a corretude das operações implementadas e o comportamento das árvores AVL e Rubro-Negra com diferentes quantidades e ordens de dados.
Serão avaliadas as operações de inserção, busca, remoção, percursos e balanceamento.
Também será verificado o comportamento das árvores quando os registros forem inseridos em diferentes ordens, permitindo observar as rotações realizadas pelas estruturas.

3.2 Cenários de teste
#	Cenário	Entrada	Resultado esperado	Status
1				
2				
3				
3.3 Casos extremos (edge cases)
Liste casos como: árvore vazia, único elemento, dados duplicados, dados em ordem crescente/decrescente (pior caso para BST), volume máximo do dataset, etc.
3.4 Testes de desempenho (Para Entrega 2)
Descreva como o grupo mediu tempo de execução e/ou uso de memória, e com quais tamanhos de entrada (ex: 100, 1.000, 10.000 registros).
3.5 Resultados obtidos (Para Entrega 2)
Resuma os resultados (tabelas, gráficos ou links para arquivos de saída na pasta /resultados) e compare-os com a complexidade assintótica (Big-O) teórica.
________________________________________
4. Como Executar
4.1 Pré-requisitos (Para Entrega 2)
Linguagem, versão e dependências necessárias.
4.2 Instruções (Para Entrega 2)
# Exemplo
git clone <link-do-repositorio>
cd <pasta>
# comandos de compilação/execução
4.3 Estrutura do repositório (já com pastas para a Entrega 2)
/src         → código-fonte
/dataset     → dataset utilizado
/testes      → scripts e casos de teste
/resultados  → saídas e relatórios de desempenho
README.md
________________________________________
5. Referências
Livros-texto de Estrutura de Dados: Fundamentação teórica para as árvores AVL e Rubro-Negra, complexidade assintótica $O(\log n)$ e balanceamento.
Fonte Oficial do Dataset: Documentação da origem dos dados reais dos Jogos Paralímpicos (International Paralympic Committee).

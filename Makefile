CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=c11 -Isrc
BIN     = bin
SRC     = src/avl.c src/bst.c src/registro.c

all: $(BIN)/gerar_dataset $(BIN)/test_arvores $(BIN)/benchmark

$(BIN):
	mkdir -p $(BIN)

$(BIN)/gerar_dataset: testes/gerar_dataset.c | $(BIN)
	$(CC) $(CFLAGS) $< -o $@

$(BIN)/test_arvores: testes/test_arvores.c $(SRC) | $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BIN)/benchmark: testes/benchmark.c $(SRC) | $(BIN)
	$(CC) $(CFLAGS) $^ -o $@

dataset: $(BIN)/gerar_dataset
	./$(BIN)/gerar_dataset 50000 dataset/ocorrencias.csv

test: $(BIN)/test_arvores
	./$(BIN)/test_arvores

run: $(BIN)/benchmark
	./$(BIN)/benchmark dataset/ocorrencias.csv resultados

clean:
	rm -rf $(BIN)

.PHONY: all dataset test run clean

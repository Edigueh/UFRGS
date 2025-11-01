CC = gcc
CFLAGS = -Iinclude

SRC_DIR := src
# SRCS : Lista de todos os arquivos (.c), separados por espaço.
SRCS := $(wildcard $(SRC_DIR)/*.c)
# OBJS : Pega a lista de SRCS e substitui '.c' por '.o'.
OBJS := $(SRCS:.c=.o)

OUTPUT ?= measurer.o

# Requisitos de frameworks para compilar na arquitetura Darwin do mac.
# ifeq ($(shell uname), Darwin)
#     LDFLAGS += -framework IOKit -framework Cocoa -framework OpenGL
# endif

# Compila tudo e linka.
all: $(OUTPUT)

# Linka os objetos com os seus respectivos executáveis.
# $^ : Todas as dependências separadas por espaços.
$(OUTPUT): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

# Compila os source files.
# $< : Nome da primeira dependência.
# $@ : Nome do primeiro alvo.
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

visualize:
	@mkdir -p visualization
	@echo "Generating graph images..."
	@dot -Tsvg visualization/bst.dot -o visualization/bst.svg
	@dot -Tsvg visualization/avl.dot -o visualization/avl.svg
	@dot -Tsvg visualization/rbt.dot -o visualization/rbt.svg
	@echo "Graph generation complete."s

# Compila e roda o jogo e depois limpa os executáveis.
run: all
	./$(OUTPUT)
	rm -f $(OBJS)

# Limpa os executáveis deixados pra trás caso existam.
clean:
	rm -f $(OUTPUT) $(OBJS)

.PHONY: all run clean

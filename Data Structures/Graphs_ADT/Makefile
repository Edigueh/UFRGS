CC = gcc
CFLAGS = -Iinclude

SRC_DIR := include
# SRCS : Lista de todos os arquivos (.c) do diretório include, separados por espaço.
SRCS := $(wildcard $(SRC_DIR)/*.c)
# OBJS : Pega a lista de SRCS e substitui '.c' por '.o'.
OBJS := $(SRCS:.c=.o)

# Adiciona main.c e main.o
MAIN_SRC := main.c
MAIN_OBJ := main.o

# Nome do executável final
OUTPUT ?= graphs.o

# Compila tudo e linka.
all: $(OUTPUT)

# Linka os objetos com os seus respectivos executáveis.
# $^ : Todas as dependências separadas por espaços.
$(OUTPUT): $(OBJS) $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Compila os source files do diretório include.
# $< : Nome da primeira dependência.
# $@ : Nome do primeiro alvo.
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Compila o main.c
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) -c $< -o $@ $(CFLAGS)

# Compila e roda o programa e depois limpa os executáveis.
run: all
	./$(OUTPUT)
	rm -f $(OBJS) $(MAIN_OBJ)

# Limpa os executáveis deixados pra trás caso existam.
clean:
	rm -f $(OUTPUT) $(OBJS) $(MAIN_OBJ)

.PHONY: all run clean

# Nome do projeto
PROJ_NAME = tp1

# Arquivos .c
C_SOURCE = image.c main.c

# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -std=c99 -pedantic

# Comando para executar o projeto
RUN_CMD = ./$(PROJ_NAME)

# Alvo padrão: compila e executa o projeto
all: $(PROJ_NAME)
	$(RUN_CMD)

# Alvo para compilar o projeto
$(PROJ_NAME): $(C_SOURCE)
	$(CC) $(CFLAGS) $^ -o $@

# Alvo para limpar arquivos compilados e executáveis
clean:
	rm -f $(PROJ_NAME)

.PHONY: all clean

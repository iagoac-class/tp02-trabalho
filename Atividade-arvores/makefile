# Nome do compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -Wextra -g

# Nome do executável
EXEC = arvores

# Fonte e objetos
SRCS = arvores.c 
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos .c em .o
# Você pode executar o programa com make run arg=1 (ou substitua 1 pelo número da instância que deseja testar).
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJS) $(EXEC)

# Regra para executar o programa
run: $(EXEC)
	./$(EXEC) $(arg)

.PHONY: all clean run
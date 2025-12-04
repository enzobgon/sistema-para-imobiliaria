# Compilador a ser utilizado
CC = gcc

# Flags de Compilação (CFLAGS)
# -Wall -Wextra: Ativa avisos para ajudar a identificar erros.
# -g: Adiciona informações de debug.
# -I: Indica onde estão os arquivos de cabeçalho (.h) do MySQL.
# (Nota: Em Linux é padrão /usr/include/mysql. Em Windows/Mac pode variar).
CFLAGS = -Wall -Wextra -g -I/usr/include/mysql

# Flags de Linkagem (LDFLAGS)
# -L: Indica onde está a biblioteca binária do MySQL.
# -lmysqlclient: O nome da biblioteca que o compilador deve buscar.
LDFLAGS = -L/usr/lib/mysql -lmysqlclient

# Nome do executável final que será gerado
TARGET = sistema_imobiliaria

# Lista de todos os arquivos fonte do projeto
SRCS = main.c menu.c conexao.c cliente.c imovel.c corretor.c fiador.c negociacao.c consulta.c

# Transforma a lista de .c em .o (Objetos compilados) automaticamente
OBJS = $(SRCS:.c=.o)

# Regra padrão (o que acontece quando você digita apenas 'make')
all: $(TARGET)

# Regra de Linkagem: Junta todos os objetos (.o) para criar o executável final
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Regra de Compilação: Transforma cada .c em um .o individualmente
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de Limpeza: Apaga o executável e os arquivos .o (digite 'make clean')
clean:
	rm -f $(OBJS) $(TARGET)

# Regra de Execução: Compila (se necessário) e roda o programa (digite 'make run')
run: $(TARGET)
	./$(TARGET)

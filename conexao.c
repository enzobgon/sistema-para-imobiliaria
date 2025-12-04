#include <stdio.h>
#include <stdlib.h>
#include "conexao.h"

// Configurações do Banco de Dados
#define SERVER "localhost"
#define USER "root"
#define PASSWORD "SUA_SENHA_AQUI" // Alterar para senha local
#define DATABASE "imobiliaria"

MYSQL *conectar() {
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "Falha na inicializacao do mysql_init()\n");
        exit(1);
    }

    if (mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Erro de conexao com o banco de dados: %s\n", mysql_error(conn));
        exit(1);
    }

    return conn;
}

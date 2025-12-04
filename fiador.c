#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fiador.h"
#include "conexao.h"

// Estruturas semelhantes as implementadas no Cliente.c.
// Função de Cadastro de Fiador (É possível cadastrar 1 por vez).
void cadastrarFiador() {
    MYSQL *conn = conectar();
    char query[500];
    int id_inquilino, qtd_fiadores;
    char nome[100], telefone[20];
    float saldo_bancario;

    printf("\nCadastro de Fiadores\n");
    // Qual inquilino deve ser associado ao fiador em questão!
    printf("ID do Inquilino: ");
    scanf("%d", &id_inquilino);
    getchar();

    printf("Quantos fiadores deseja cadastrar?: ");
    scanf("%d", &qtd_fiadores);
    getchar();

    if (qtd_fiadores < 2)
        printf("Lembrete: 2 fiadores por inquilino e o minimo para fechamento de contrato!\n");     // Apenas um aviso.

    for (int i = 0; i < qtd_fiadores; i++) {
        printf("\nCadastrando Fiador %d\n", i + 1);

        // 'stdin' preferível para evitar que espaços sejam contabilizados!
        printf("Nome: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = 0;

        printf("Telefone: ");
        fgets(telefone, sizeof(telefone), stdin);
        telefone[strcspn(telefone, "\n")] = 0;

        printf("Saldo Bancario: ");
        scanf("%f", &saldo_bancario);
        getchar();

        snprintf(query, sizeof(query),
                 "INSERT INTO Fiador (id_inquilino, nome, telefone, saldo_bancario) "
                 "VALUES (%d, '%s', '%s', %.2f)", id_inquilino, nome, telefone, saldo_bancario);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Erro ao cadastrar fiador: %s\n", mysql_error(conn));
        } else {
            printf("Fiador cadastrado com sucesso!\n");
        }
    }

    mysql_close(conn);
}
// Função para listar Fiadores (Em ordem crescente ao id)
void listarFiadores() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[] = "SELECT f.id_fiador, f.nome, f.telefone, f.saldo_bancario, i.id_inquilino, c.nome "
                   "FROM Fiador f "
                   "JOIN Inquilino i ON f.id_inquilino = i.id_inquilino "
                   "JOIN Cliente c ON i.id_inquilino = c.id_cliente "
                   "ORDER BY f.id_fiador ASC";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar fiadores: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Erro ao armazenar resultado: %s\n", mysql_error(conn));
        return;
    }

    // Mesmo padrão de "tabela" será apresentada em todo o código.
    printf("\nLista de Fiadores:\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("ID | Nome                     | Telefone      | Saldo Bancario | ID Inquilino | Nome Inquilino\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-2s | %-24s | %-13s | R$%-12s | %-12s | %-15s\n",
               row[0], row[1], row[2], row[3], row[4], row[5]);
    }

    printf("-----------------------------------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}
// Função para deletar Fiador (Pode gerar problemas).
void deletarFiador() {
    MYSQL *conn = conectar();
    int id_fiador;

    printf("\nExcluir Fiador\n");
    printf("Digite o ID do fiador: ");
    scanf("%d", &id_fiador);
    getchar();

    char query[128];
    snprintf(query, sizeof(query), "DELETE FROM Fiador WHERE id_fiador = %d", id_fiador);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao excluir fiador: %s\n", mysql_error(conn));
    } else {
        printf("Fiador excluido com sucesso!\n"); // ON DELETE CASCATE com FK id_inquilino.
    }

    mysql_close(conn);
}

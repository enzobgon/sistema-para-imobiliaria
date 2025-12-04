#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corretor.h"
#include "conexao.h"
// Semelhante as outras funções de cadastro, modificação e registro!
void cadastrarCorretor() {
    MYSQL *conn = conectar();
    char nome[200], creci[50], telefone[20];
    char data_prestacao[11];
    float comissao;

    printf("\nCadastro de Corretor\n");

    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("CRECI (Formato: CRECI-RJ 1234 F): ");
    fgets(creci, sizeof(creci), stdin);
    creci[strcspn(creci, "\n")] = 0;

    printf("Telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = 0;

    printf("Data de inicio da prestacao (YYYY-MM-DD): ");
    scanf("%10s", data_prestacao);
    getchar();
    // DECIMAL (5,2)
    printf("Comissao (Percentual): ");
    scanf("%f", &comissao);
    getchar();

    char query[500];
    snprintf(query, sizeof(query),
        "INSERT INTO Corretor (nome, creci, telefone, data_prestacao, comissao) "
        "VALUES ('%s', '%s', '%s', '%s', %.2f)",
        nome, creci, telefone, data_prestacao, comissao);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao cadastrar corretor: %s\n", mysql_error(conn));
    } else {
        printf("Corretor cadastrado com sucesso!\n");
    }

    mysql_close(conn);
}

void listarCorretores() {
    MYSQL *conn = conectar();
    MYSQL_RES *res; // Armazenar o resultado.
    MYSQL_ROW row;  // Percorrer o resultado.

    char query[] = "SELECT id_corretor, nome, creci, telefone, data_prestacao, comissao FROM Corretor ORDER BY id_corretor ASC";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar corretores: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Erro ao armazenar resultado: %s\n", mysql_error(conn));
        return;
    }

    printf("\nLista de Corretores:\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("ID | Nome                 | CRECI           | Telefone      | Inicio Servico | Comissao\n");
    printf("------------------------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-2s | %-20s | %-15s | %-13s | %-14s | %.2f%%\n",
               row[0], row[1], row[2], row[3], row[4], atof(row[5]));
    }

    printf("------------------------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}

void modificarCorretor() {
    MYSQL *conn = conectar();
    int id, opcao;
    char novo_telefone[20];
    float nova_comissao;
    char query[200];

    printf("\nModificar Corretor\n");
    printf("Digite o ID do corretor: ");
    scanf("%d", &id);
    getchar();

    printf("\nEscolha o que deseja modificar:\n");
    printf("1 - Alterar telefone\n");
    printf("2 - Alterar comissao\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("Novo telefone: ");
            fgets(novo_telefone, sizeof(novo_telefone), stdin);
            novo_telefone[strcspn(novo_telefone, "\n")] = 0;

            snprintf(query, sizeof(query), "UPDATE Corretor SET telefone = '%s' WHERE id_corretor = %d", novo_telefone, id);
            break;

        case 2:
            printf("Nova comissao (exemplo: 5.50 para 5,5%%): ");
            scanf("%f", &nova_comissao);
            getchar();

            snprintf(query, sizeof(query), "UPDATE Corretor SET comissao = %.2f WHERE id_corretor = %d", nova_comissao, id);
            break;

        default:
            printf("Opcao invalida.\n");
            mysql_close(conn);
            return;
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao modificar corretor: %s\n", mysql_error(conn));
    } else {
        printf("Corretor atualizado com sucesso!\n");
    }

    mysql_close(conn);
}

void deletarCorretor() {
    MYSQL *conn = conectar();
    int id;

    printf("\nExcluir Corretor\n");
    printf("Digite o ID do corretor: ");
    scanf("%d", &id);
    getchar();

    char query[200];
    snprintf(query, sizeof(query), "DELETE FROM Corretor WHERE id_corretor = %d", id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao excluir corretor: %s\n", mysql_error(conn));
    } else {
        printf("Corretor excluido com sucesso!\n");
        // ON DELETE SET NULL, sem exclusão em tabelas relacionadas (ex: Ímoveis).
    }

    mysql_close(conn);
}
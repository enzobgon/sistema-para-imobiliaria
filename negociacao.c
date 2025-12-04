#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conexao.h"
#include "negociacao.h"
// Aqui existem as tabelas que representam todas as negociações oferecidas pela imobiliária.
// Função para marcar Visita (Pelo Inquilino).
void marcarVisita() {
    MYSQL *conn = conectar();
    int id_inquilino, id_imovel, id_corretor;
    char data_visita[20];

    printf("\nMarcar Visita\n");
    // Coleta de dados (FK da tabela).
    printf("ID do Inquilino: ");
    scanf("%d", &id_inquilino);
    getchar();

    printf("ID do Imovel: ");
    scanf("%d", &id_imovel);
    getchar();

    printf("ID do Corretor: ");
    scanf("%d", &id_corretor);
    getchar();

    printf("Data da Visita (YYYY-MM-DD HH:MM:SS): ");
    scanf("%19s", data_visita);
    getchar();

    char query[300]; // Querry para conferir a situação do imóvel (disponível ou não).
    snprintf(query, sizeof(query),
             "SELECT situacao FROM Imovel WHERE id_imovel = %d AND situacao = 'Disponivel'", id_imovel);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao verificar disponibilidade: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL || mysql_num_rows(res) == 0) {
        printf("O imovel nao esta disponivel para visita.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return;
    }
    mysql_free_result(res);

    snprintf(query, sizeof(query),
             "INSERT INTO Visita (id_inquilino, id_imovel, id_corretor, data_visita) "
             "VALUES (%d, %d, %d, '%s')", id_inquilino, id_imovel, id_corretor, data_visita);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao marcar visita: %s\n", mysql_error(conn));
    } else {
        printf("Visita marcada com sucesso!\n");
    }

    mysql_close(conn);
}

void registrarProposta() {
    MYSQL *conn = conectar();
    int id_inquilino, id_imovel;
    float valor_proposta;
    char data_proposta[11], validade[11];

    printf("\nRegistrar Proposta\n");

    printf("ID do Inquilino: ");
    scanf("%d", &id_inquilino);
    getchar();

    printf("ID do Imovel: ");
    scanf("%d", &id_imovel);
    getchar();

    printf("Valor da Proposta: ");
    scanf("%f", &valor_proposta);
    getchar();

    printf("Data da Proposta (YYYY-MM-DD): ");
    scanf("%10s", data_proposta);
    getchar();

    printf("Data de Validade (YYYY-MM-DD): ");
    scanf("%10s", validade);
    getchar();

    char query[300];
    snprintf(query, sizeof(query),
             "SELECT situacao FROM Imovel WHERE id_imovel = %d AND situacao = 'Disponivel'", id_imovel);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao verificar disponibilidade: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL || mysql_num_rows(res) == 0) {
        printf("Erro: O imovel nao esta disponivel para propostas.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return;
    }
    mysql_free_result(res);

    snprintf(query, sizeof(query),
             "INSERT INTO Proposta (id_inquilino, id_imovel, valor_proposta, data_proposta, validade) "
             "VALUES (%d, %d, %.2f, '%s', '%s')", id_inquilino, id_imovel, valor_proposta, data_proposta, validade);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao registrar proposta: %s\n", mysql_error(conn));
    } else {
        printf("Proposta registrada com sucesso!\n");
    }

    mysql_close(conn);
}

void firmarContrato() {
    MYSQL *conn = conectar();
    int id_proposta, id_inquilino;

    printf("\nFirmar Contrato\n");

    printf("ID da Proposta: ");
    scanf("%d", &id_proposta);
    getchar();

    char query[300];
    snprintf(query, sizeof(query),
             "SELECT id_inquilino FROM Proposta WHERE id_proposta = %d AND validade >= CURDATE()", id_proposta);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao verificar validade da proposta: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL || mysql_num_rows(res) == 0) {
        printf("Erro: A proposta nao e valida ou ja expirou.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    id_inquilino = atoi(row[0]); 
    mysql_free_result(res);

    snprintf(query, sizeof(query),
             "SELECT COUNT(*) FROM Fiador WHERE id_inquilino = %d", id_inquilino);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao verificar fiadores: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    int total_fiadores = atoi(row[0]);
    mysql_free_result(res);

    if (total_fiadores < 2) {
        printf("Erro: O inquilino nao possui pelo menos dois fiadores.\n");
        mysql_close(conn);
        return;
    }

    snprintf(query, sizeof(query),
             "INSERT INTO Contrato (id_proposta, duracao, valor_inicial) "
             "VALUES (%d, (SELECT duracao FROM Proposta WHERE id_proposta = %d), "
             "(SELECT valor_proposta FROM Proposta WHERE id_proposta = %d))",
             id_proposta, id_proposta, id_proposta);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao firmar contrato: %s\n", mysql_error(conn));
    } else {
        printf("Contrato firmado com sucesso!\n");
    }

    mysql_close(conn);
}

void listarVisitas() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[] =
        "SELECT id_visita, id_inquilino, id_imovel, id_corretor, data_visita "
        "FROM Visita ORDER BY data_visita ASC";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar visitas: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Erro ao armazenar resultado: %s\n", mysql_error(conn));
        return;
    }

    printf("\nLista de Visitas:\n");
    printf("-----------------------------------------------------------------------\n");
    printf(" ID  | Inquilino ID | Imovel ID | Corretor ID | Data\n");
    printf("----------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf(" %-3s | %-12s | %-9s | %-11s | %s\n",
               row[0], row[1], row[2], row[3], row[4]);
    }

    printf("--------------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}

void cancelarVisita() {
    MYSQL *conn = conectar();
    int id_visita;
    char query[150];

    printf("\nCancelar Visita\n");
    printf("Digite o ID da visita a ser cancelada: ");
    scanf("%d", &id_visita);
    getchar();

    char confirmacao;
    printf("Tem certeza que deseja cancelar a visita ID %d? (S/N): ", id_visita);
    scanf("%c", &confirmacao);
    getchar();

    if (confirmacao != 'S' && confirmacao != 's') {
        printf("Operacao cancelada.\n");
        mysql_close(conn);
        return;
    }

    snprintf(query, sizeof(query), "DELETE FROM Visita WHERE id_visita = %d", id_visita);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao cancelar visita: %s\n", mysql_error(conn));
    } else {
        printf("Visita cancelada com sucesso!\n");
    }

    mysql_close(conn);
}

void listarProposta() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Querry para buscar todas as propostas ordenadas por data
    char query[] =
        "SELECT id_proposta, id_inquilino, id_imovel, valor_proposta, data_proposta, validade "
        "FROM Proposta ORDER BY data_proposta ASC";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar propostas: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Erro ao armazenar resultado: %s\n", mysql_error(conn));
        return;
    }

    printf("\nLista de Propostas:\n");
    printf("---------------------------------------------------------------------------------\n");
    printf(" ID  | Inquilino ID | Imovel ID | Valor Proposta | Data Proposta  | Validade \n");
    printf("---------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf(" %-3s | %-12s | %-9s | R$ %-12s | %-13s | %-10s\n",
               row[0], row[1], row[2], row[3], row[4], row[5]);
    }

    printf("---------------------------------------------------------------------------------\n");

    // Libera memória e fecha conexão
    mysql_free_result(res);
    mysql_close(conn);
}
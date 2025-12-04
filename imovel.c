#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imovel.h"
#include "conexao.h"
#include "corretor.h"
// Semelhante as outras funções de cadastro, modificação e registro!
void cadastrarImovel() {
    MYSQL *conn = conectar();
    char query[512];
    int id_proprietario, id_corretor,num_comodos, vagas_garagem;
    char tipo[20], cidade[50], bairro[50], rua[100], numero[10], data_oferta[11];
    float area, valor_aluguel;

    printf("\nCadastro de Imovel\n");

    printf("ID do Proprietario: ");
    scanf("%d", &id_proprietario);
    getchar();

    printf("ID do Corretor ('0' se ainda nao tiver): ");
    scanf("%d", &id_corretor);
    getchar();

    printf("Tipo (Casa/Apartamento/Kitnet): ");
    scanf("%19s", tipo);
    getchar();

    printf("Numero de Comodos: ");
    scanf("%d", &num_comodos);
    getchar();

    printf("Vagas de Garagem: ");
    scanf("%d", &vagas_garagem);
    getchar();

    printf("Area Construida (m2): ");
    scanf("%f", &area);
    getchar();

    printf("Cidade: ");
    fgets(cidade, sizeof(cidade), stdin);
    cidade[strcspn(cidade, "\n")] = 0;

    printf("Bairro: ");
    fgets(bairro, sizeof(bairro), stdin);
    bairro[strcspn(bairro, "\n")] = 0;

    printf("Rua: ");
    fgets(rua, sizeof(rua), stdin);
    rua[strcspn(rua, "\n")] = 0;

    printf("Numero: ");
    fgets(numero, sizeof(numero), stdin);
    numero[strcspn(numero, "\n")] = 0;

    printf("Valor do Aluguel: ");
    scanf("%f", &valor_aluguel);
    getchar();

    printf("Data da Oferta (YYYY-MM-DD): ");
    scanf("%10s", data_oferta);
    getchar();

    if (id_corretor == 0) { // Corretor não precisa ser apresentado imediatamente.
    snprintf(query, sizeof(query),
        "INSERT INTO Imovel (id_proprietario, id_corretor, tipo, num_comodos, vagas_garagem, area, cidade, bairro, rua, numero, valor_aluguel, data_oferta) "
        "VALUES (%d, NULL, '%s', %d, %d, %.2f, '%s', '%s', '%s', '%s', %.2f, '%s')",
        id_proprietario, tipo, num_comodos, vagas_garagem, area, cidade, bairro, rua, numero, valor_aluguel, data_oferta);
    } else {
    snprintf(query, sizeof(query),
        "INSERT INTO Imovel (id_proprietario, id_corretor, tipo, num_comodos, vagas_garagem, area, cidade, bairro, rua, numero, valor_aluguel, data_oferta) "
        "VALUES (%d, %d, '%s', %d, %d, %.2f, '%s', '%s', '%s', '%s', %.2f, '%s')",
        id_proprietario, id_corretor, tipo, num_comodos, vagas_garagem, area, cidade, bairro, rua, numero, valor_aluguel, data_oferta);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao cadastrar imovel: %s\n", mysql_error(conn));
    } else {
        printf("Imovel cadastrado com sucesso!\n");
    }

    mysql_close(conn);
}

void listarImoveis() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[] =
        "SELECT i.id_imovel, i.tipo, i.num_comodos, i.vagas_garagem, i.area, i.cidade, i.bairro, i.rua, i.numero, i.valor_aluguel, i.data_oferta, "
        "p.nome AS proprietario, c.nome AS corretor, i.situacao "
        "FROM Imovel i "
        "JOIN Proprietario pr ON i.id_proprietario = pr.id_proprietario "
        "JOIN Cliente p ON pr.id_proprietario = p.id_cliente "
        "LEFT JOIN Corretor c ON i.id_corretor = c.id_corretor " // Corretor nulls existem
        "ORDER BY i.id_imovel ASC";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar imoveis: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Erro ao armazenar resultado: %s\n", mysql_error(conn));
        return;
    }

    printf("\nLista de Imoveis:\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("ID | Tipo        | Comodos | Vagas | Area   | Cidade       | Bairro   | Rua                 | Num  | Valor Aluguel | Oferta     | Proprietario      | Corretor       | Situacao\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-2s | %-11s | %-7s | %-5s | %-6s | %-12s | %-8s | %-19s | %-4s | R$%-11s | %-10s | %-17s | %-14s | %-12s \n",
               row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11], row[12], row[13]);
    }

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}

void modificarImovel() {
    MYSQL *conn = conectar();
    int id, opcao, id_novo_corretor;
    float novo_valor;
    char query[256];

    printf("\nModificar Imovel\n");
    printf("Digite o ID do imovel: ");
    scanf("%d", &id);
    getchar();

    printf("\nEscolha o que deseja modificar:\n");
    printf("1 - Alterar valor do aluguel\n");
    printf("2 - Adicionar ou modificar corretor responsavel\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("Novo valor do aluguel: ");
            scanf("%f", &novo_valor);
            getchar();

            snprintf(query, sizeof(query), "UPDATE Imovel SET valor_aluguel = %.2f WHERE id_imovel = %d", novo_valor, id);
            break;

        case 2:
            printf("Digite o ID do novo corretor (ou 0 para remover o corretor atual): ");
            scanf("%d", &id_novo_corretor);
            getchar();

            if (id_novo_corretor == 0) {
                snprintf(query, sizeof(query), "UPDATE Imovel SET id_corretor = NULL WHERE id_imovel = %d", id);
            } else {
                snprintf(query, sizeof(query), "UPDATE Imovel SET id_corretor = %d WHERE id_imovel = %d", id_novo_corretor, id);
            }
            break;

        default:
            printf("Opcao invalida.\n");
            mysql_close(conn);
            return;
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao modificar imovel: %s\n", mysql_error(conn));
    } else {
        printf("Imovel atualizado com sucesso!\n");
    }

    mysql_close(conn);
}

void deletarImovel() {
    MYSQL *conn = conectar();
    int id;

    printf("\nExcluir Imovel\n");
    printf("Digite o ID do imovel: ");
    scanf("%d", &id);
    getchar();

    char query[128];
    snprintf(query, sizeof(query), "DELETE FROM Imovel WHERE id_imovel = %d", id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao excluir imovel: %s\n", mysql_error(conn));
    } else {
        printf("Imovel excluido com sucesso!\n");
    }

    mysql_close(conn);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consulta.h"
#include "conexao.h"

// 1 - Todos os clientes cadastrados que ja fizeram alguma proposta
void clientesComPropostas() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;


    char query[] = // Querry do problema:
        "SELECT c.id_cliente, c.nome, c.cpf, c.telefone_um, COUNT(p.id_proposta) AS total_propostas "
        "FROM Cliente c "
        "JOIN Inquilino i ON c.id_cliente = i.id_inquilino "
        "JOIN Proposta p ON i.id_inquilino = p.id_inquilino "
        "GROUP BY c.id_cliente, c.nome, c.cpf, c.telefone_um "
        "ORDER BY total_propostas DESC";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar clientes com propostas: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    printf("\nLista de todos os clientes cadastrados que ja fizeram alguma proposta:");
    printf("\n--------------------------------------------------------------------------------\n");
    printf("ID | Nome                 | CPF         | Telefone       | Total de Propostas\n");
    printf("---------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-2s | %-20s | %-11s | %-14s | %-2s\n",
               row[0], row[1], row[2], row[3], row[4]);
    }

    printf("---------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}

// 2 - Listar todos os imoveis (Está em imovel.c)

// 3 - Listar as propostas feitas para um determinado imóvel
void propostasPorImovel() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;
    int id_imovel;

    printf("\nDigite o ID do imovel: ");
    scanf("%d", &id_imovel);
    getchar();

    char query[250];
    snprintf(query, sizeof(query),
             "SELECT p.id_proposta, c.nome, p.valor_proposta, p.data_proposta "
             "FROM Proposta p "
             "JOIN Inquilino i ON p.id_inquilino = i.id_inquilino "
             "JOIN Cliente c ON i.id_inquilino = c.id_cliente "
             "WHERE p.id_imovel = %d "
             "ORDER BY p.data_proposta DESC", id_imovel);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar propostas para o imovel: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    printf("\nTodas as proposta feitas para o imovel %d:",id_imovel);
    printf("\n------------------------------------------------------------------------\n");
    printf("Proposta ID | Nome do Inquilino      | Valor     | Data da Proposta\n");
    printf("-------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-11s | %-22s | R$%-7s | %s\n",
               row[0], row[1], row[2], row[3]);
    }

    printf("-------------------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}


// 4 - Informar o corretor que obteve maior rendimento no ano de um determinado ano
void corretorMaiorRendimento() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;
    int ano;

    printf("\nDigite o ano para verificar o corretor com maior rendimento: ");
    scanf("%d", &ano);
    getchar();

    char query[1000]; // Comissão recebida está relacionada com o valor do aluguel e tempo de contrato nas regras de negócio.
    snprintf(query, sizeof(query),
            "SELECT c.id_corretor, c.nome, "
            "SUM(i.valor_aluguel * (c.comissao / 100) * co.duracao) AS rendimento_total "
            "FROM Contrato co "
            "JOIN Proposta p ON co.id_proposta = p.id_proposta "
            "JOIN Imovel i ON p.id_imovel = i.id_imovel "
            "JOIN Corretor c ON i.id_corretor = c.id_corretor "
            "WHERE YEAR(p.data_proposta) = %d "  // Usa data da proposta para filtrar o ano
            "GROUP BY c.id_corretor, c.nome "
            "ORDER BY rendimento_total DESC "
            "LIMIT 1", ano);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao consultar corretor com maior rendimento: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    if (row && row[2] != NULL) {
        printf("\nO corretor com maior arrecadamento:");
        printf("\n----------------------------------------------------------------\n");
        printf("Corretor ID | Nome Corretor        | Arrecadamento no Ano (%d)\n", ano);
        printf("-----------------------------------------------------------------\n");
        printf("%-11s | %-20s | R$ %-8s\n", row[0], row[1], row[2]);
        printf("-----------------------------------------------------------------\n");
    } else {
        printf("\nNenhum corretor teve rendimento registrado para o ano %d.\n", ano);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

// 5 - 3 Imóveis mais caros
void tresImoveisMaisCaros() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[] =
        "SELECT i.id_imovel, i.tipo, i.valor_aluguel, c.nome AS proprietario "
        "FROM Imovel i "
        "JOIN Proprietario p ON i.id_proprietario = p.id_proprietario "
        "JOIN Cliente c ON p.id_proprietario = c.id_cliente "
        "ORDER BY i.valor_aluguel DESC "
        "LIMIT 3";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar imóveis mais caros: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);

    printf("\nOs 3 imoveis mais caros ofertados:");
    printf("\n-----------------------------------------------------------\n");
    printf("ID | Tipo       | Valor Aluguel | Proprietario\n");
    printf("-----------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-2s | %-10s | R$ %-10s | %-20s\n", row[0], row[1], row[2], row[3]);
    }

    printf("-----------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}


// 6 - Listar propostas sem contratos
void propostasSemContratos() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[] = 
        "SELECT p.id_proposta, p.id_imovel, c.nome, p.valor_proposta, p.data_proposta, p.validade "
        "FROM Proposta p "
        "JOIN Inquilino i ON p.id_inquilino = i.id_inquilino "
        "JOIN Cliente c ON i.id_inquilino = c.id_cliente "
        "LEFT JOIN Contrato co ON p.id_proposta = co.id_proposta "      // LEFT JOIN Contrato gera "contratos" com propostas nulas
        "WHERE co.id_proposta IS NULL";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar propostas sem contratos: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);

    printf("\nLista de propostas sem contrato firmado:");
    printf("\n------------------------------------------------------------------------------------\n");
    printf("Proposta ID | Imovel ID | Inquilino          | Valor      | Data       | Validade\n");
    printf("------------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-11s | %-9s | %-18s | R$ %-6s | %-10s | %-10s\n",
               row[0], row[1], row[2], row[3], row[4], row[5]);
    }

    printf("------------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}


// 7 - Listar imóveis mais visitados, ao lado do número de visitas
void imoveisMaisVisitados() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[] = 
        "SELECT i.id_imovel, c.nome AS proprietario, co.nome AS corretor, COUNT(v.id_visita) AS total_visitas " // COUNT id_visita sempre será distinto, já que id_visita é pk auto_increment.
        "FROM Visita v "
        "JOIN Imovel i ON v.id_imovel = i.id_imovel "
        "JOIN Proprietario p ON i.id_proprietario = p.id_proprietario "
        "JOIN Cliente c ON p.id_proprietario = c.id_cliente "
        "JOIN Corretor co ON v.id_corretor = co.id_corretor "
        "GROUP BY i.id_imovel, c.nome, co.nome "
        "ORDER BY total_visitas DESC";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar imóveis mais visitados: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);

    printf("\nLista de imoveis mais visitados:");
    printf("\n-----------------------------------------------------------------\n");
    printf("ID | Proprietario       | Corretor           | Total de Visitas\n");
    printf("-----------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-2s | %-18s | %-18s | %-5s\n", row[0], row[1], row[2], row[3]);
    }

    printf("-----------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}

// 8 - Mostrar imóveis até 3000 reais
void imoveisAbaixo3000() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[] =
        "SELECT i.id_imovel, i.tipo, i.num_comodos, i.vagas_garagem, i.area, i.cidade, "
        "i.bairro, i.rua, i.numero, i.valor_aluguel, i.data_oferta, "
        "p.nome AS proprietario, c.nome AS corretor "
        "FROM Imovel i "
        "JOIN Proprietario pr ON i.id_proprietario = pr.id_proprietario "
        "JOIN Cliente p ON pr.id_proprietario = p.id_cliente "
        "LEFT JOIN Corretor c ON i.id_corretor = c.id_corretor "
        "WHERE i.valor_aluguel <= 3000 "    // Valores menores <= 3000
        "ORDER BY i.valor_aluguel ASC";     // Ordem crescente

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar imóveis abaixo de R$3000: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);

    printf("\nLista de imoveis ate 3000 reais:");
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("ID | Tipo        | Comodos | Vagas | Area   | Cidade       | Bairro   | Rua                 | Num  | Valor Aluguel | Oferta     | Proprietario      | Corretor\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-2s | %-11s | %-7s | %-5s | %-6s | %-12s | %-8s | %-19s | %-4s | R$%-11s | %-10s | %-17s | %-10s\n",
               row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11], row[12]);
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}
// Função para filtrar imóveis por cidade
void imoveisPorCidade() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;
    char cidade[50];

    printf("\nDigite a cidade: ");
    fgets(cidade, sizeof(cidade), stdin);
    cidade[strcspn(cidade, "\n")] = 0;

    char query[500];
    snprintf(query, sizeof(query),
             "SELECT i.id_imovel, i.tipo, i.num_comodos, i.vagas_garagem, i.area, i.cidade, "
             "i.bairro, i.rua, i.numero, i.valor_aluguel, i.data_oferta, "
             "cl.nome AS proprietario, c.nome AS corretor "
             "FROM Imovel i "
             "JOIN Proprietario p ON i.id_proprietario = p.id_proprietario "
             "JOIN Cliente cl ON p.id_proprietario = cl.id_cliente "
             "LEFT JOIN Corretor c ON i.id_corretor = c.id_corretor "
             "WHERE i.cidade = '%s'", cidade);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar imóveis da cidade %s: %s\n", cidade, mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);

    printf("\nLista de Imoveis na cidade %s:\n", cidade);
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("ID | Tipo        | Comodos | Vagas | Area   | Cidade       | Bairro   | Rua                 | Num  | Valor Aluguel | Oferta     | Proprietario      | Corretor\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-2s | %-11s | %-7s | %-5s | %-6s | %-12s | %-8s | %-19s | %-4s | R$%-11s | %-10s | %-17s | %-10s\n",
               row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11], row[12]);
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}


// 10 - Listar o maior proprietário de imóveis, com o total de imóveis ofertados
void maiorProprietario() {
    MYSQL *conn = conectar();
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[] =
        "SELECT p.id_proprietario, c.nome, COUNT(i.id_imovel) AS total_imoveis "
        "FROM Imovel i "
        "JOIN Proprietario p ON i.id_proprietario = p.id_proprietario "
        "JOIN Cliente c ON p.id_proprietario = c.id_cliente "
        "GROUP BY p.id_proprietario, c.nome "
        "ORDER BY total_imoveis DESC "
        "LIMIT 1";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar maior proprietário: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    
    printf("\nProprietario com mais imoveis registrados:");
    printf("\n----------------------------------------------------\n");
    printf(" ID | Nome               | Total de Imoveis\n");
    printf("----------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf(" %-2s | %-18s | %-5s\n", row[0], row[1], row[2]);
    }

    printf("----------------------------------------------------\n");

    mysql_free_result(res);
    mysql_close(conn);
}
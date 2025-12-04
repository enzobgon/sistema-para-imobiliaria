#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "conexao.h"           
// Função para Cadastrar um Cliente (Os nomes das funções são intuitivas).
void cadastrarCliente() {
    // Estebelecer conexão sempre nas funções que necessitam acessar dados e estruturas do SGBD.
    MYSQL *conn = conectar(); 

    // Coleta de atributos para inserção na tabela cliente.
    char nome[100], cpf[12], telefone1[20], telefone2[20], estado_civil[20], tipo_cliente[20];
    int id_cliente;

    printf("\nCadastro de Cliente\n");
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("CPF (11 digitos): ");
    scanf("%11s", cpf);
    getchar(); 

    printf("Telefone 1: ");
    scanf("%19s", telefone1);
    getchar();

    printf("Telefone 2 (Opcional): ");
    scanf("%19s", telefone2);
    getchar();

    printf("Estado Civil (Solteiro/Casado/Divorciado/Viuvo): ");
    scanf("%19s", estado_civil);
    getchar();

    printf("Tipo de Cliente (Proprietario/Inquilino): ");
    scanf("%19s", tipo_cliente);
    getchar();

    // Char Querry para receber a escrita da consulta.
    char query[500];
    // Comando de formatação de consulta
    snprintf(query, sizeof(query),
        "INSERT INTO Cliente (nome, cpf, telefone_um, telefone_dois, estado_civil, tipo_cliente) VALUES ('%s', '%s', '%s', '%s', '%s', '%s')",
        nome, cpf, telefone1, telefone2, estado_civil, tipo_cliente);

    // Comando de execução de consulta
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao cadastrar cliente: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Obtém o ID do cliente recém-cadastrado
    id_cliente = mysql_insert_id(conn); 

    // Cadastro de informações extras
    if (strcmp(tipo_cliente, "Proprietario") == 0) {
        char certidao_registro[40];
        char data_registro[11];

        printf("Certidao de Registro do Imovel: ");
        scanf("%39s", certidao_registro);
        getchar();

        printf("Data de Registro (YYYY-MM-DD): ");
        scanf("%10s", data_registro);
        getchar();

        snprintf(query, sizeof(query),
            "INSERT INTO Proprietario (id_proprietario, certidao_registro, data_registro) VALUES (%d, '%s', '%s')",
            id_cliente, certidao_registro, data_registro);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Erro ao cadastrar proprietario: %s\n", mysql_error(conn));
        } else {
            printf("Proprietario cadastrado com sucesso.\n");
        }
    }
    else if (strcmp(tipo_cliente, "Inquilino") == 0) {
        char profissao[50];
        float renda_familiar;

        printf("Profissao: ");
        fgets(profissao, sizeof(profissao), stdin);
        profissao[strcspn(profissao, "\n")] = 0;


        printf("Renda Familiar: ");
        scanf("%f", &renda_familiar);
        getchar();

        snprintf(query, sizeof(query),
            "INSERT INTO Inquilino (id_inquilino, profissao, renda_familiar) VALUES (%d, '%s', %.2f)",
            id_cliente, profissao, renda_familiar);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Erro ao cadastrar inquilino: %s\n", mysql_error(conn));
        } else {
            printf("Inquilino cadastrado com sucesso.\n");
        }
    }
    // Sempre encerrar a conexão
    mysql_close(conn);

}
// Função para Listar Clientes.
void listarClientes() {
    MYSQL *conn = conectar();
    MYSQL_RES *res; // Variável para armazenar resultado de consultas.
    MYSQL_ROW row;  // Variável para percorrer o o registro armazenado nela.

    char query[] = // Query para listar todos os clientes e os atributos de inquilino ou proprietario
        "SELECT c.id_cliente, c.nome, c.cpf, c.telefone_um, c.telefone_dois, c.tipo_cliente, "
        "p.certidao_registro, p.data_registro, i.profissao, i.renda_familiar "
        "FROM Cliente c "
        "LEFT JOIN Proprietario p ON c.id_cliente = p.id_proprietario "
        "LEFT JOIN Inquilino i ON c.id_cliente = i.id_inquilino";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao listar clientes: %s\n", mysql_error(conn));
        return;
    }
    // Resultado da consulta armazenado!
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Erro ao armazenar resultado: %s\n", mysql_error(conn));
        return;
    }

    // Print organizado em uma "tabela" no terminal.
    printf("\nLista de Clientes:\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("ID | Nome                 | CPF         | Telefone 1     | Telefone 2     | Tipo         | Dados Complementares\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-2s | %-20s | %-11s | %-14s | %-14s | %-12s | ",
               row[0], row[1], row[2], row[3], row[4], row[5]);
        // Se o tipo_cliete for Proprietario, será impresso as rows 6 e 7 da tabela geradas da query, que pertencem a tabela Proprietario. 
        // O Análogo com inquilino ocorre se o if falhar.
        if (strcmp(row[5], "Proprietario") == 0) {
            printf("Certidao: %-13s | Data: %-10s\n", row[6] ? row[6] : "N/A", row[7] ? row[7] : "N/A");
        } else if (strcmp(row[5], "Inquilino") == 0) {
            printf("Profissao: %-12s | Renda: %-10s\n", row[8] ? row[8] : "N/A", row[9] ? row[9] : "N/A");
        } 
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");

    // Libera o espaço alocado pela memória
    mysql_free_result(res);
    mysql_close(conn);
}
// Função para alterar alguns valores de cliente.
void modificarCliente() {
    MYSQL *conn = conectar();
    int id, opcao;
    // Uma query UPDATE para atualizar valores.
    char query[500], novo_valor[250];

    printf("\nModificar Cliente\n");
    printf("Digite o ID do cliente que deseja modificar: ");
    scanf("%d", &id);
    getchar();

    // Submenu de alterações (novamente um switch case).
    printf("\nEscolha o campo a modificar:\n");
    printf("1 - Nome\n");
    printf("2 - Telefone 1\n");
    printf("3 - Telefone 2\n");
    printf("4 - Estado Civil\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("Novo Nome: ");
            fgets(novo_valor, sizeof(novo_valor), stdin);
            novo_valor[strcspn(novo_valor, "\n")] = 0;
            snprintf(query, sizeof(query), "UPDATE Cliente SET nome = '%s' WHERE id_cliente = %d", novo_valor, id);
            break;

        case 2:
            printf("Novo Telefone 1: ");
            scanf("%19s", novo_valor);
            getchar();
            snprintf(query, sizeof(query), "UPDATE Cliente SET telefone_um = '%s' WHERE id_cliente = %d", novo_valor, id);
            break;

        case 3:
            printf("Novo Telefone 2: ");
            scanf("%19s", novo_valor);
            getchar();
            snprintf(query, sizeof(query), "UPDATE Cliente SET telefone_dois = '%s' WHERE id_cliente = %d", novo_valor, id);
            break;

        case 4:
            printf("Novo Estado Civil (Solteiro/Casado/Divorciado/Viuvo): ");
            scanf("%19s", novo_valor);
            getchar();
            snprintf(query, sizeof(query), "UPDATE Cliente SET estado_civil = '%s' WHERE id_cliente = %d", novo_valor, id);
            break;

        default:
            printf("Opcao invalida.\n");
            mysql_close(conn);
            return;
    }
    // Query registrada.
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao modificar cliente: %s\n", mysql_error(conn)); // Caso de falha, reporta erro especificado.
    } else {
        printf("Cliente atualizado com sucesso!\n");
    }

    mysql_close(conn);
}

void deletarCliente() {
    MYSQL *conn = conectar();
    int id;

    printf("\nExcluir Cliente\n");
    printf("Digite o ID do cliente: ");
    scanf("%d", &id);
    getchar();
    // Uma querry DELETE para apagar os registros.
    char query[128];
    snprintf(query, sizeof(query), "DELETE FROM Cliente WHERE id_cliente = %d", id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao excluir cliente: %s\n", mysql_error(conn));
    } else {
        printf("\nCliente excluido com sucesso!\n");
        // ON DELETE CASCADE em Proprietario e Inquilino -> Sem registros órfaõs
    }

    mysql_close(conn);
}
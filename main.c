#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>  // Biblioteca padrão do MySQL
#include "menu.h"
#include "conexao.h" 

// Trabalho de Banco de Dados - Sistema de Gerenciamento Imobiliário
// Aluno: Enzo Basaldella Gonçalves

// Recomendação: O programa está modularizado, acesse a tabela conexão 
// e depois explore o código pela ordem de chamada das funções Menu.
// Os comentários iniciais são importantes para compreender funcionalidades
// fornecidas pela Biblioteca do MySQL, que serão utilizadas repetidas vezes
// no projeto. 

void exibirMenu() {
    int opcao;
    
    do {
        printf("\nSistema de Gerenciamento Imobiliario\n");
        printf("1 - Menu de Clientes\n");
        printf("2 - Menu de Imoveis\n");
        printf("3 - Menu de Corretores\n");
        printf("4 - Menu de Fiadores\n");
        printf("5 - Menu de Negociacao\n");
        printf("6 - Menu de Consultas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuClientes();
                break;
            case 2:
                menuImoveis();
                break;
            case 3:
                menuCorretores();
                break;
            case 4:
                menuFiadores();
                break;
            case 5:
                menuNegociacao();
                break;
            case 6:
                menuConsultas();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                exit(0);
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

int main() {
    exibirMenu();
    return 0;
}
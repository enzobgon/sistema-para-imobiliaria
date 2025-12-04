#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "cliente.h"
#include "imovel.h"
#include "corretor.h"
#include "consulta.h"
#include "fiador.h"
#include "negociacao.h"

// Funções de Clientes
void cadastrarCliente();
void modificarCliente();
void deletarCliente();
void listarClientes();
// Funções de Imóveis
void cadastrarImovel();
void modificarImovel();
void deletarImovel();
void listarImoveis();
// Funções de Corretor
void cadastrarCorretor();
void modificarCorretor();
void deletarCorretor();
void listarCorretores();
// Função de Fiadores
void cadastrarFiador();
void listarFiadores();
void deletarFiador();
// Funções de Negócios
void marcarVisita();
void registrarProposta();
void firmarContrato();
void listarVisitas();
void cancelarVisita();
void listarProposta();
// Funções de Consultas Relevantes
void clientesComPropostas();
void listarImoveis();
void propostasPorImovel();
void corretorMaiorRendimento();
void tresImoveisMaisCaros();
void propostasSemContratos();
void imoveisMaisVisitados();
void imoveisAbaixo3000();
void imoveisPorCidade();
void maiorProprietario();

// Menu com funções de Cliente
void menuClientes() {                                   // Todas as funções de Menu são implementadas com um switch case
    int opcao;                                          // que redirecionam para funções de outros módulos do projeto.
                                                        
    do {
        printf("\nMenu de Clientes\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Modificar Cliente\n");
        printf("3 - Deletar Cliente\n");
        printf("4 - Listar Clientes\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                modificarCliente();
                break;
            case 3:
                deletarCliente();
                break;
            case 4:
                listarClientes();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Menu com funções de Imoveis
void menuImoveis() {
    int opcao;
    
    do {
        printf("\nMenu de Imoveis\n");
        printf("1 - Cadastrar Imovel\n");
        printf("2 - Modificar Imovel\n");
        printf("3 - Deletar Imovel\n");
        printf("4 - Listar Imoveis\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: "); 
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarImovel();
                break;
            case 2:
                modificarImovel();
                break;
            case 3:
                deletarImovel();
                break;
            case 4:
                listarImoveis();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Menu com funções de Corretores
void menuCorretores() {
    int opcao;
    
    do {
        printf("\nMenu de Corretores \n");
        printf("1 - Cadastrar Corretor\n");
        printf("2 - Modificar Corretor\n");
        printf("3 - Deletar Corretor\n");
        printf("4 - Listar Corretores\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarCorretor();
                break;
            case 2:
                modificarCorretor();
                break;
            case 3:
                deletarCorretor();
                break;
            case 4:
                listarCorretores();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Menu com funções de Fiadores
void menuFiadores() {
    int opcao;
    do {
        printf("\nMenu de Fiadores\n");
        printf("1 - Cadastrar Fiador\n");
        printf("2 - Listar Fiadores\n");
        printf("3 - Excluir Fiador\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarFiador();
                break;
            case 2:
                listarFiadores();
                break;
            case 3:
                deletarFiador();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Menu com funções de Consultas
void menuConsultas() {
    int opcao;
    do {
        printf("\nMenu de Consultas\n");
        printf("1 - Todos os clientes cadastrados que ja fizeram alguma proposta\n");
        printf("2 - Todos os imoveis cadastrados (alugados ou nao)\n");
        printf("3 - Listar as propostas feitas para um determinado imovel\n");
        printf("4 - Informar o corretor que obteve maior rendimento no ano de um determinado ano\n");
        printf("5 - Listar os 3 imoveis mais caros\n");
        printf("6 - Listar propostas sem contratos\n");
        printf("7 - Listar imoveis mais visitados\n");
        printf("8 - Mostrar imoveis ordenado por preco em ordem crescente ate 3000 reais\n");
        printf("9 - Mostrar todos os imoveis de uma determinada cidade\n");
        printf("10 - Listar maior proprietario de imoveis\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                clientesComPropostas();
                break;
            case 2: 
                listarImoveis(); 
                break;
            case 3:     
                propostasPorImovel();
                break;
            case 4: 
                corretorMaiorRendimento();
                break;
            case 5: 
                tresImoveisMaisCaros(); 
                break;
            case 6: 
                propostasSemContratos(); 
                break;
            case 7:     
                imoveisMaisVisitados(); 
                break;
            case 8: 
                imoveisAbaixo3000(); 
                break;
            case 9: 
                imoveisPorCidade(); 
                break;
            case 10: 
                maiorProprietario(); 
                break;
            case 0: 
                return;
            default: printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Menu com funções de Negociacao
void menuNegociacao() {
    int opcao;
    do {
        printf("\nMenu de Negociacoes\n");
        printf("1 - Marcar Visita\n");
        printf("2 - Registrar Proposta\n");
        printf("3 - Firmar Contrato\n");
        printf("4 - Listar Visitas\n");
        printf("5 - Cancelar Visita\n");
        printf("6 - Listar Propostas\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                marcarVisita();
                break;
            case 2:
                registrarProposta();
                break;
            case 3:
                firmarContrato();
                break;
            case 4:
                listarVisitas();
                break;
            case 5:
                cancelarVisita();
                break;
            case 6:
                listarProposta();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}
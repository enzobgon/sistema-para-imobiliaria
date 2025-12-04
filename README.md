# Sistema de Gerenciamento Imobiliário

Projeto acadêmico desenvolvido para a disciplina de Banco de Dados.

Este projeto implementa um sistema de gestão para imobiliárias utilizando Linguagem C integrada a um banco de dados MySQL. Ele garante a persistência de dados e a execução de regras de negócio via terminal, além de modelar consultas SQL complexas.

## Funcionalidades

- Arquitetura modular separando interface, conexão e lógica de negócio.

- Operações CRUD para Clientes, Imóveis, Corretores e Fiadores.

- Módulo de negociação com validação de contratos e agendamento de visitas.

- Geração de relatórios gerenciais através de consultas SQL otimizadas.

## Configuração do Banco de Dados

Importe o esquema do banco de dados no MySQL:

mysql -u root -p < banco-de-dados-imobiliaria.sql

Edite o arquivo conexao.c e atualize a senha do banco de dados na constante PASSWORD.

## Como Compilar e Executar

Compile o código usando Make:

make

Execute o programa:

./sistema_imobiliaria

## Opções do Menu

O programa interage via menus numéricos na entrada padrão.

OBS: Há diversas opções em cada módulo do código.

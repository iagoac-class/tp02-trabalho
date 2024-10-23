[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/K7_2VYVB)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=16476734&assignment_repo_type=AssignmentRepo)

# Comparação de Árvores Balanceadas e Não-Balanceadas

## Visão Geral

Neste projeto, exploramos o desempenho de árvores binárias balanceadas e não-balanceadas em C, avaliando como o balanceamento afeta a eficiência das operações de inserção e remoção. O objetivo é demonstrar a importância do balanceamento em estruturas de dados e como isso impacta o tempo de execução.

## Objetivo

O foco principal deste trabalho é comparar o tempo de execução de operações de inserção e remoção entre duas implementações:

- **Árvore Binária Não-Balanceada**: Estrutura básica que não mantém a ordem dos elementos.
- **Árvore AVL (Balanceada)**: Estrutura que ajusta automaticamente seu balanceamento após cada operação.

## Como Funciona

O programa recebe uma série de instruções de inserção e remoção de nós, medindo o tempo necessário para realizar essas operações em ambas as estruturas de dados. Ao final, são apresentados os tempos em milissegundos para cada tipo de árvore.

### Estrutura das Entradas

As entradas são fornecidas em um arquivo de texto e consistem em duas colunas:

1. Um caractere 'I' para inserção ou 'R' para remoção.
2. Um número inteiro representando o valor a ser inserido ou removido.

### Saída

O programa imprime os tempos necessários para realizar as operações em ambas as árvores:


## Autores

Este trabalho foi desenvolvido por:

- **Carlos Augusto Regis Lorim**
- **João Pedro Pereira de Freitas**
- **Gabriel Ribeiro**

## Requisitos

- Compilador C (pode ser GCC)
- Ambiente Linux (recomendado)

## Instruções de Compilação e Execução

1. **Compilação**: Utilize o comando abaixo para compilar o código.
   ```bash
   make
   ./arvores <número_da_instância>


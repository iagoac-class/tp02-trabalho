#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvores.h"

// Obtem a altura da AVL
int altura(struct Node *N) {
    if (N == NULL) {
        return 0;
    }
    return N->altura;
}

// Obtem o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Cria um novo nó com apontadores esquerda e direita nulos
struct Node* newNod(int valor) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o nó.\n");
        exit(EXIT_FAILURE);
    }
    node->valor = valor;
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 1;  // Novo nó é adicionado como folha
    return node;
}

// Faz a rotação à direita na raiz y
struct Node *direitaRotate(struct Node *y) {
    struct Node *x = y->esquerda;
    struct Node *T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    // Retorna a nova raiz
    return x;
}

// Faz a rotação à esquerda na raiz x
struct Node *esquerdaRotate(struct Node *x) {
    struct Node *y = x->direita;
    struct Node *T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    // Retorna a nova raiz
    return y;
}

// Obtem o fator de balanceamento para o nó N
int balanceamento(struct Node *N) {
    if (N == NULL) {
        return 0;
    }
    return (altura(N->esquerda) - altura(N->direita));
}

// Função recursiva para inserir um novo item na árvore com raiz
// *Node e retorna a nova raiz da subárvore
struct Node* inseriravl(struct Node* node, int valor) {
    /* 1.  Realiza a inserção normal de árvore binária */
    if (node == NULL) {
        return newNod(valor);
    }

    if (valor < node->valor) {
        node->esquerda = inseriravl(node->esquerda, valor);
    } else if (valor > node->valor) {
        node->direita = inseriravl(node->direita, valor);
    } else {
        // Valores duplicados não são permitidos na AVL
        return node;
    }

    /* 2. Atualiza a altura de seu antecessor */
    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

    /* 3. Obtem o fator de balanceamento da raiz 
    para observar se a árvore continua balanceada */
    int balance = balanceamento(node); // Se a árvore está desbalanceada, então existem quatro casos possíveis

    /* Caso esquerda esquerda
        T1, T2, T3 e T4 são sub-árvores.
          z                                      y 
         / \                                   /   \
        y   T4     Rotação direita (z)        x      z
       / \          - - - - - - - - ->      /  \    /  \ 
      x   T3                               T1  T2  T3  T4
     / \
    T1   T2                                              */
    if (balance > 1 && valor < node->esquerda->valor) {
        return direitaRotate(node);
    }

    /* Caso direita direita
      z                                y
     /  \                            /   \ 
    T1   y   Rotação esquerda (z)   z      x
        /  \   - - - - - - - ->    / \    / \
       T2   x                     T1  T2 T3  T4
           / \
         T3  T4                                  */
    if (balance < -1 && valor > node->direita->valor) {
        return esquerdaRotate(node);
    }

    /* Caso esquerda direita
         z                               z                              x
        / \                            /   \                           /  \ 
       y   T4  Rotação esquerda (y)   x    T4  Rotação direita (z)   y      z
      / \      - - - - - - - - ->    /  \       - - - - - - - ->    / \    / \
    T1   x                          y    T3                       T1  T2 T3  T4
        / \                        / \
      T2   T3                    T1   T2                                     */
    if (balance > 1 && valor > node->esquerda->valor) {
        node->esquerda = esquerdaRotate(node->esquerda);
        return direitaRotate(node);
    }

    /* Caso direita esquerda
       z                            z                            x
      / \                          / \                          /  \ 
    T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
        / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
       x   T4                      T2   y                  T1  T2  T3  T4
      / \                              /  \
    T2   T3                           T3   T4                             */
    if (balance < -1 && valor < node->direita->valor) {
        node->direita = direitaRotate(node->direita);
        return esquerdaRotate(node);
    }

    /* retorna o ponteiro (não-atualizado) para a raiz */
    return node;
}

struct Node* removeravl(struct Node* node, int valor) {
    // Se a árvore estiver vazia
    if (node == NULL) {
        return node;
    }

    // Se o valor a ser removido for menor que o valor do nó atual
    if (valor < node->valor) {
        node->esquerda = removeravl(node->esquerda, valor);
    } else if (valor > node->valor) {
        node->direita = removeravl(node->direita, valor);
    } else {
        // Nó a ser removido encontrado
        if ((node->esquerda == NULL) || (node->direita == NULL)) {
            struct Node *temp = node->esquerda ? node->esquerda : node->direita;

            // Se não tiver filhos ou apenas um filho
            if (temp == NULL) {
                temp = node;
                node = NULL; // Remover o nó
            } else {
                *node = *temp; // Copia o conteúdo do nó filho
            }
            free(temp);
        } else {
            // Nó com dois filhos: pega o menor valor da subárvore direita
            struct Node* temp = node->direita;
            while (temp && temp->esquerda != NULL) {
                temp = temp->esquerda;
            }

            // Copia o valor do nó
            node->valor = temp->valor;

            // Remove o nó
            node->direita = removeravl(node->direita, temp->valor);
        }
    }

    // Se a árvore tiver apenas um nó
    if (node == NULL) {
        return node;
    }

    return node;
}


//Talvez tenha que arrumar essa parte
//Trocar a função inserir com Node por inseriravl


double arvore_binaria(int instancia_num, struct node *root, FILE *arq) {
    double tempo = 0;
    int elementint;
    char elementchar;
    clock_t begin = clock();

    while ((elementchar = getc(arq)) != EOF) {
        if (elementchar == 'I') {
            elementint = getc(arq) - '0'; 
            root = inserir(root, elementint);
        } else if (elementchar == 'R') {
            elementint = getc(arq) - '0'; 
            root = remover(root, elementint);
        }
    }
    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;


    return (tempo);
}

double arvore_balanceada(int instancia_num, struct Node *root, FILE *arq) {
    double tempo = 0;
    int elementint;
    char elementchar;
    clock_t begin = clock();

    while ((elementchar = getc(arq)) != EOF) {
        if (elementchar == 'I') {
            elementint = getc(arq) - '0'; // Ajuste para ler o inteiro corretamente
            root = inseriravl(root, elementint);
        } else if (elementchar == 'R') {
            elementint = getc(arq) - '0'; // Ajuste para ler o inteiro corretamente
            root = removeravl(root, elementint);
        }
    }

    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

// Cria um novo nó na árvore
struct node* novo_no(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->valor = item;
    temp->esquerda = temp->direita = NULL;
    return temp;
}
 
// Inserir novo nó com determinado
// valor na árvore binária
struct node* inserir(struct node* node, int valor) {
    // Se a árvore é vazia, então cria um novo nó
    if (node == NULL) {
        return novo_no(valor);
    }
 
    // Caso contrário, faz uma busca pelo local adequado de inserção
    if (valor < node->valor) {
        node->esquerda = inserir(node->esquerda, valor);
    } else if (valor > node->valor) {
        node->direita = inserir(node->direita, valor);
    }
    
    // Retorna o ponteiro para o nó
    return node;
}

struct node* remover(struct node* node, int valor) {
    // Se a árvore estiver vazia
    if (node == NULL) {
        return node;
    }

    // Se o valor a ser removido for menor que o valor do nó atual
    if (valor < node->valor) {
        node->esquerda = remover(node->esquerda, valor);
    } else if (valor > node->valor) {
        node->direita = remover(node->direita, valor);
    } else {
        // Nó a ser removido encontrado
        if ((node->esquerda == NULL) || (node->direita == NULL)) {
            struct node *temp = node->esquerda ? node->esquerda : node->direita;

            // Se não tiver filhos ou apenas um filho
            if (temp == NULL) {
                temp = node;
                node = NULL; // Remover o nó
            } else {
                *node = *temp; // Copia o conteúdo do nó filho
            }
            free(temp);
        } else {
            // Nó com dois filhos: pega o menor valor da subárvore direita
            struct node* temp = node->direita;
            while (temp && temp->esquerda != NULL) {
                temp = temp->esquerda;
            }

            // Copia o valor do nó
            node->valor = temp->valor;

            // Remove o nó
            node->direita = remover(node->direita, temp->valor);
        }
    }

    // Se a árvore tiver apenas um nó
    if (node == NULL) {
        return node;
    }

    return node;
}


int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }

    // Define a árvore não balanceada como uma estrutura vazia
    struct node* root = NULL;
    // Define a árvore balanceada como uma estrutura vazia
    struct Node* rootavl = NULL;

    FILE *arq;

    if (instancia_num == 1){
        arq = fopen("1.txt", "r");
    } else {
        if (instancia_num == 2){
            arq = fopen("2.txt", "r");
        } else {
            arq = fopen("3.txt", "r");
        }
    }

    if (arq == NULL)
    {
        return EXIT_FAILURE;
    }

    double tempo_n_balanceada = arvore_binaria(instancia_num, root, arq);
    rewind(arq);
    double tempo_balanceada = arvore_balanceada(instancia_num, rootavl, arq);

    fclose(arq);  
 
    printf("%f\n%f\n", tempo_n_balanceada, tempo_balanceada);

    return (1);
}
#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui
struct node {
    int valor;
    struct node *esquerda, *direita;
};

struct Node {
    int valor;
    struct Node *esquerda;
    struct Node *direita;
    int altura;
};

double arvore_binaria(int instancia_num, struct node *root, FILE *arq);
double arvore_balanceada(int instancia_num, struct Node *root, FILE *arq);
struct node* novo_no(int item);
struct node* inserir(struct node* node, int valor);
int altura(struct Node *N);
int max(int a, int b);
struct Node* newNode(int valor);
struct Node *direitaRotate(struct Node *y);
struct Node *esquerdaRotate(struct Node *x);
int balanceamento(struct Node *N);
struct Node* inseriravl(struct Node* node, int valor);
struct node* remover(struct node* node, int valor);
struct Node* removeravl(struct Node* node, int valor);

#endif // _H_ARVORES
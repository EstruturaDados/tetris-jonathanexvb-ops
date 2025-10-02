#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PEÇAS 5

// Struct que representa cada peça do Tetris
typedef struct {
    char tipo; // Tipo: I, O, T, L
    int id;    // Identificador único
} Peca;

// Fila circular de peças
typedef struct {
    Peca pecas[MAX_PEÇAS];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Inicializa a fila
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = 0;
    fila->tamanho = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->tamanho == MAX_PEÇAS;
}

// Verifica se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

// Gera peça automaticamente com id sequencial
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Adiciona peça ao final da fila
int enqueue(Fila *fila, Peca peca) {
    if (filaCheia(fila)) return 0;
    fila->pecas[fila->tras] = peca;
    fila->tras = (fila->tras + 1) % MAX_PEÇAS;
    fila->tamanho++;
    return 1;
}

// Remove peça da frente da fila
int dequeue(Fila *fila, Peca *pecaRemovida) {
    if (filaVazia(fila)) return 0;
    *pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_PEÇAS;
    fila->tamanho--;
    return 1;
}

// Mostra o estado atual da fila
void mostrarFila(Fila fila) {
    printf("\nFila de pecas:\n");
    for (int i = 0; i < fila.tamanho; i++) {
        int idx = (fila.frente + i) % MAX_PEÇAS;
        printf("[%c %d] ", fila.pecas[idx].tipo, fila.pecas[idx].id);
    }
    printf("\n");
}

int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    int idAtual = 0;

    // Inicializa fila com 5 peças
    for (int i = 0; i < MAX_PEÇAS; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    int opcao;
    do {
        mostrarFila(fila);
        printf("\nMenu de Acoes:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Peca removida;
                if(dequeue(&fila, &removida)) {
                    printf("Peca jogada: [%c %d]\n", removida.tipo, removida.id);
                    // Adiciona automaticamente nova peça
                    enqueue(&fila, gerarPeca(idAtual++));
                } else {
                    printf("Fila vazia! Nenhuma peça para jogar.\n");
                }
                break;
            }
            case 2:
                if(enqueue(&fila, gerarPeca(idAtual++))) {
                    printf("Nova peça adicionada.\n");
                } else {
                    printf("Fila cheia! Nao é possivel adicionar.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

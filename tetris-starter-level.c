#include <stdio.h>
#include <stdlib.h>

#define TAM 5

// Struct da peça
struct Peca {
    char nome;   // tipo da peça: T, O, I, L
    int id;      // identificador da peça
};

// Variáveis globais da fila
struct Peca fila[TAM];
int inicio = 0;
int fim = 0;
int quantidade = 0;
int proximoId = 0;

// Função para gerar uma peça automática
struct Peca gerarPeca() {
    struct Peca nova;
    int sorteio = rand() % 4;

    if (sorteio == 0) {
        nova.nome = 'T';
    } else if (sorteio == 1) {
        nova.nome = 'O';
    } else if (sorteio == 2) {
        nova.nome = 'I';
    } else {
        nova.nome = 'L';
    }

    nova.id = proximoId;
    proximoId++;

    return nova;
}

// Verifica se a fila está vazia
int filaVazia() {
    if (quantidade == 0) {
        return 1;
    }
    return 0;
}

// Verifica se a fila está cheia
int filaCheia() {
    if (quantidade == TAM) {
        return 1;
    }
    return 0;
}

// Inserir peça no final da fila
void enfileirar() {
    if (filaCheia()) {
        printf("\nA fila esta cheia. Nao e possivel inserir nova peca.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM;
    quantidade++;

    printf("\nNova peca inserida com sucesso.\n");
}

// Remover peça da frente da fila
void desenfileirar() {
    if (filaVazia()) {
        printf("\nA fila esta vazia. Nenhuma peca para jogar.\n");
        return;
    }

    printf("\nPeca jogada: [%c %d]\n", fila[inicio].nome, fila[inicio].id);

    inicio = (inicio + 1) % TAM;
    quantidade--;
}

// Mostrar fila atual
void mostrarFila() {
    int i;
    int posicao;

    printf("\nFila de pecas:\n");

    if (filaVazia()) {
        printf("[vazia]\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        posicao = (inicio + i) % TAM;
        printf("[%c %d] ", fila[posicao].nome, fila[posicao].id);
    }

    printf("\n");
}

int main() {
    int opcao;
    int i;

    // Preenche a fila inicial com 5 peças
    for (i = 0; i < TAM; i++) {
        enfileirar();
    }

    do {
        printf("\n=============================\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("=============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                desenfileirar();
                mostrarFila();
                break;

            case 2:
                enfileirar();
                mostrarFila();
                break;

            case 3:
                mostrarFila();
                break;

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}

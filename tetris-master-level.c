#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Struct da peça
struct Peca {
    char nome;
    int id;
};

// Fila circular
struct Peca fila[TAM_FILA];
int inicio = 0;
int fim = 0;
int quantidadeFila = 0;

// Pilha
struct Peca pilha[TAM_PILHA];
int topo = -1;

// Controle do id único
int proximoId = 0;

// Gera uma nova peça automática
struct Peca gerarPeca() {
    struct Peca nova;
    int sorteio = rand() % 4;

    if (sorteio == 0) {
        nova.nome = 'I';
    } else if (sorteio == 1) {
        nova.nome = 'O';
    } else if (sorteio == 2) {
        nova.nome = 'T';
    } else {
        nova.nome = 'L';
    }

    nova.id = proximoId;
    proximoId++;

    return nova;
}

// ====================
// FUNÇÕES DA FILA
// ====================

int filaVazia() {
    return quantidadeFila == 0;
}

int filaCheia() {
    return quantidadeFila == TAM_FILA;
}

void enfileirar(struct Peca nova) {
    if (filaCheia()) {
        return;
    }

    fila[fim] = nova;
    fim = (fim + 1) % TAM_FILA;
    quantidadeFila++;
}

struct Peca desenfileirar() {
    struct Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidadeFila--;
    return removida;
}

// Pega uma peça da fila por posição lógica
// Exemplo: posicao 0 = frente da fila
struct Peca pegarDaFila(int posicao) {
    int indiceReal = (inicio + posicao) % TAM_FILA;
    return fila[indiceReal];
}

// Coloca uma peça na fila por posição lógica
void colocarNaFila(int posicao, struct Peca nova) {
    int indiceReal = (inicio + posicao) % TAM_FILA;
    fila[indiceReal] = nova;
}

// ====================
// FUNÇÕES DA PILHA
// ====================

int pilhaVazia() {
    return topo == -1;
}

int pilhaCheia() {
    return topo == TAM_PILHA - 1;
}

void empilhar(struct Peca nova) {
    if (pilhaCheia()) {
        return;
    }

    topo++;
    pilha[topo] = nova;
}

struct Peca desempilhar() {
    struct Peca removida = pilha[topo];
    topo--;
    return removida;
}

// ====================
// EXIBIÇÃO
// ====================

void mostrarFila() {
    int i;
    int indice;

    printf("Fila de pecas: ");

    if (filaVazia()) {
        printf("[vazia]");
    } else {
        for (i = 0; i < quantidadeFila; i++) {
            indice = (inicio + i) % TAM_FILA;
            printf("[%c %d] ", fila[indice].nome, fila[indice].id);
        }
    }

    printf("\n");
}

void mostrarPilha() {
    int i;

    printf("Pilha de reserva (Topo -> Base): ");

    if (pilhaVazia()) {
        printf("[vazia]");
    } else {
        for (i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n");
}

void mostrarEstado() {
    printf("\n==============================\n");
    printf("Estado atual:\n");
    mostrarFila();
    mostrarPilha();
    printf("==============================\n");
}

// ====================
// AÇÕES DO JOGO
// ====================

void inicializarFila() {
    int i;

    for (i = 0; i < TAM_FILA; i++) {
        enfileirar(gerarPeca());
    }
}

void jogarPeca() {
    struct Peca removida;

    if (filaVazia()) {
        printf("\nA fila esta vazia.\n");
        return;
    }

    removida = desenfileirar();
    printf("\nVoce jogou a peca [%c %d].\n", removida.nome, removida.id);

    // Mantém a fila cheia
    enfileirar(gerarPeca());
}

void reservarPeca() {
    struct Peca reservada;

    if (filaVazia()) {
        printf("\nA fila esta vazia.\n");
        return;
    }

    if (pilhaCheia()) {
        printf("\nA pilha esta cheia. Nao da para reservar mais pecas.\n");
        return;
    }

    reservada = desenfileirar();
    empilhar(reservada);

    printf("\nA peca [%c %d] foi enviada para a pilha.\n", reservada.nome, reservada.id);

    // Mantém a fila cheia
    enfileirar(gerarPeca());
}

void usarPecaReservada() {
    struct Peca usada;

    if (pilhaVazia()) {
        printf("\nA pilha esta vazia. Nao ha peca reservada.\n");
        return;
    }

    usada = desempilhar();
    printf("\nVoce usou a peca reservada [%c %d].\n", usada.nome, usada.id);
}

void trocarPecaAtual() {
    struct Peca temp;

    if (filaVazia()) {
        printf("\nA fila esta vazia.\n");
        return;
    }

    if (pilhaVazia()) {
        printf("\nA pilha esta vazia. Nao ha peca para trocar.\n");
        return;
    }

    temp = fila[inicio];
    fila[inicio] = pilha[topo];
    pilha[topo] = temp;

    printf("\nTroca realizada entre a frente da fila e o topo da pilha.\n");
}

void trocaMultipla() {
    struct Peca tempFila[3];
    struct Peca tempPilha[3];
    int i;

    if (quantidadeFila < 3) {
        printf("\nNao ha pelo menos 3 pecas na fila.\n");
        return;
    }

    if (topo < 2) {
        printf("\nNao ha pelo menos 3 pecas na pilha.\n");
        return;
    }

    // Guardar os 3 primeiros da fila
    for (i = 0; i < 3; i++) {
        tempFila[i] = pegarDaFila(i);
    }

    // Guardar as 3 peças da pilha
    for (i = 0; i < 3; i++) {
        tempPilha[i] = pilha[topo - i];
    }

    // Colocar as peças da pilha nos 3 primeiros da fila
    for (i = 0; i < 3; i++) {
        colocarNaFila(i, tempPilha[i]);
    }

    // Colocar as peças da fila na pilha
    for (i = 0; i < 3; i++) {
        pilha[topo - i] = tempFila[i];
    }

    printf("\nTroca multipla realizada entre os 3 primeiros da fila e as 3 pecas da pilha.\n");
}

// ====================
// MENU
// ====================

int main() {
    int opcao;

    srand(time(NULL));

    inicializarFila();

    do {
        mostrarEstado();

        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para a pilha\n");
        printf("3 - Usar peca da pilha\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
        printf("6 - Visualizar estado atual\n");
        printf("0 - Sair\n");
        printf("Opcao escolhida: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca();
                break;

            case 2:
                reservarPeca();
                break;

            case 3:
                usarPecaReservada();
                break;

            case 4:
                trocarPecaAtual();
                break;

            case 5:
                trocaMultipla();
                break;

            case 6:
                mostrarEstado();
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}

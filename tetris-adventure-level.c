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

// Pilha de reserva
struct Peca pilha[TAM_PILHA];
int topo = -1;

// Controle do id único
int proximoId = 0;

// Função para gerar peça automática
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

// Verifica se a fila está cheia
int filaCheia() {
    return quantidadeFila == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia() {
    return quantidadeFila == 0;
}

// Inserir no final da fila
void enfileirar(struct Peca nova) {
    if (filaCheia()) {
        return;
    }

    fila[fim] = nova;
    fim = (fim + 1) % TAM_FILA;
    quantidadeFila++;
}

// Remover da frente da fila
struct Peca desenfileirar() {
    struct Peca removida = fila[inicio];

    inicio = (inicio + 1) % TAM_FILA;
    quantidadeFila--;

    return removida;
}

// Verifica se a pilha está cheia
int pilhaCheia() {
    return topo == TAM_PILHA - 1;
}

// Verifica se a pilha está vazia
int pilhaVazia() {
    return topo == -1;
}

// Empilhar peça na reserva
void empilhar(struct Peca nova) {
    if (pilhaCheia()) {
        return;
    }

    topo++;
    pilha[topo] = nova;
}

// Desempilhar peça da reserva
struct Peca desempilhar() {
    struct Peca removida = pilha[topo];
    topo--;
    return removida;
}

// Mostrar fila
void mostrarFila() {
    int i, pos;

    printf("Fila de pecas: ");

    if (filaVazia()) {
        printf("[vazia]");
    } else {
        for (i = 0; i < quantidadeFila; i++) {
            pos = (inicio + i) % TAM_FILA;
            printf("[%c %d] ", fila[pos].nome, fila[pos].id);
        }
    }

    printf("\n");
}

// Mostrar pilha
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

// Mostrar estado atual do jogo
void mostrarEstado() {
    printf("\n==============================\n");
    printf("Estado atual:\n");
    mostrarFila();
    mostrarPilha();
    printf("==============================\n");
}

// Inicializar fila com peças automáticas
void inicializarFila() {
    int i;
    for (i = 0; i < TAM_FILA; i++) {
        enfileirar(gerarPeca());
    }
}

// Jogar peça da frente da fila
void jogarPeca() {
    struct Peca jogada;

    if (filaVazia()) {
        printf("\nA fila esta vazia.\n");
        return;
    }

    jogada = desenfileirar();
    printf("\nVoce jogou a peca [%c %d].\n", jogada.nome, jogada.id);

    // Mantém a fila sempre cheia
    enfileirar(gerarPeca());
}

// Reservar peça da frente da fila
void reservarPeca() {
    struct Peca reservada;

    if (filaVazia()) {
        printf("\nA fila esta vazia.\n");
        return;
    }

    if (pilhaCheia()) {
        printf("\nA pilha de reserva esta cheia.\n");
        return;
    }

    reservada = desenfileirar();
    empilhar(reservada);

    printf("\nA peca [%c %d] foi reservada.\n", reservada.nome, reservada.id);

    // Mantém a fila sempre cheia
    enfileirar(gerarPeca());
}

// Usar peça reservada
void usarPecaReservada() {
    struct Peca usada;

    if (pilhaVazia()) {
        printf("\nNao ha pecas na reserva.\n");
        return;
    }

    usada = desempilhar();
    printf("\nVoce usou a peca reservada [%c %d].\n", usada.nome, usada.id);
}

int main() {
    int opcao;

    srand(time(NULL));

    inicializarFila();

    do {
        mostrarEstado();

        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
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

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}

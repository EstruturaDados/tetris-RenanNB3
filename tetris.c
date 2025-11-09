#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

//Definindo o tamanho máximo da fila
#define MAX_FILA 5
//Definindo o tamanho máximo da pilha
#define MAX_PILHA 3


//Struct para a peça
typedef struct {
    char nome;
    int id;
} Peca;

//Struct para a fila circular
typedef struct {
    Peca elementos[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

//Struct para a pilha
typedef struct {
    Peca elementos[MAX_PILHA];
    int topo;
} Pilha;

//Função para iniciar a fila
void inicializarFila(Fila *fila){
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

//Função para iniciar a pilha
void inicializarPilha(Pilha *pilha){
    pilha->topo = -1;
}

int filaCheia(Fila *fila){
    return fila->tamanho == MAX_FILA;
}

int filaVazia(Fila *fila){
    return fila->tamanho == 0;
}

int pilhaCheia(Pilha *pilha){
    return pilha->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *pilha){
    return pilha->topo ==-1;
}



//Gerando uma nova peça
Peca gerarPeca(int id){
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    //Escolhendo um tipo aleatóriamente
    nova.nome = tipos[rand()%4];
    nova.id = id;
    return nova;

}

//Função enqueue
void enqueue(Fila *fila, Peca nova){
    if(filaCheia(fila)){
        printf("\nA fila está cheia!\n");
        return;
    }
    fila->tras = (fila->tras +1) % MAX_FILA;
    fila->elementos[fila->tras] = nova;
    fila->tamanho++;
    printf("\nA peça [%c %d] foi adicionada à fila!\n", nova.nome, nova.id);
}

//Função dequeue desenfileirada
Peca dequeue(Fila *fila) {
    Peca removida = {'-', -1};
    if (filaVazia(fila)) return removida;

    removida = fila->elementos[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_FILA;
    fila->tamanho--;
    return removida;
}

//Empilhando peça
void push(Pilha *pilha, Peca nova) {
    if (pilhaCheia(pilha)) {
        printf("\nA pilha de reserva está cheia!\n");
        return;
    }

    pilha->elementos[++pilha->topo] = nova;
    printf("\nA Peça [%c %d] foi movida para reserva.\n", nova.nome, nova.id);
}

//Desempilhando peça
Peca pop(Pilha *pilha) {
    Peca removida = {'-', -1};
    if (pilhaVazia(pilha)) {
        printf("\nNenhuma peça na reserva!\n");
        return removida;
    }

    removida = pilha->elementos[pilha->topo--];
    printf("\nPeça da reserva usada: [%c %d]\n", removida.nome, removida.id);
    return removida;
}


//Mostrando o estado da fila e da pilha atual
void mostrarEstado(Fila *fila, Pilha *pilha) {
    printf("\n Estado atual do jogo:\n");

    // Mostrando a fila
    printf("Fila de peças: ");
    if (filaVazia(fila))
        printf("(vazia)\n");
    else {
        for (int i = 0; i < fila->tamanho; i++) {
            int indice = (fila->frente + i) % MAX_FILA;
            printf("[%c %d] ", fila->elementos[indice].nome, fila->elementos[indice].id);
        }
        printf("\n");
    }

    // Mostrar pilha
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia(pilha))
        printf("(vazia)\n");
    else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->elementos[i].nome, pilha->elementos[i].id);
        }
        printf("\n");
    }
}

//Troca de peças
void trocarTopo(Fila *fila, Pilha *pilha){
    if (filaVazia(fila) || pilhaVazia(pilha)){
        printf("\nNão foi possível fazer a troca");
        return;
    }

    int indicefrente = fila->frente;
    Peca temp = fila->elementos[indicefrente];
    fila->elementos[indicefrente] = pilha->elementos[pilha->topo];
    pilha->elementos[pilha->topo] = temp;
    printf("\Troca realizada entre frente da fila e topo da pilha!\n");

}

void trocarBloco(Fila *fila, Pilha *pilha){
    if (fila->tamanho < 3 || pilha->topo < 2){
        printf("\nImpossível realizar a troca! É necessário ao menos 2 peças em cada.\n");
        return;

    }
    for (int i = 0; i < 3; i ++){
        int indice = (fila->frente +i) %MAX_FILA;
        Peca temp = fila->elementos[indice];
        fila->elementos[indice] = pilha->elementos[pilha->topo - i];
        pilha->elementos[pilha->topo -i] = temp;
    }
    printf("\Troca múltipla realizada entre as 3 primeiras da fila e as 3 da pilha!\n");

}

int main() {

    
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    srand(time(NULL));
    int idAtual = 0;

    for(int i = 0; i < MAX_FILA; i++){
        enqueue(&fila, gerarPeca(idAtual++));
    }

    int opcao;
    do{
        mostrarEstado(&fila, &pilha);
        printf("\n--- Menu de Ações ---\n");
        printf("1. Jogar peça\n");
        printf("2. Reservar peça\n");
        printf("3. Usar peça reserva\n");
        printf("4. Trocar peça da frente com o topo da pilha\n");
        printf("5. Trocar as 3 primeiras da fila com as 3 da pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma das opções: ");
        scanf("%d",&opcao);

        switch (opcao)
        {

        case 1: {
            if (filaVazia(&fila)) {
                printf("\nA fila está vazia!\n");
            } else {
                Peca jogada = dequeue(&fila);
                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
                enqueue(&fila, gerarPeca(idAtual++));
            }
            break;
        }

        case 2: { 
            if (filaVazia(&fila)) {
                printf("\n A fila está vazia!\n");
            } else if (pilhaCheia(&pilha)) {
                printf("\nA pilha está cheia!\n");
            } else {
                Peca reservada = dequeue(&fila);
                push(&pilha, reservada);
                enqueue(&fila, gerarPeca(idAtual++));
            }
            break;
        }

        case 3: {
            if (!pilhaVazia(&pilha)) {
                pop(&pilha);
            } else {
                printf("\nNenhuma peça na reserva!\n");
            }
            break;
        }

        case 4 :
            trocarTopo(&fila, &pilha);

            break;

        case 5 :
            trocarBloco(&fila, &pilha);

            break;

        case 0 :
            printf("\nSaindo...\n");

            break;
            
        default:
            printf("\nOpção inválida!");
        }
    }
    while (opcao != 0);


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}


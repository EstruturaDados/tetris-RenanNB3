#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

//Definindo o tamanho máximo da fila
#define MAX_FILA 5

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

//Função para iniciar a fila
void inicializarFila(Fila *fila){
    fila->frente = 0;
    fila->tras = 0;
    fila->tamanho = 0;
}

int filaCheia(Fila *fila){
    return fila->tamanho == MAX_FILA;
}

int filaVazia(Fila *fila){
    return fila->tamanho == 0;
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

//Função dequeue
void dequeue(Fila *fila){
    if(filaVazia(fila)){
        printf("\nFila vazia!\n");
        return;
    }

    Peca removida = fila->elementos[fila->frente];
    fila->frente = (fila->frente +1) % MAX_FILA;
    fila->tamanho--;
    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);

}

//Mostrando fila atual
void mostrarFila(Fila *fila){
    if(filaVazia(fila)){
        printf("\nFila sem elementos\n");
        return;
    }

    printf("\nFila de peças:\n");
    for(int i = 0; i<fila->tamanho; i++){
        int indice = (fila->frente + 1) %MAX_FILA;
        printf("[%c %d]", fila->elementos[indice].nome, fila->elementos[indice].id);
    }
    printf("\n"); //Adicionando espaçamentos
}

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));
    int idAtual = 0;

    for(int i = 0; i < MAX_FILA; i++){
        enqueue(&fila, gerarPeca(idAtual++));
    }

    int opcao;
    do{
        mostrarFila(&fila);
        printf("\n--- Menu de Ações ---\n");
        printf("1. Jogar peça\n");
        printf("2. Iserir nova peça\n");
        printf("0. Sair\n");
        printf("Escolha uma das opções: ");
        scanf("%d",&opcao);

        switch (opcao)
        {
        case 1 :
            dequeue(&fila);

            break;

        case 2 :
            enqueue(&fila, gerarPeca(idAtual++));
        
            break;

        case 0 :
            printf("\nSaindo...\n");

            break;
        default:
            printf("\nOpção inválida!");
        }
    }
    while (opcao != 0);
    




    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


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


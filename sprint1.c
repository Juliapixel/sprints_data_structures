/*
Data Structure and Algorithms - Sprint 1

Integrantes:
- Allan de Souza Cardoso        RM: 561721
- Eduardo Bacelar Rudner        RM: 564925
- Giovana Dias Valentini        RM: 562390
- Júlia Borges Paschoalinoto    RM: 564725
- Raquel Amaral de Oliveira     RM: 566491
*/

#include <stdlib.h> // alocação
#include <stdio.h> // lidar com I/O do stdin e stdout

// constantes para dar significado para os valors
#define PRIO_ALTA 1
#define PRIO_MEDIA 2
#define PRIO_BAIXA 3

// definição do struct Dispositivo e criação de novo tipo
typedef struct Dispositivo {
    char nome[50];
    int prioridade;
    float consumo;
} Dispositivo;

// recebe ponteiro para um Dispositivo e registra dados dele a partir do stdin
void disp_cadastrar(Dispositivo *disp) {
    printf("Nome do dispositivo: ");
    scanf(" %[^\n]", &disp->nome);
    printf("Prioridade do dispositivo (1: Alta, 2: Média, 3: Baixa): ");
    scanf(" %d", &disp->prioridade);
    while (disp->prioridade < PRIO_ALTA || disp->prioridade > PRIO_BAIXA) {
        printf("Tente novamente: ");
        scanf(" %d", &disp->prioridade);
    }
    printf("Consumo do dispositivo (kWh): ");
    scanf(" %f", &disp->consumo);
}

// pretty-printing dos detalhes do Dispositivo
void disp_mostrar(Dispositivo *disp) {
    printf("Nome: %s\n", &disp->nome);
    switch (disp->prioridade) {
        case PRIO_ALTA:
            printf("Prioridade: Alta -- Deve sempre estar operante\n");
            break;
        case PRIO_MEDIA:
            printf("Prioridade: Média -- Operação não essencial\n");
            break;
        case PRIO_BAIXA:
            printf("Prioridade: Baixa -- Operação desnecessária\n");
            break;
    }
    printf("Consumo: %.2fkWh\n", disp->consumo);
}

int main(int argc, char const *argv[]) {
    // comprimento do vetor em número de itens
    int len = 0;
    // definição de novo vetor
    Dispositivo *disps = NULL;

    printf("Cadastrador dinâmico de dispositivos\n");
    while (1) {
        // guarda a escolha do usuário nessa iteração do programa
        int escolha;

        printf("Opções:\n");
        printf("1) Cadastrar novo dispositivo\n");
        printf("2) Listar todos os dispositivos\n");
        printf("3) Sair\n");
        printf("Escolha: ");

        // recebe o número escolhido
        scanf(" %d", &escolha);
        switch (escolha) {
            case 1:
                // aumentar a capacidade do vetor alocado para o novo Dispositivo
                Dispositivo *novo_disps = realloc(disps, ++len * sizeof(Dispositivo));
                // conferir se o pointeiro ao novo vetor é válido
                if (novo_disps == NULL) {
                    printf("Erro de alocação\n");
                    // free no vetor anterior, que ainda é válido nesse caso, se já não era NULL
                    if (disps != NULL) free(disps);
                    return 1;
                } else {
                    disps = novo_disps;
                    disp_cadastrar(&disps[len - 1]);
                }
                break;
            case 2:
                if (len < 1) {
                    printf("Não há dispositivos cadastrados\n");
                    continue;
                }
                printf("Dispositivos:\n");
                for (int i = 0; i < len; i++) {
                    disp_mostrar(&disps[i]);
                    printf("================\n");
                }
                break;
            case 3:
                // essa alocação não será mais usada, então podemos chamar free
                if (disps != NULL) free(disps);
                return 0;
                break;
            default:
                printf("Por favor, escolha uma opção válida\n");
                break;
        }
    }
    return 0;
}

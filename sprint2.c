/*
Data Structure and Algorithms - Sprint 2

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

// compara dois Dispositivos, retorna -1 se lhs for "menor" que rhs, ou seja, deve aparecer
// antes na lista ordenada, 1 se for "maior" e 0 se forem iguais
int disp_cmp(Dispositivo *lhs, Dispositivo *rhs) {
    if (lhs->prioridade < rhs->prioridade) {
        return -1;
    }
    if (lhs->prioridade > rhs->prioridade) {
        return 1;
    }
    if (lhs->consumo < rhs->consumo) {
        return -1;
    }
    if (lhs->consumo > rhs->consumo) {
        return 1;
    }
    else return 0;
}

// ordena uma lista de Dispositivos usando bubble sort
void disp_sort(Dispositivo *lista, int len) {
    int trocou = 1;
    while (trocou) {
        trocou = 0;
        for (int i = 0; i<len-1; i++) {
            if (disp_cmp(&lista[i], &lista[i+1]) == 1) {
                trocou = 1;
                Dispositivo tmp = lista[i];
                lista[i] = lista[i+1];
                lista[i+1] = tmp;
            }
        }
    }
}

// calcula a soma do consumo de todos os Dispositivos da lista
float consumo_total(Dispositivo *lista, int len) {
    float total = 0.0;
    for (int i = 0; i<len; i++) {
        total += lista[i].consumo;
    }
    return total;
}

// conta quantos dos Dispositivos da lista podem ficar ligados, de acordo com a
// quantidade de energia disponível.
int disps_ligados(Dispositivo *lista, int len, float pot_disponivel) {
    float total = 0.0;
    for (int i=0; i<len; i++) {
        if (total + lista[i].consumo > pot_disponivel) {
            return i;
        }
        total += lista[i].consumo;
    }
    return len;
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
        printf("3) Simular consumo inteligente\n");
        printf("4) Sair\n");
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
                // energia disponível
                float disponivel;
                // consumo de todos os dispositivos cadastrados
                float consumo_max = consumo_total(disps, len);
                // consumo de todos os dispositivos que permancerão ligados
                float consumo_real;

                printf("Digite a quantidade de energia disponível (kWh): ");
                scanf(" %f", &disponivel);

                disp_sort(disps, len);
                if (consumo_max > disponivel) {
                    int dispositivos_ligados = disps_ligados(disps, len, disponivel);
                    consumo_real = consumo_total(disps, dispositivos_ligados);

                    printf("Aviso: o consumo total dos dispostivos cadastrados ultrapassa a potência disponível\n");

                    printf("Os seguintes dispositivos permanecerão ligados: \n");
                    for (int i=0; i<dispositivos_ligados; i++) {
                        printf("%s\n", &disps[i].nome);
                    }

                    printf("Os seguintes dispositivos serão desligados: \n");
                    for (int i=dispositivos_ligados; i<len; i++) {
                        printf("%s\n", &disps[i].nome);
                    }
                } else {
                    consumo_real = consumo_max;

                    printf("Todos os dispositivos permanecerão ligados: \n");
                    for (int i=0; i<len; i++) {
                        printf("%s\n", &disps[i].nome);
                    }
                }
                printf("O consumo total da sua casa será de %.2fkWh\n", consumo_real);
                break;
            case 4:
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

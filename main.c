/*
Data Structure and Algorithms - Sprint 3

Integrantes:
- Allan de Souza Cardoso        RM: 561721
- Eduardo Bacelar Rudner        RM: 564925
- Giovana Dias Valentini        RM: 562390
- Júlia Borges Paschoalinoto    RM: 564725
- Raquel Amaral de Oliveira     RM: 566491
*/

#include <stdlib.h> // alocação
#include <stdio.h> // lidar com I/O do stdin e stdout
#include <string.h> // usar memcpy
#include <time.h> // medição de tempo de execução
#include <unistd.h>

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

typedef struct Metricas {
    int trocas;
    int comparacoes;
} Metricas;

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
void disp_sort_bubble(Dispositivo *lista, int len, Metricas *m) {
    int trocou = 1;
    while (trocou) {
        trocou = 0;
        for (int i = 0; i<len-1; i++) {
            m->comparacoes += 1;
            if (disp_cmp(&lista[i], &lista[i+1]) == 1) {
                trocou = 1;
                m->trocas += 1;
                Dispositivo tmp = lista[i];
                lista[i] = lista[i+1];
                lista[i+1] = tmp;
            }
        }
    }
}

// ordena uma lista de Dispositivos usando selection sort
void disp_sort_selection(Dispositivo *lista, int len, Metricas *m) {
    int trocou = 1;
    for (int i = 0; i < len; i++)
    {
        int min_idx = i;
        for (int j = i; j < len; j++) {
            m->comparacoes += 1;
            if (disp_cmp(&lista[min_idx], &lista[j]) == 1) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            m->trocas += 1;
            Dispositivo tmp = lista[i];
            lista[i] = lista[min_idx];
            lista[min_idx] = tmp;
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
        printf("\n");
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
                if (len == 0) {
                    printf("Não há dispositivos cadastrados.\n");
                    break;
                }

                // energia disponível
                float disponivel;
                // consumo de todos os dispositivos cadastrados
                float consumo_max = consumo_total(disps, len);
                // consumo de todos os dispositivos que permancerão ligados
                float consumo_real;

                printf("Digite a quantidade de energia disponível (kWh): ");
                scanf(" %f", &disponivel);

                Metricas m_bubble = {0,0};
                Metricas m_selection = {0,0};

                // criar cópia da lista antes de ordenar, para manter comparação justa
                Dispositivo *tmp_disps = malloc(sizeof(Dispositivo) * len);
                if (tmp_disps == NULL) return 1;
                memcpy(tmp_disps, disps, sizeof(Dispositivo) * len);

                // Utilizamos a função POSIX clock_gettime pois ela possui
                // resolução máxima de 0.1us, enquanto clock tem resolução de
                // apenas 1ms

                // Medição do bubble sort
                struct timespec tspec_start_bubble;
                clock_gettime(CLOCK_MONOTONIC, &tspec_start_bubble);

                disp_sort_bubble(disps, len, &m_bubble);

                struct timespec tspec_end_bubble;
                clock_gettime(CLOCK_MONOTONIC, &tspec_end_bubble);
                struct timespec bubble_dur = {
                    .tv_sec = tspec_end_bubble.tv_sec - tspec_start_bubble.tv_sec,
                    .tv_nsec = tspec_end_bubble.tv_nsec - tspec_start_bubble.tv_nsec
                };

                // Medição do selection sort
                struct timespec tspec_start_selection;
                clock_gettime(CLOCK_MONOTONIC, &tspec_start_selection);

                disp_sort_selection(tmp_disps, len, &m_selection);

                struct timespec tspec_end_selection;
                clock_gettime(CLOCK_MONOTONIC, &tspec_end_selection);
                struct timespec selection_dur = {
                    .tv_sec = tspec_end_selection.tv_sec - tspec_start_selection.tv_sec,
                    .tv_nsec = tspec_end_selection.tv_nsec - tspec_start_selection.tv_nsec
                };

                free(tmp_disps);

                printf("\n===== RESULTADOS ======\n\n");

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


                printf("\n===== INFO ======\n\n");

                printf(
                    "Bubble sort levou %.6fms, fez %d comparações e %d trocas\n",
                    ((double)bubble_dur.tv_sec * 1000.0) + ((double)bubble_dur.tv_nsec / 1000000.0),
                    m_bubble.comparacoes,
                    m_bubble.trocas
                );

                printf(
                    "Selection sort levou %.6fms, fez %d comparações e %d trocas\n",
                    ((double)selection_dur.tv_sec * 1000.0) + ((double)selection_dur.tv_nsec / 1000000.0),
                    m_selection.comparacoes,
                    m_selection.trocas
                );
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
        printf("\n");
    }
    return 0;
}

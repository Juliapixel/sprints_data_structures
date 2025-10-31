# Sprints Data Structures and Algorithms

## Integrantes

- Allan de Souza Cardoso        RM: 561721
- Eduardo Bacelar Rudner        RM: 564925
- Giovana Dias Valentini        RM: 562390
- Júlia Borges Paschoalinoto    RM: 564725
- Raquel Amaral de Oliveira     RM: 566491

## Evolucão

### Sprint 1

Adição de cadastro e enumeração de dispositivos elétricos residenciais

### Sprint 2

Simulação de consumo de energia com base na prioridade dos dispositivos cadastrados
e potência disponível, utilizando bubble sort para ordenação da lista de dispositivos

### Sprint 3

Adição do algoritmo de ordenação alternativo selection sort, com comparação com
bubble sort

Benchmark com 500 dispositivos adicionados ([s3_benchmark.py](s3_benchmark.py)):

|             | Bubble sort | Selection sort |
|-------------|-------------|----------------|
| Comparações |   241107    |     125250     |
| Trocas      |    63302    |      498       |
| Tempo (μs)  |    621.2    |     146.9      |

### Sprint 4

Consolidação do código e da documentação das sprints anteriores e formulação do
relatório em PDF

## Compilação e execução

A compilação correta do programa exige suporte a funçoes POSIX básicas, por
exemplo, utilizando o `gcc` distribuído pelo projeto MSYS2

```bash
gcc -o cadastro.exe main.c && ./cadastro.exe
```

Para executar o teste de performance:

```bash
gcc -o cadastro.exe -O3 main.c && python s3_benchmark.py
```

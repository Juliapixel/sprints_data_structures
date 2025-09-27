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

## Compilação e execução

A compilação correta do programa exige suporte a funçoes POSIX básicas, por
exemplo, utilizando o `gcc` distribuído pelo projeto MSYS2

```bash
gcc -o sprint1.exe sprint1.c && ./sprint1.exe
gcc -o sprint2.exe sprint2.c && ./sprint2.exe
gcc -o sprint3.exe sprint3.c && ./sprint3.exe
```

Para executar o teste de performance:

```bash
gcc -o sprint3.exe -O3 sprint3.c && python s3_benchmark.py
```

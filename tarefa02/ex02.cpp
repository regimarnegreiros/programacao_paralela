/* Exercício 2 — Paralelizando um for simples
a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
b) Escreva um loop sequencial que soma todos os elementos.
c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
d) Compare os resultados e explique por que a diretiva reduction é necessária. */

#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int v_tam = 100;
    int vetor[v_tam];
    int soma_sequencial = 0;
    int soma_paralela = 0;

    // Inicializa o vetor com 1 em todas as posições e executa a soma sequencial
    for (int i = 0; i < v_tam; i++) {
        vetor[i] = 1;
        soma_sequencial += vetor[i];
        // cout << i << ":" <<vetor[i] << endl;
    }
    cout << "Soma sequencial: " << soma_sequencial << endl;

    // Soma paralela usando OpenMP
    #pragma omp parallel for reduction (+:soma_paralela)
    for (int i = 0; i < v_tam; i++) {
        soma_paralela += vetor[i];
    }
    cout << "Soma paralela: " << soma_paralela << endl;

    /*
    Resultados: Ambos resultaram 100 como soma.
    Importância do reduction: O reduction tem a função de criar cópias da variável soma_paralela em cada thread, assim evitando que várias threads acessem a mesma variável ao mesmo tempo, ocasionando erros na soma.
    */
}
/* Exercício 1 — “Hello World” Paralelo
a) Crie uma região paralela com #pragma omp parallel.
b) Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num()) e o total de threads (omp_get_num_threads()).
c) Configure o programa para rodar com 4 threads. */

#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    omp_set_num_threads(4); // Criação de 4 threads

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); // Coleta do id de cada thread
        int total_threads = omp_get_num_threads(); // Total de threads

        // As 4 threads imprimem seu id em paralelo
        cout << "Thread " << thread_id << " de " << total_threads << " threads." << endl;
    }
    return 0;
}
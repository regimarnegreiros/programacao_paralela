/* Exercício 4 — Medindo tempo por thread
Adapte o código do exercício anterior para:
a) Medir e exibir o tempo total de execução.
b) Medir e exibir o tempo gasto por cada thread.
c) Mostrar quantas threads foram utilizadas no cálculo. */

#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

int main() {
    // Definição do tamanho do vetor
    const int V_TAM = 1000000;

    // Definição dos vetores
    std::vector<int> x(V_TAM), y(V_TAM), z(V_TAM), a_seq(V_TAM), a_par(V_TAM);
    
    // Preenchendo vetores com valores aleatórios
    for (int i = 0; i < V_TAM; i++) {
        x[i] = i;
        y[i] = i + 1;
        z[i] = i + 2;
    }
    
    // Inicio da contagem de tempo (sequencial)
    auto inicio = std::chrono::high_resolution_clock::now();

    // for sequencial
    for (int i = 0; i < V_TAM; i++) {
        a_seq[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }

    // Fim da contagem sequencial
    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracao = fim - inicio;
    std::cout << "Tempo total sequencial: " << duracao.count() * 1000 
              << " ms." << std::endl;
    
    
    int num_threads = 0;
    int max_threads = omp_get_max_threads();
    // Contagem de tempo por thread
    std::vector<double> tempos_inicio(max_threads, 0.0);
    std::vector<double> tempos_fim(max_threads, 0.0);
    
    // Região paralela para contar o tempo de cada thread em paralelo
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int n_threads = omp_get_num_threads();
        
        // Região single para não haver sobrescrita de outras threads
        #pragma omp single
        {
            num_threads = n_threads;

            // Inicio da contagem de tempo total (paralelo)
            inicio = std::chrono::high_resolution_clock::now();
        }

        // Marcar inicio por thread
        tempos_inicio[thread_id] = omp_get_wtime();
        
        // for paralelo com schedule(static)
        #pragma omp for schedule(static)
        for (int i = 0; i < V_TAM; i++) {
            a_par[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
        }
        
        // Marcar fim por thread
        tempos_fim[thread_id] = omp_get_wtime();

        #pragma omp single
        {
            // Fim da contagem total paralela
            fim = std::chrono::high_resolution_clock::now();
        }
    }

    duracao = fim - inicio;
    std::cout << "Tempo total paralelo: " << duracao.count() * 1000 
              << " ms." << std::endl;

    for (int i = 0; i < num_threads; i++) {
        double tempo_thread = (tempos_fim[i] - tempos_inicio[i]) * 1000;
        std::cout << "Thread " << i << ": " << tempo_thread << " ms\n";
    }

    /*
    Resultado: é possível ver uma pequena melhora de tempo, mas nem sempre a versão paralela é mais rápida nesse exemplo. Também é possível notar que o tempo de execução por thread é decrescrente de acordo com o número da thread, mas com tempos similares em alguns casos.
    */

    return 0;
}
/* Exercício 3 — Expressão Vetorial
Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
a) Faça a versão sequencial.
b) Paralelize com #pragma omp parallel for schedule(static).
c) Mostre o tempo total de execução em cada versão. */

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
    std::cout << "Tempo Sequencial: " << duracao.count() * 1000 
              << " ms." << std::endl;
    
    
    // Inicio da contagem de tempo (paralelo)
    inicio = std::chrono::high_resolution_clock::now();

    // for paralelo com schedule(static)
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < V_TAM; i++) {
        a_par[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }
    
    // Fim da contagem paralela
    fim = std::chrono::high_resolution_clock::now();
    duracao = fim - inicio;
    std::cout << "Tempo paralelo: " << duracao.count() * 1000 
              << " ms." << std::endl;


    /*
    Resultados: é possível ver uma pequena melhora de tempo, mas nem sempre a versão paralela é mais rápida nesse exemplo.
    */

    return 0;
}
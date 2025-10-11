/* Exercício 5 — Escalonamento
Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
a) Execute com schedule(static) e schedule(dynamic, 1000).
b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
c) Explique em quais situações static e dynamic são mais adequados. */

#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

// Função para calcular a[i] = x[i]^2 + y[i]^2 + z[i]^2 de forma sequencial
void calcular_sequencial(
    std::vector<int>& a,
    const std::vector<int>& x, const std::vector<int>& y, const std::vector<int>& z,  
    int V_TAM
    ) {
    for (int i = 0; i < V_TAM; i++) {
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }
}

// Função para executar o cálculo com OpenMP e medir o tempo total com schedule(static)
void calcular_paralelo_static(
    std::vector<int>& a, 
    const std::vector<int>& x, const std::vector<int>& y, const std::vector<int>& z, 
    int V_TAM, int num_threads
    ) {
    #pragma omp parallel for schedule(static) num_threads(num_threads)
    for (int i = 0; i < V_TAM; i++) {
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }
}

// Função para executar o cálculo com OpenMP e medir o tempo total com schedule(dynamic, 1000)
void calcular_paralelo_dynamic(
    std::vector<int>& a, 
    const std::vector<int>& x, const std::vector<int>& y, const std::vector<int>& z, 
    int V_TAM, int num_threads
    ) {
    #pragma omp parallel for schedule(dynamic, 1000) num_threads(num_threads)
    for (int i = 0; i < V_TAM; i++) {
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }
}

// Função para medir o tempo total de execução em milissegundos
template <typename Func, typename... Args>
double medir_tempo_total(Func&& func, Args&&... args) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    // Chamando a função
    std::forward<Func>(func)(std::forward<Args>(args)...);
    
    auto fim = std::chrono::high_resolution_clock::now();
    
    // Calculando a duração
    std::chrono::duration<double> duracao = fim - inicio;
    return duracao.count() * 1000;
}

// Função para inicializar os vetores com valores de teste
void inicializar_vetores(
    std::vector<int>& x, std::vector<int>& y, std::vector<int>& z, 
    int V_TAM) {
    for (int i = 0; i < V_TAM; i++) {
        x[i] = i;
        y[i] = i + 1;
        z[i] = i + 2;
    }
}

int main() {
    const int V_TAM = 1000000;
    std::vector<int> x(V_TAM), y(V_TAM), z(V_TAM), a_seq(V_TAM), a_par(V_TAM);
    inicializar_vetores(x, y, z, V_TAM);

    // Teste com 2, 4 e 8 threads
    for (int num_threads : {2, 4, 8}) {
        std::cout << "\nNúmero de threads: " << num_threads << std::endl;
        
        // Tempo para execução sequencial
        double tempo_seq = medir_tempo_total(
            calcular_sequencial, x, y, z, a_seq, V_TAM);
        std::cout << "Tempo sequencial: " << tempo_seq << " ms." << std::endl;

        // Tempo para execução com schedule(static)
        double tempo_static = medir_tempo_total(
            calcular_paralelo_static, a_par, x, y, z, V_TAM, num_threads);
        std::cout << "Tempo com schedule(static): " << tempo_static << " ms." << std::endl;

        // Tempo para execução com schedule(dynamic, 1000)
        double tempo_dynamic = medir_tempo_total(
            calcular_paralelo_dynamic, a_par, x, y, z, V_TAM, num_threads);
        std::cout << "Tempo com schedule(dynamic, 1000): " << tempo_dynamic << " ms." << std::endl;
    }

    /*
    Resultados: Nesse exercício foi possível notar que ao utilizar a quantidade de threads de 
    forma responsável, os resultados são mais consistentes, ao contrário dos dois exercícios 
    anteriores que o tempo de execução não era consistente e nem sempre melhor que o tempo paralelo.
    Agora comparando o tempo com schedule(static) e com schedule(dynamic, 1000), foi possível notar 
    uma ligeira melhora no tempo usando o dynamic quando a função possuí mais threads para usar, 
    enquanto o static é mais eficiente no contexto onde existe o uso de poucas threads.
    */

    return 0;
}
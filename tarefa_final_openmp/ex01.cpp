#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <omp.h>

const int N_PESSOAS = 1000;
const int INTERVALO_ALTURA = 8.0;
const int INTERVALO_PESO = 4.0;

const int ALTURA_MIN = 150;
const int ALTURA_MAX = 200;
const int PESO_MIN = 50;
const int PESO_MAX = 100;

typedef struct {
    int altura;
    int peso;
} Pessoa;

void gerar_dados(std::vector<Pessoa> &dados) {
    dados.resize(N_PESSOAS);
    srand(time(NULL));

    #pragma omp parallel for
    for (int i = 0; i < N_PESSOAS; i++) {
        dados[i].altura = ALTURA_MIN + (rand() % (ALTURA_MAX - ALTURA_MIN + 1));
        dados[i].peso = PESO_MIN + (rand() % (PESO_MAX - PESO_MIN + 1));
    }
}

void classificar(std::vector<int> &dados, double valor, double valor_min, double intervalo) {
    int inc = static_cast<int>((valor - valor_min) / intervalo);

    if (inc >= static_cast<int>(dados.size())) {
        dados.resize(inc + 1, 0);
    }

    dados[inc]++;
}

double media_ponderada(std::vector<int> qtd_por_faixa, double min, double intervalo) {
    size_t soma_frequencia = 0;
    double produtos = 0.0;

    #pragma omp parallel for reduction(+:soma_frequencia, produtos)
    for (size_t i = 0; i < qtd_por_faixa.size(); ++i) {
        int xi = (2 * min + intervalo * (2*i + 1)) / 2;
        produtos += xi * qtd_por_faixa[i];
        soma_frequencia += qtd_por_faixa[i];
    }

    return produtos / soma_frequencia;
}

double desvio_padrao_populacional(std::vector<int> qtd_por_faixa, double min, double intervalo) {
    double desvio_padrao;
    double termo_1;
    double termo_2;

    double soma_xi = 0.0;
    double soma_xi2 = 0.0;
    double soma_frequencia = 0.0;

    #pragma omp parallel for reduction(+:soma_xi, soma_xi2, soma_frequencia)
    for (size_t i = 0; i < qtd_por_faixa.size(); i++) {
        int xi = (2 * min + intervalo * (2*i + 1)) / 2;
        soma_xi += xi;
        soma_xi2 += xi * xi;
        soma_frequencia += qtd_por_faixa[i];
    }

    termo_1 = soma_xi2 / soma_frequencia;
    termo_2 = (soma_xi / soma_frequencia) * (soma_xi / soma_frequencia);
    desvio_padrao = std::sqrt(termo_1 + termo_2);

    return desvio_padrao;
}

double coeficiente_de_variacao(double media, double desvio_padrao) {
    return (desvio_padrao / media) * 100;
}

double media_ponderada_sequencial(std::vector<int> qtd_por_faixa, double min, double intervalo) {
    size_t soma_frequencia = 0;
    double produtos = 0.0;

    for (size_t i = 0; i < qtd_por_faixa.size(); ++i) {
        int xi = (2 * min + intervalo * (2*i + 1)) / 2;
        produtos += xi * qtd_por_faixa[i];
        soma_frequencia += qtd_por_faixa[i];
    }

    return produtos / soma_frequencia;
}

double desvio_padrao_populacional_sequencial(std::vector<int> qtd_por_faixa, double min, double intervalo) {
    double desvio_padrao;
    double termo_1;
    double termo_2;

    double soma_xi = 0.0;
    double soma_xi2 = 0.0;
    double soma_frequencia = 0.0;

    for (size_t i = 0; i < qtd_por_faixa.size(); i++) {
        int xi = (2 * min + intervalo * (2*i + 1)) / 2;
        soma_xi += xi;
        soma_xi2 += xi * xi;
        soma_frequencia += qtd_por_faixa[i];
    }

    termo_1 = soma_xi2 / soma_frequencia;
    termo_2 = (soma_xi / soma_frequencia) * (soma_xi / soma_frequencia);
    desvio_padrao = std::sqrt(termo_1 + termo_2);

    return desvio_padrao;
}

int main() {
    std::vector<Pessoa> pessoas;
    std::vector<int> classe_altura;
    std::vector<int> classe_peso; 
    
    gerar_dados(pessoas);
    
    for (size_t i = 0; i < N_PESSOAS; i++) {
        // std::cout << "Pessoa[" << i << "] = "
        //           << "Altura: " << pessoas[i].altura
        //           << " Peso: " << pessoas[i].peso << std::endl;
        
        classificar(classe_altura, pessoas[i].altura, ALTURA_MIN, INTERVALO_ALTURA);
        classificar(classe_peso, pessoas[i].peso, PESO_MIN, INTERVALO_PESO);
    }

    double media_ponderada_altura, media_ponderada_peso, desvio_padrao_populacional_altura, desvio_padrao_populacional_peso;
    double media_ponderada_altura_seq, media_ponderada_peso_seq, desvio_padrao_populacional_altura_seq, desvio_padrao_populacional_peso_seq;

    // Número de repetições
    const int REPETICOES = 100000;
    double inicio, fim;

    // Tempo paralelo total
    inicio = omp_get_wtime();
    for (int r = 0; r < REPETICOES; ++r) {
        media_ponderada_altura = media_ponderada(classe_altura, ALTURA_MIN, INTERVALO_ALTURA);
        media_ponderada_peso = media_ponderada(classe_peso, PESO_MIN, INTERVALO_PESO);
        desvio_padrao_populacional_altura = desvio_padrao_populacional(classe_altura, ALTURA_MIN, INTERVALO_ALTURA);
        desvio_padrao_populacional_peso = desvio_padrao_populacional(classe_peso, PESO_MIN, INTERVALO_PESO);
    }
    fim = omp_get_wtime();
    double tempo_paralelo_total = (fim - inicio) * 1000;

    // Tempo sequencial total
    inicio = omp_get_wtime();
    for (int r = 0; r < REPETICOES; ++r) {
        media_ponderada_altura_seq = media_ponderada_sequencial(classe_altura, ALTURA_MIN, INTERVALO_ALTURA);
        media_ponderada_peso_seq = media_ponderada_sequencial(classe_peso, PESO_MIN, INTERVALO_PESO);
        desvio_padrao_populacional_altura_seq = desvio_padrao_populacional_sequencial(classe_altura, ALTURA_MIN, INTERVALO_ALTURA);
        desvio_padrao_populacional_peso_seq = desvio_padrao_populacional_sequencial(classe_peso, PESO_MIN, INTERVALO_PESO);
    }
    fim = omp_get_wtime();
    double tempo_sequencial_total = (fim - inicio) * 1000;

    double tempo_paralelo_medio = (tempo_paralelo_total / REPETICOES) * 1000;
    double tempo_sequencial_medio = (tempo_sequencial_total / REPETICOES) * 1000;

    std::cout << "Tempo médio paralelo: " << tempo_paralelo_medio << " ms\n";
    std::cout << "Tempo médio sequencial: " << tempo_sequencial_medio << " ms\n";
    std::cout << "Diferença: " << tempo_sequencial_medio - tempo_paralelo_medio << " ms\n\n";


    // RESULTADOS
    std::cout << "Média ponderada da altura (paralela): " << media_ponderada_altura << " cm\n";
    std::cout << "Média ponderada do peso (paralela): " << media_ponderada_peso << " kg\n";
    std::cout << "Desvio padrão da altura (paralela): " << desvio_padrao_populacional_altura << " cm\n";
    std::cout << "Desvio padrão do peso (paralela): " << desvio_padrao_populacional_peso << " kg\n\n";

    std::cout << "Média ponderada da altura (sequencial): " << media_ponderada_altura_seq << " cm\n";
    std::cout << "Média ponderada do peso (sequencial): " << media_ponderada_peso_seq << " kg\n";
    std::cout << "Desvio padrão da altura (sequencial): " << desvio_padrao_populacional_altura_seq << " cm\n";
    std::cout << "Desvio padrão do peso (sequencial): " << desvio_padrao_populacional_peso_seq << " kg\n\n";

    return 0;
}
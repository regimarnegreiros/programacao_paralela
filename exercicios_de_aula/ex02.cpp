#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <omp.h>

/*
1. Faça um programa que encontre o desvio padrão amostral.
de um conjunto de valores de  dois milhões de salários de uma
bigtech fictícia espalhadas nas americas. Escolha o nome da sua bigtech, 
assim como, dos departamentos e cargos.
*/

// Informações sobre a empresa
std::string nome_big_tech = "BigTechTudo";
std::vector<std::string> departamentos = {"Desenvolvimento", "Vendas", "Suporte"};
std::vector<std::string> cargos = {"Analista", "Gerente", "Coordenador", "Assistente"};

// Função para gerar um valor aleatório para salário (Com duas casas decimais)
double gerar_salario(double valor_min, double valor_max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(valor_min, valor_max);
    float salario = dist(gen);
    salario = std::round(salario * 100.0f) / 100.0f; // Truncar para 2 casas decimais
    return salario;
}

double calcular_desvio_padrao(const std::vector<double>& valores, double media) {
    double soma_das_diferenças_ao_quadrado = 0.0;

    // Utiliza um for reduction para calcular o somatório em paralelo
    // Cria uma cópia da variável para cada thread
    #pragma omp parallel for reduction(+:soma_das_diferenças_ao_quadrado)
    for (size_t i = 0; i < valores.size(); ++i) {
        soma_das_diferenças_ao_quadrado += std::pow(valores[i] - media, 2);
    }

    return std::sqrt(soma_das_diferenças_ao_quadrado / (valores.size() - 1));
}

int main() {
    const int num_funcionarios = 2000000;
    const double salario_min = 2000;
    const double salario_max = 15000;

    std::vector<double> salarios(num_funcionarios);
    
    // Parallel for para acelerar a geração de valores para salário
    #pragma omp parallel for
    for (int i = 0; i < num_funcionarios; ++i) {
        salarios[i] = gerar_salario(salario_min, salario_max);
    }

    // #pragma omp for ordered
    // for (int i = 0; i < num_funcionarios; ++i) {
    //     #pragma omp ordered
    //     std::cout << "Funcionario [" << i << "]: " << salarios[i] << std::endl;
    // }

    // Calcula a soma de todos os salários usando for reduction
    // Cria uma cópia da variável para cada thread
    double soma_salarios = 0.0;
    #pragma omp parallel for reduction(+:soma_salarios)
    for (size_t i = 0; i < num_funcionarios; ++i) {
        soma_salarios += salarios[i];
    }

    // Imprime as informações sobre a empresa
    std::cout << std::endl << "BigTech: " << nome_big_tech 
              << std::endl << std::endl;

    std::cout << "Departamentos: ";
    for (const auto& dept : departamentos) {
        std::cout << dept << " ";
    }
    std::cout << std::endl;
    
    std::cout << std::endl << "Cargos: ";
    for (const auto& carg : cargos) {
        std::cout << carg << " ";
    }
    std::cout << std::endl << std::endl;

    double media_salarios = soma_salarios / num_funcionarios;
    std::cout << "Média dos salários: " << media_salarios << std::endl;
    
    double desvio_padrao = calcular_desvio_padrao(salarios, media_salarios);
    std::cout << "Desvio padrão: " << desvio_padrao << std::endl;
    
    return 0;
}
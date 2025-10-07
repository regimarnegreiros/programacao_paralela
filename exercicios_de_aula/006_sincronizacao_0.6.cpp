/*
---------------------------------
Exercícios
---------------------------------

Utilize o código base abaixo para a resolução dos exercícios.
Ao final de cada código, escreva um parágrafo com suas palavras

a) Qual é o objetivo do código em detalhes.
b) O que o seu código faz, etapa por etapa em detalhes.
c) Ao final de cada exercício, ouvirei uma explicação sua sobre o que está sendo feito.

Explicações, datas:

exercício 1 e 2 hoje: 07/10/2025.
exercício 3 e 4 14/10/2025.
exercício 5     21/10/2025.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Função para calcular as raizes de uma equação de segundo grau
// Retorna um std::pair contendo as raizes x1 e x2.
// Se não houver raizes reais, ambas serão 0.
std::pair<double, double> resolver_bhaskara(double a, double b, double c) {
    /* double delta = (b * b) - (4 * a * c);
    
    b * b - 4 * a * c;
     \ /    \   \  /   
      r1     \   r2
        \     \  /
         \     r2
          \   /
           r1
    */
    
    // Paraleliza confome o diagrama acima em duas threads (não é eficiente usar mais de duas threads por conta das dependencias)
    double bb, ac;
    #pragma omp parallel num_threads(2)
    {
        bb = b * b;
        ac = a * c;
    }

    double delta = bb - 4 * ac;

    if (delta < 0) return {0.0, 0.0};

    // Executa a multiplicação 2 * a para não ser necessário calcular duas vezes
    double a2 = 2 * a;
    double x1, x2;
    // Executa a operação das raizes em paralelo (não é eficiente usar mais de duas threads por conta das dependencias)
    #pragma omp parallel num_threads(2)
    {
        x1 = (-b + std::sqrt(delta)) / a2;
        x2 = (-b - std::sqrt(delta)) / a2;
    }

    return {x1, x2};
}

int main() {
    // Número de equações a serem resolvidas
    const int N = 1000;

    // Vetores para armazenar os coeficientes
    std::vector<double> a(N), b(N), c(N);

    // Preenche os vetores com valores de exemplo.
    // Metade terá raizes reais, a outra metade não.
    for (int i = 0; i < N; ++i) {
        a[i] = 1.0;
        if (i % 2 == 0) {
            // Equação com raizes reais: x^2 - 7x + 10 = 0 (raizes 5 e 2)
            b[i] = -7.0;
            c[i] = 10.0;
        } else {
            // Equação sem raizes reais: x^2 + 2x + 5 = 0 (delta < 0)
            b[i] = 2.0;
            c[i] = 5.0;
        }
    }

    // ===============================================================
    //               ÁREA PARA RESOLVER OS EXERCÍCIOS
    // ===============================================================

    // Adicione aqui o seu código OpenMP para cada exercício.

    // Exercício 01
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        std::pair<double, double> raizes = resolver_bhaskara(a[i], b[i], c[i]);

        #pragma omp critical
        std::cout << "Equação " << i + 1 << ": x1 = " << raizes.first << ", x2 = " << raizes.second << std::endl;
    }

    // Exercício 02
    double soma_total = 0.0;

    // Divide as operações igualmente entre as threads
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; ++i) {
        a[i] = 1.0;
        b[i] = -5.0;
        c[i] = 6.0;
    }
    
    // Cria uma cópia local de soma_total em cada thread para evitar conflitos
    #pragma omp parallel for reduction (+:soma_total)
    for (int i = 0; i < N; ++i) {
        std::pair<double, double> raizes = resolver_bhaskara(a[i], b[i], c[i]);
        double soma_local = raizes.first + raizes.second;

        soma_total += soma_local;
    }

    std::cout << "Soma total: " << soma_total << std::endl;

    // ===============================================================

    return 0;
}

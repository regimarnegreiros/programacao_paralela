#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Exercício 01
    cout << boolalpha;
    string nome_aluno = "Regimar";
    int idade_aluno = 20;
    double altura_aluno = 1.73;
    bool aprovado_aluno = true;

    cout << "Nome: " << nome_aluno << endl;
    cout << "Idade: " << idade_aluno << endl;
    cout << "Altura: " << altura_aluno << endl;
    cout << "Aprovado: " << aprovado_aluno << endl;

    const double pi = 3.1415;

    double area_cicunferencia_raio_5 = 2*pi*5*5;
    cout << "Área da circunferencia de raio 5: " << area_cicunferencia_raio_5 << endl << endl;

    return 0;
}
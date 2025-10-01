#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Exercício 02
    string nome;
    int idade;

    cout << "Digite o seu primeiro nome: ";
    cin >> nome;

    cout << "Digite a sua idade: ";
    cin >> idade;

    cout << "Olá, " << nome << "! Você tem " << idade << " anos." << endl << endl;

    return 0;
}

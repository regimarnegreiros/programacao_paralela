#include <iostream>
#include <fstream>

using namespace std;

struct Aluno {
    string nome;
    unsigned int idade;
};

class ContaBancaria {
private:
    string titular;
    double saldo{0.0};
public:
    ContaBancaria(const string &t, double s = 0.0) : titular(t), saldo(s) {}

    void depositar(double valor) {
        saldo += valor;
    }

    bool sacar(double valor) {
        if (valor <= saldo) {
            saldo -= valor;
            return true;
        }
        return false;
    }

    void imprimir() const {
        cout << "Titular: " << titular << ", Saldo: R$ " << saldo << endl;
    }
};

int main() {
    // Exercício 09
    Aluno aluno;

    cout << "Digite o nome do aluno: ";
    getline(cin, aluno.nome);
    cout << "Digite a idade do aluno: ";
    cin >> aluno.idade;

    cout << endl << "Dados do aluno:" << endl;
    cout << "Nome: " << aluno.nome << endl;
    cout << "Idade: " << aluno.idade << endl;

    
    ContaBancaria conta{"Regimar", 500};
    conta.imprimir();
    conta.depositar(100);
    conta.imprimir();
    conta.sacar(300);
    conta.imprimir();
    conta.sacar(400);
    conta.imprimir();
    conta.sacar(100);
    conta.imprimir();
    

    return 0;
}
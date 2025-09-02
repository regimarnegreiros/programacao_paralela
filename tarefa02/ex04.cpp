#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Exercício 04
    int nota;
    cout << "Digite a nota (0 a 10): ";
    cin >> nota;

    if (nota >= 6) {
        cout << "Aprovado" << endl;
    } else if (nota >= 4) {
        cout << "Prova final" << endl;
    } else {
        cout << "Reprovado" << endl;
    }

    string nome;
    vector<string> nomes;
    int opcao;

    do {
        cout << "Menu:" << endl;
        cout << "1 – Cadastrar nome" << endl;
        cout << "2 – Listar nomes" << endl;
        cout << "3 – Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;
    
        switch (opcao)
        {
        case 1:
            cout << "Digite o nome para cadastrar: ";
            cin.ignore();
            getline(cin, nome);
            nomes.push_back(nome);
            break;

        case 2:
            cout << "Lista de nomes cadastrados:" << endl;
            for(string nome : nomes) {
                cout << nome << endl;
            }
            break;

        case 3:
            break;

        default:
            cout << "Opção inválida. Tente novamente. " << endl;
            break;
        }

    } while (opcao != 3);

    return 0;
}
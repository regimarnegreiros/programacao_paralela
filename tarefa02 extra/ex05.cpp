#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Exercício 05
    cout << "Números impares: " << endl;
    for (int i = 1; i <= 20; i++) {
        if (i % 2 != 0) {
            cout << i << " - ";
        }
    }
    cout << endl;

    cout << "Contagem regressiva: " << endl;
    int i = 10;
    while (i >= 0) {
        cout << i << " - ";
        i--;
    }
    cout << endl;

    int opcao;

    do {
        cout << "Menu:" << endl;
        cout << "1 – Opção" << endl;
        cout << "2 – Opção" << endl;
        cout << "0 – Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;
    
        switch (opcao)
        {
        case 0:
            break;

        case 1:
            cout << "Opção 1 selecionada." << endl;
            break;
            
        case 2:
            cout << "Opção 2 selecionada." << endl;
            break;

        default:
            cout << "Opção inválida. Tente novamente. " << endl;
            break;
        }

    } while (opcao != 0);
    
    return 0;
}
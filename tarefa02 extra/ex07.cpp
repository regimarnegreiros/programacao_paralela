#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // Exercício 07
    int arr[5] = {0, 1, 2, 3, 4};

    int soma = 0;
    for(int i = 0; i < 5; i++) {
        soma += arr[i];
    }

    cout << "A soma dos elementos do array é: " 
    << soma << endl;
    
    vector<int> v = {5, 10, 15};

    v.push_back(5);
    v.push_back(10);
    
    int soma_vetor = 0;
    for (int e : v) {
        soma_vetor += e;
    }
    
    cout << "A soma dos elementos do vetor é: " 
    << soma_vetor << endl;

    return 0;
}
#include <iostream>
#include <fstream>

using namespace std;

int soma(int a, int b) {
    return a + b;
}

void incrementa_1(int &n) {
    n++;
}

int soma(int a, int b, int c) {
    return a + b + c;
}

int main() {
    // Exercício 06 
    int a = 2;
    int b = 5;
    int resultado = soma(a, b);
    cout << a << " + " << b
    << " = " << resultado << endl;
    
    int n = 1;
    cout << "Número Antes "<< n << endl;
    incrementa_1(n);
    cout << "Número incrementado por referência "<< n << endl;
    
    int c = 3;
    int resultado_2 = soma(a, b, c);
    cout << a << " + " << b << " + " << c
    << " = " << resultado_2 << endl;

    return 0;
}
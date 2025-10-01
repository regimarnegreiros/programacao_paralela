#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Exercício 03
    int num1, num2;
    cout << "Digite dois números inteiros: ";
    cin >> num1 >> num2;

    cout << "Soma: " << num1 + num2 << endl;
    cout << "Subtração: " << num1 - num2 << endl;
    cout << "Multiplicação: " << num1 * num2 << endl;
    cout << "Divisão inteira: " << num1 / num2 << endl;
    cout << "Divisão real: " << static_cast<double>(num1) / num2 << endl;
    cout << "O maior número é: " << (num1 > num2 ? num1 : num2) << endl;
    return 0;
}
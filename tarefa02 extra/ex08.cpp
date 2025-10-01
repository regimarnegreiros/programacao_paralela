#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Exercício 08
    int x = 10;
    
    int *ptr = &x;

    *ptr = *ptr *2;

    int &ref = x;
    ref = ref * 3;

    cout << "O valor final de x é: " << x << endl; 

    int *ptrd = new int;
    *ptrd = 7;

    cout << "O valor do ponteiro dinâmico é: " << *ptrd << endl;
    delete ptrd;

    return 0;
}
#include <iostream>
#include <omp.h>
#include <iomanip>

using namespace std;

int main() {
    int num_procs = omp_get_num_procs();
    int max_threads = omp_get_max_threads();

    cout << "Processadores lógicos disponíveis: " << num_procs << endl;
    cout << "Máximo de threads padrão: " << max_threads << endl;

    cout << endl;
    #pragma omp parallel 
    {
        int thread_id = omp_get_thread_num();
        int total = omp_get_num_threads();
        #pragma omp critical
        cout << "Hello thread: " << setw(3) << setfill(' ') << thread_id
             << " | Total: " << total << endl;
    }
    return 0;
}

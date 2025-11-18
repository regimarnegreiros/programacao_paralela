#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            std::cerr << "Erro: Este exercicio deve ser executado com exatamente 2 processos." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    const int NUM = 5; // 5 envios e 5 recebimentos
    int contador = 0;
    const int TAG = 0; 
    
    if (rank == 0) {
        for (int i = 0; i < NUM; ++i) { 
            
            MPI_Send(&contador, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD);
            MPI_Recv(&contador, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if (i < NUM - 1) {
                contador++;
                std::cout << "P0 recebeu " << contador - 1 
                          << " | enviando " << contador << "." << std::endl;
            } else {
                std::cout << "P0 recebeu " << contador 
                          << " | finalizando." << std::endl;
            }
        }
    } 
    else if (rank == 1) {
        for (int i = 0; i < NUM; ++i) {
            
            MPI_Recv(&contador, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            contador++;
            std::cout << "P1 recebeu " << contador - 1 
                      << " | enviando " << contador << "." << std::endl;

            MPI_Send(&contador, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        }
    }
    
    MPI_Finalize();
    return 0;
}
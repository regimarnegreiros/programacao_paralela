#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) std::cerr << "Erro: Requer pelo menos 2 processos." << std::endl;
        MPI_Finalize();
        return 1;
    }

    int token;
    const int TAG = 0; 
    
    int destino = (rank + 1) % size;
    int origem = (rank - 1 + size) % size;

    if (rank == 0) {
        token = 100;
        
        std::cout << "P" << rank 
                  << " inicia o anel com o token = " 
                  << token << std::endl;
        
        MPI_Send(&token, 1, MPI_INT, destino, TAG, MPI_COMM_WORLD);
        MPI_Recv(&token, 1, MPI_INT, origem, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        std::cout << "P"<< rank 
                  << " recebeu o token de volta do processo " << origem 
                  << ". Anel completo." << std::endl;
    
    } else {
        MPI_Recv(&token, 1, MPI_INT, origem, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::cout << "P" << rank << " recebeu o token = " 
                  << token << std::endl;
        
        MPI_Send(&token, 1, MPI_INT, destino, TAG, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}
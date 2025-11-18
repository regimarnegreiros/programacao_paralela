#include <iostream>
#include <vector>
#include <numeric>
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

    const int TAMANHO_TOTAL = 1200;
    const int NUM_TRABALHADORES = size - 1;
    const int TAG_DADOS = 1;
    const int TAG_RESULTADO = 2;

    if (rank == 0) {
        // Lógica do Mestre (Processo 0)
        if (TAMANHO_TOTAL % NUM_TRABALHADORES != 0) {
            std::cerr << "O tamanho do vetor não é divisível pelo número de trabalhadores." << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        std::vector<int> vetor_mestre(TAMANHO_TOTAL, 1);
        int tamanho_parte = TAMANHO_TOTAL / NUM_TRABALHADORES;
        int soma_total = 0;
        int soma_parcial_recebida;
        int indice_inicial;

        std::cout << "Mestre (P0): Dividindo o trabalho para " 
                  << NUM_TRABALHADORES << " trabalhadores." << std::endl;

        for (int i = 1; i < size; ++i) {
            indice_inicial = (i - 1) * tamanho_parte;
            MPI_Send(&vetor_mestre[indice_inicial], tamanho_parte, MPI_INT, i, TAG_DADOS, MPI_COMM_WORLD);
        }

        for (int i = 1; i < size; ++i) {
            MPI_Recv(&soma_parcial_recebida, 1, MPI_INT, i, TAG_RESULTADO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            soma_total += soma_parcial_recebida;
        }

        std::cout << "Mestre (P0): Recebido." << std::endl;
        std::cout << "Mestre (P0): A SOMA TOTAL É: " << soma_total << "." << std::endl;

    } else {
        int tamanho_parte = TAMANHO_TOTAL / NUM_TRABALHADORES;
        std::vector<int> vetor_parte(tamanho_parte);
        
        MPI_Recv(vetor_parte.data(), tamanho_parte, MPI_INT, 0, TAG_DADOS, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int soma_parcial = 0;
        for (int valor : vetor_parte) {
            soma_parcial += valor;
        }
        
        std::cout << "Trabalhador (P" << rank 
                  << "): Recebido, a soma parcial é " 
                  << soma_parcial << "." << std::endl;

        MPI_Send(&soma_parcial, 1, MPI_INT, 0, TAG_RESULTADO, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
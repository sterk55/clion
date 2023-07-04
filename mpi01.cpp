#include <iostream>
#include <mpi.h>

int sumar_Datos(int* data, int size){
    int suma = 0;
    for(int i = 0; i<size;i++){
        suma = suma + data[i];
    }
    return suma;
}

int main(int argc, char** argv){

    MPI_Init(&argc,&argv);

    int rank , nproc;


    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    if(rank==0){
        int data[100];

        std::printf("MPI group size: %d\n", nproc);
        for(int i = 0;i <100; i++){
            data[i] = i;
        }
        int bloque = 100/nproc;

        for(int nRank=1; nRank<nproc; nRank++){
            MPI_Send(&data[bloque*(nRank -1 )], bloque, MPI_INT, nRank, 0, MPI_COMM_WORLD);
        }
        int suma0 = sumar_Datos(&data[bloque*(nproc-1)], 100-(nproc-1)*bloque);
        int sumaTotal = suma0;

        for(int nRank=1; nRank<nproc; nRank++){
            int sumaTmp;
            MPI_Recv(&sumaTmp,1,MPI_INT,nRank,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::printf("[Rank-%d] - Resultado rank-%d: %d\n", rank, nRank, sumaTmp);
            sumaTotal = sumaTotal+sumaTmp;
        }
        std::printf("[Rank-%d] Suma total %d\n" ,rank, sumaTotal);

    }else{
        int bloque = 100/nproc;
        int* dataTmp = new int[bloque];
        //std::printf("rank %d recibiendo datos\n", rank);
        MPI_Recv(dataTmp,bloque,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::string str = "";
        for(int i =0;i<bloque;i++){
            str = str + std::to_string(dataTmp[i])+", ";
        }
        std::printf("[Rank-%d] %d datos recibidos: [%s]\n", rank,bloque, str.c_str());

        //sumar los datos
        int suma = sumar_Datos(dataTmp,bloque);
        MPI_Send(&suma, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }

    MPI_Finalize();



    return 0;
}

#include <iostream>
#include <mpi.h>

int main(int argc, char** argv){

    MPI_Init(&argc,&argv);

    int rank , nproc;


    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);


    if(rank == 0){
        std::printf("MPI group size: %d\n", nproc);
    }else{
        std::printf("Soy el rank %d\n", rank);

    }


    //std::printf("Rank %d of %d procs\n", rank, nproc);

    //while(1);

    MPI_Finalize();



    return 0;
}
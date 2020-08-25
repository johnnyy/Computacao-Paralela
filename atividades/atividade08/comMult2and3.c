#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv) {
    int numprocs, org_rank, new_rank[3];



    new_rank[0] =-1;
    new_rank[1] =-1;
    new_rank[2] =-1;

    MPI_Comm mult2_comm, mult3_comm, mult2_3_comm;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &org_rank);

    
    
    MPI_Comm_split(MPI_COMM_WORLD, org_rank % 2, 0, &mult2_comm);
    MPI_Comm_split(MPI_COMM_WORLD, org_rank % 3, 0, &mult3_comm);
    MPI_Comm_split(MPI_COMM_WORLD, org_rank % 3 + org_rank % 2, 0, &mult2_3_comm);


    
    if(org_rank % 2 == 0){
        MPI_Comm_rank(mult2_comm, &new_rank[0]);

    }
    
    if(org_rank %3 == 0){
        MPI_Comm_rank(mult3_comm, &new_rank[1]);

    }
    if(org_rank %3 == 0 && org_rank %2 == 0 ){
        MPI_Comm_rank(mult2_3_comm, &new_rank[2]);


    }


    if(new_rank[0] !=-1 && new_rank[1] !=-1){
        printf("processo rank %d em MPI_COMM_WORLD: rank %d em mult2_comm, rank %d em mult3_comm, rank %d em mult2_3_comm\n", org_rank, new_rank[0], new_rank[1], new_rank[2]);

    }
    else if (new_rank[0] !=-1){
        printf("processo rank %d em MPI_COMM_WORLD: rank %d em mult2_comm\n", org_rank, new_rank[0]);

    }

    else if (new_rank[1] !=-1){
        printf("processo rank %d em MPI_COMM_WORLD: rank %d em mult3_comm\n", org_rank, new_rank[1]);

    }
    else{
        printf("processo rank %d em MPI_COMM_WORLD\n", org_rank);
    }


    MPI_Finalize();
    return 0;
}
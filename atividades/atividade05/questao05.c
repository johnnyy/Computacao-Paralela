#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
    int source, destination;
    int tag = 3;
    double starttime, endtime;
    int rank, size;

    starttime = MPI_Wtime();


   

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n = atoi(argv[1]);


    destination = (rank + 1) % size;
    source = (rank + size - 1) % size;
    if(rank ==0){
        MPI_Send(&n, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
        printf("Process %d send %d\n",rank,n);

        while(1){

            MPI_Recv(&n, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
            if(n ==0){
                break;
            }
            n--;
            MPI_Send(&n, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
            printf("Process %d send %d\n",rank,n);


        }

        endtime   = MPI_Wtime();
        printf("That took %f seconds\n",endtime-starttime);
    }

    else{
        while(1){
            MPI_Recv(&n, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
            MPI_Send(&n, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
           // printf("Process %d send %d\n",rank,n);

            if(n == 0){
                break;
            }
        }
        


    }

    MPI_Finalize();

    return 0;
}
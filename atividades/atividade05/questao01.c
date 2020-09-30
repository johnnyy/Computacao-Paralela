// Nota 0,5
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
                        
#define MAX 100
                        
int main(int argc, char *argv[]) {
    int rank, numtasks,total_num;
    int destination = 0, numbers[MAX];

                        
    MPI_Status status;
                        
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
                        

    if (rank == destination) {
        int total_num_received[numtasks];
        int sources[numtasks];
        for(int i =0; i < numtasks -1; i++){
            MPI_Recv(numbers, MAX, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &total_num_received[i]);
            sources[i] = status.MPI_SOURCE;
        }

        
        for(int i=0;i<numtasks-1; i++){
            printf("Process %d received %d numbers. Source = %d\n", destination, total_num_received[i], sources[i]);
        }
    }

    else  {
        srand(time(0));
        total_num = (rand() / (float) RAND_MAX) * (MAX);
                        
        MPI_Send(numbers, total_num, MPI_INT, destination, 0, MPI_COMM_WORLD);
                        
        printf("Process %d sent %d numberts to 0\n", rank, total_num);
    } 
                        
    MPI_Finalize();
                   
    return 0;

}

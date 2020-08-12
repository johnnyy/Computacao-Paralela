#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include<malloc.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
    double parcial = 0.0, total= 0.0;
    int source, destination = 0;
    int tag = 3;
    double starttime, endtime;
    int rank, size, p, lo, hi;

    starttime = MPI_Wtime();


   

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    long int n = atoi(argv[1]);
    p = n/size;

    double * vector1 = malloc(p*sizeof(double));
    double * vector2 = malloc(p*sizeof(double));

    for(int j = 0; j < p ; j++){
        vector1[j] = 1.0;
        vector2[j] = 1.0;


    }
    for(int i = 0; i<p; i++){
        parcial += vector1[i]*vector2[i];
    }

   
    if(rank ==0){      
        total = parcial;
        for (source = 1; source < size; source++) {
            MPI_Recv(&parcial, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status);
            total += parcial;
        }
        printf("Total: %lf\n",total);
        endtime   = MPI_Wtime();
        printf("That took %f seconds\n",endtime-starttime);
    }

    else{
        
        MPI_Send(&parcial, 1, MPI_DOUBLE, destination, tag, MPI_COMM_WORLD);


    }

    MPI_Finalize();

    return 0;
}
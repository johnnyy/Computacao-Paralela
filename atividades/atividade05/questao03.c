#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include<malloc.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
    double parcial = 0.0, total= 0.0;
    int source = 0, destination = 0;
    int tag = 0;
    int rank, size, p, lo, hi;




   

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    long int n = atoi(argv[1]);
    p = n/size;

   
    if(rank ==0){
	double * vector1 = malloc(n*sizeof(double));
	double * vector2 = malloc(n*sizeof(double));

	for(int j = 0; j < n ; j++){
		vector1[j] = 1.0;
		vector2[j] = 1.0;

	}


	for (int destination = 1; destination < size; destination++) {


        	MPI_Send(vector1+destination*p, p, MPI_DOUBLE, destination, tag, MPI_COMM_WORLD);
        	MPI_Send(vector2+destination*p , p, MPI_DOUBLE, destination, tag+1, MPI_COMM_WORLD);
        }


	for(int i = 0; i<p; i++){
		parcial += vector1[i]*vector2[i];
	}


        total = parcial;

        for (source = 1; source < size; source++) {
            MPI_Recv(&parcial, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status);
            total += parcial;
        }
        printf("Total: %lf\n",total);
    }



    else{
	double * vector1 = malloc(p*sizeof(double));
	double * vector2 = malloc(p*sizeof(double));

        MPI_Recv(vector1, p, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(vector2, p, MPI_DOUBLE, 0, tag+1, MPI_COMM_WORLD, &status);

	for(int i = 0; i<p; i++){
       		parcial += vector1[i]*vector2[i];
    	}

        MPI_Send(&parcial, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD);


    }

    MPI_Finalize();

    return 0;
}

#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include<malloc.h>
#include <stdlib.h>


void mtxMul(double *c, double *a, double *b, int p, int n){
	for (int i = 0; i < p; i++){
		for (int j = 0; j < n; j++){
			c[i*n + j] = 0.0;
			for ( int k=0; k < n; k++)
				c[i*n + j] = c[i*n +j] + a[i*n + k] * b[j*n + k];

		}

	}
}



int main(int argc, char *argv[]) {


    int source = 0, destination = 0, n, elem;
    double * a, *b, *c;

    int tag = 0, root=0;
    int rank, size, p;

   

    MPI_Status status;
    double starttime, endtime;
    starttime = MPI_Wtime();

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);



   
    if(rank ==root){
        n = atoi(argv[1]);
	//Matriz a é orientada a linha e matrix b a coluna 
    	a = (double*) malloc(n*n*sizeof(double));
    	b = (double*) malloc(n*n*sizeof(double));
    	c = (double*) malloc(n*n*sizeof(double));
    	for(int j = 0; j < n*n ; j++){
    				a[j] = 1.0;
    				b[j] = 1.0;
    	}	
   }

    MPI_Bcast(&n,1, MPI_INT,root, MPI_COMM_WORLD);

    p = n/size;
    elem = p*n;
    double *a_parcial = (double*) malloc(elem*sizeof(double));
    double *c_parcial = (double*) malloc(elem*sizeof(double));
    
    if(rank != root){
            b = (double*) malloc(n*n*sizeof(double));

    }

    MPI_Scatter(a,elem,MPI_DOUBLE, a_parcial, elem, MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Bcast(b,n*n,MPI_DOUBLE, root, MPI_COMM_WORLD);

    mtxMul(c_parcial, a_parcial, b, p, n);
    
    

    MPI_Gather(c_parcial, elem, MPI_DOUBLE, c, elem, MPI_DOUBLE, root, MPI_COMM_WORLD);
    if(rank ==root){
        endtime   = MPI_Wtime();
        printf("That took %f seconds\n",endtime-starttime);
    }
    

    MPI_Finalize();

    return 0;
}

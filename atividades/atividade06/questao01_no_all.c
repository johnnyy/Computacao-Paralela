// Cálculo das Médias
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
                        
#define NELEM 1024*1024

int main(int argc, char *argv[]) {
    int i, rank, size;
    float *random_numbers;
    float avg, dif_quad_local = 0, sum_local = 0;
    float sum_global, dif_quad_global, std_dev;
    double starttime, endtime;
    starttime = MPI_Wtime();

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Cria um vetor de números aleatórios em cada processo.
    srand(MPI_Wtime() * rank);
    random_numbers = (float *) malloc(sizeof(float) * NELEM);
    for(i = 0; i < NELEM; i++)
        random_numbers[i] = (rand()/(float)RAND_MAX);

    for(i = 0; i < NELEM; i++)
        sum_local += random_numbers[i];

    printf("Process %d: local sum %f, local average %f .\n", rank, sum_local, sum_local/NELEM);

    // Média Global
    MPI_Reduce(&sum_local, &sum_global, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sum_global,1,MPI_FLOAT,0,MPI_COMM_WORLD);
    avg = sum_global / (NELEM * size);

    // Soma local do Quadrado das diferenças 
    for(i = 0; i < NELEM; i++)
        dif_quad_local += (random_numbers[i]- avg) * (random_numbers[i] - avg);

    // Soma Global do Quadrado das diferenças 
    MPI_Reduce(&dif_quad_local, &dif_quad_global, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
            
    if (rank == 0) {
        std_dev = sqrt(dif_quad_global/(NELEM * size));
        printf("Average %f, Standard Deviation %f\n", avg, std_dev);
        endtime   = MPI_Wtime();
        printf("That took %f seconds\n",endtime-starttime);
    }

    free(random_numbers);
    MPI_Finalize();
    return 0;
}
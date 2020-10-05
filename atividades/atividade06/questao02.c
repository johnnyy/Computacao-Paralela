// Nota 0,5
// Cálculo das Médias
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
                
int main(int argc, char *argv[]) {
    int i, rank, size;
    int *input_array, *output_array;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    input_array = (int *) malloc(2*size * sizeof(int));
    output_array = (int *) malloc(2*size * sizeof(int));

    for (i = 0; i < 2*size; i++)
        input_array[i] = rank * 2*size + i;

    printf("Input for process %d\n", rank);
    for (i = 0; i < 2*size; i++)
        printf("%d ", input_array[i]);
    printf("\n");

    MPI_Alltoall(input_array, 2, MPI_INT, output_array, 2, MPI_INT, MPI_COMM_WORLD);

    printf("Output for process %d\n", rank);
    for (i = 0; i < 2*size; i++)
        printf("%d ", output_array[i]);
    printf("\n");

    free(input_array);
    free(output_array);
    MPI_Finalize();
    return 0;
}

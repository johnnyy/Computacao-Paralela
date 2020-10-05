// Nota Questão 03 0,5
// Nota Questão 04 0,8 
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include<malloc.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
    float parcial = 0.0, total= 0.0;


    int source = 0, destination = 0;

    float number1,number2;
    int tag = 0, root=0;
    int rank, size, p;
    float * vector1, *retorno;
    float * vector2;
    float * vector1_c, * vector2_c;
    double starttime, endtime;
    // Depois de MPI_Init.
    starttime = MPI_Wtime();


   

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);



   
    if(rank ==0){
        long int n = atoi(argv[3]);
        p = n/size;
        number1 = atof(argv[1]);
        number2 = atof(argv[2]);
        vector1_c =(float *) malloc(n*sizeof(float));
        vector2_c = (float *) malloc(n*sizeof(float));
        retorno = (float*) malloc(size*sizeof(float));

        for(int j = 0; j < n ; j++){
          vector1_c[j] = number1;
          vector2_c[j] = number2;

        }
    }

    MPI_Bcast(&p,1, MPI_INT,root, MPI_COMM_WORLD);
    vector1 = (float*) malloc(p*sizeof(float));
    vector2 = (float*) malloc(p*sizeof(float));
    MPI_Scatter(vector1_c,p,MPI_FLOAT, vector1, p, MPI_FLOAT, root, MPI_COMM_WORLD);
    MPI_Scatter(vector2_c,p,MPI_FLOAT, vector2, p, MPI_FLOAT, root, MPI_COMM_WORLD);
    
	for(int i = 0; i<p; i++){
       		parcial += vector1[i]*vector2[i];
    }
    
    //Entendi com recepção dos resultados parciais pelo processo raiz
    //Como a recepçao das partes separadas de cada soma parcial
    // Portanto, entendi como o recebimento com Gether e e depois a contagem
    // Se não iria utilizar o REDUCE para produzir a soma final

     //MPI_Reduce(&parcial,&total,1,MPI_FLOAT,MPI_SUM,root, MPI_COMM_WORLD);
    
    //Com esse código o for dentro do if(rank==root) abaixo seria eliminado
    //Como também a função MPI_Gather

    MPI_Gather(&parcial,1,MPI_FLOAT,retorno,1,MPI_FLOAT, root, MPI_COMM_WORLD);

    if(rank ==root){
        for(int i =0; i<size;i++){
            total +=retorno[i];
        }
        endtime   = MPI_Wtime();
        printf(" %f seconds\n",endtime-starttime);
        printf("Produto Escalar: %lf\n",total );
    }
    

    MPI_Finalize();

    return 0;
}

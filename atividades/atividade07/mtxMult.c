#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <time.h>
void mtxMul(double **c, double **a, double **b, int n){
	for (int i = 0; i < n; i++){
		for (int j =0; j < n; j++){

			for ( int k=0; k < n; k++)
				c[i][j] = c[i][j] + a[i][k]* b[k][j];
		}
	}
}


int main(int argc,char * argv[]){

	int n = atoi(argv[1]);
	clock_t Ticks[2];

	double **a = malloc(n*sizeof(double*));
	double **b = malloc(n*sizeof(double*));
	double **c = malloc(n*sizeof(double*));

	for (int i =0; i <n; i++){
		a[i] = malloc(n*sizeof(double));
		b[i] = malloc(n*sizeof(double));
		c[i] = malloc(n*sizeof(double));
		
		for(int j = 0; j < n ; j++){
			a[i][j] = 1.0;
			b[i][j] = 1.0;
			c[i][j] = 0.0;
		}
	}
  	Ticks[0] = clock();


	mtxMul(c, a , b , n);
  	Ticks[1] = clock();

	 double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  	 printf("Tempo gasto: %g ms.", Tempo);
}

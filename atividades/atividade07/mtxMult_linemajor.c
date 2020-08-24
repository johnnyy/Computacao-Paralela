#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <time.h>
void mtxMul(double *c, double *a, double *b, int n){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){

			for ( int k=0; k < n; k++)
				c[i*n + j] = c[i*n +j] + a[i*n + k] * b[k*n + j];
		}
	}
}


int main(int argc,char * argv[]){

	int n = atoi(argv[1]);
	clock_t Ticks[2];

	double *a = malloc(n*n*sizeof(double));
	double *b = malloc(n*n*sizeof(double));
	double *c = malloc(n*n*sizeof(double));
		
	for(int j = 0; j < n*n ; j++){
		a[j] = 1.0;
		b[j] = 1.0;
		c[j] = 0.0;
	}
	
  	Ticks[0] = clock();


	mtxMul(c, a , b , n);
  	Ticks[1] = clock();
	
	 double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  	 printf("Tempo gasto: %g ms.", Tempo);
}

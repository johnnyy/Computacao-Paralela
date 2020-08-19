// Correção: OK. 2,5 pontos.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "jacobi.h"
#include <omp.h>

#define ECHO 0

int main(int argc, char *argv[]){
    int n;
    int iters = 0;
    double epsilon = 0.0;

    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &iters);
    
    double **grid = allocate2dMatrix(n+2,n+2);
    double **new = allocate2dMatrix(n+2,n+2);
    stableValues2dMatrix(grid, n+2, n+2);


    for (int k = 0; k < iters; k = k + 2) {
        #pragma omp parallel for collapse(2)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) 
                new[i][j] = (grid[i-1][j] + grid[i+1][j] + grid[i][j-1] + grid[i][j+1]) * 0.25;
        #pragma omp parallel for collapse(2)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) 
                grid[i][j] = (new[i-1][j] + new[i+1][j] + new[i][j-1] + new[i][j+1]) * 0.25;
    }

    double maxdiff = 0.0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            maxdiff = fmax(maxdiff, fabs(new[i][j]-grid[i][j]));
        }
        
    printf("Diferença: %.5f\n", maxdiff);

    free2dMatrix(grid, n+1);
    free2dMatrix(new, n+1);
    return 0;
}

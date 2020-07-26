#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

double **allocate2dMatrix(int l, int c) {
    double **a = malloc(l * sizeof(double *));
    for (int i = 0; i < c; i++)
	    a[i] = malloc(c * sizeof(double));

    return a;
}

void free2dMatrix(double **m, int l) {
    for (int i = 0; i < l; i++)
        free(m[i]);
    free(m);
}

void randomValues2dMatrix(double **m, int l, int c, double max) {
    srand((unsigned) time(0));
    for(int i = 0; i < l; i++)
        for(int j = 0; j < c; j++)
            m[i][j] = (max / RAND_MAX) * rand();
    return;
}

void stableValues2dMatrix(double **m, int l, int c) {
    for(int i = 0; i < l; i++)
        for(int j = 0; j < c; j++) {
            if (i == 0 || j == 0)
                m[i][j] = 0;
            else if (i == l - 1 || j == c - 1)
                m[i][j] = 0;
            else
                m[i][j] = i * j;
        }
    return;
}

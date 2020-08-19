// Correção: OK. Ficou diferente do que acho que o OpenMP do GCC faz, entretanto é uma opção de implementação. 1,5 Pontos.
#include <stdio.h>
#include <omp.h>

#define chunk 3

int main (int argc , char *argv[]) {
    int max; 
    sscanf (argv[1], "%d", &max);
    int ts = omp_get_max_threads ();
    int sums[ts];
    #pragma omp parallel
    {
        int passo = chunk-1;
        //Pega os elementos de forma alternada nas threads, semelhante ao static
        int t = omp_get_thread_num ();
        sums[t] = 0;
        int position = 0;
        for(int i = 0; i*ts*chunk + t + 1 + t*passo <= max; i++){

            position = i*ts*chunk+ t + 1 + t*passo;
            printf("%d, %d\n",t,position);

            for(int j = position; j <= position + passo && j <= max ; j++)
                sums[t] += j;   
        }
    }
int sum = 0;
for (int t = 0; t < ts; t++) sum = sum + sums[t];
printf ("%d\n", sum);
return 0;
}

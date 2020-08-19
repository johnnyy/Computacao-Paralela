// Correção: OK. 1,0 Ponto.
#include <stdio.h>
#include <omp.h>


int main (int argc , char *argv[]) {
    int max; 
    sscanf (argv[1], "%d", &max);
    int ts = omp_get_max_threads ();

    int resto = max % ts;

        int sums[ts];
        #pragma omp parallel
        {
            int t = omp_get_thread_num ();
            int lo = 0;
            int hi = 0;
            if(resto > 0){
                if(t <= resto -1){
                    lo = (max / ts) * (t + 0) + 1 + t;
                    hi = (max / ts) * (t + 1) + t +1;

                }
                else if(t ==resto){
                    lo = (max / ts) * (t + 0) + 1 + t;
                    hi = (max / ts) * (t + 1) + t;
                }

                else {
                    lo = (max / ts) * (t + 0) + resto+1;
                    hi = (max / ts) * (t + 1) + resto;
                }
            }
            else{
                lo = (max / ts) * (t + 0) + 1;
                hi = (max / ts) * (t + 1) + 0;
            }
            
	        sums[t] = 0;

            
            for (int i = lo; i <= hi; i++){
                sums[t] = sums[t] + i;
                printf("id: %d, %d\n",t, i );
            }
        }

    int sum = 0;
    for (int t = 0; t < ts; t++) sum = sum + sums[t];
    printf ("%d\n", sum);
    return 0;
}

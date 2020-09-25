
__kernel void Transpose(__global float* a, __global float* b, int N) {
	
	// Achar o índice global
	int global_size = get_global_size(0);
	int iGID = get_global_id(0);
	int i = 0;
	
	while (i < N) {
	
		b[N * i + iGID] = a[N * iGID + i];
		i++;
	}
	
	


}

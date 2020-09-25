
__kernel void pi_integral(__global float* c, int intervals_number) {
	
	// Achar o índice global
	int ID = get_global_id(0);
	int global_size = get_global_size(0);
	int iGID = ID;
	float integral = 0.0;
	float dx = 1.0/intervals_number;
	float x = 0.0;
	float fx = 0.0;
	float n_1 = 1.0;
	
	
	while (iGID <= intervals_number) {
	
		x = iGID * dx;
		fx = sqrt(n_1 - x * x );

		integral = integral + fx * dx;
		

		iGID += global_size;
		c[ID] = integral;

	}
	



}

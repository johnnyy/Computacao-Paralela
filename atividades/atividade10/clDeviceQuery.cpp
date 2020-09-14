#include <stdio.h>

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define CL_TARGET_OPENCL_VERSION 200
#include <CL/cl.h>
#include <stdlib.h>
#include <string.h>

void error(cl_int status, const char *s){
    if (status) {
        printf("%s\n", s);
        exit(1);
    }
}

cl_int status;
cl_platform_id intel_platform_id;

int main(int argc, char *argv[]) {
    cl_uint quantidade_de_plataformas;

    // Recupera a quantidade de plataformas.
    status = clGetPlatformIDs(0, 
                              0, 
                              &quantidade_de_plataformas);
    error(status, "Erro ao recuperar o número de plataformas.");
    printf("Quantidade de Plataformas: %d\n\n", quantidade_de_plataformas);

    // Recupera os identificadores de plataformas.
    cl_platform_id *plataformas = (cl_platform_id *) malloc(quantidade_de_plataformas * sizeof(cl_platform_id));
    status = clGetPlatformIDs(quantidade_de_plataformas, 
                              plataformas, 
                              0);
    error(status, "Erro ao recuperar as plataformas.");
    
    // Imprime o nome das plataformas e os respectivos dispositivos
    for (cl_uint i = 0; i < quantidade_de_plataformas; i++) {
        size_t tamanho_nome_plataforma; 

        // Recupera o tamanho do nome e aloca a cadeia de caracteres.
        status = clGetPlatformInfo(plataformas[i], 
                                   CL_PLATFORM_NAME, 
                                   0, 
                                   0, 
                                   &tamanho_nome_plataforma);
        error(status, "Erro ao recuperar o tamanho do nome da plataforma.");
        char *nome_plataforma = (char *) malloc(tamanho_nome_plataforma * sizeof(char));

        // Recupera o nome
        status = clGetPlatformInfo(plataformas[i], 
                                   CL_PLATFORM_NAME, 
                                   tamanho_nome_plataforma, 
                                   nome_plataforma, 
                                   0);
        error(status, "Erro ao recuperar o nome da plataforma.");

        // Imprime o resultado.
        printf("Plataforma[%d]: %s\n", i, nome_plataforma);

        cl_uint quantidade_de_dispositivos;
        status = clGetDeviceIDs(plataformas[i], 
                                CL_DEVICE_TYPE_ALL, 
                                0, 
                                NULL, 
                                &quantidade_de_dispositivos);
        error(status, "Erro ao recuperar quantidade de dispositivos da plataforma.");
        printf("Quantidade de dispositivos %s: %d\n", nome_plataforma, quantidade_de_dispositivos);

        cl_device_id *dispositivos = (cl_device_id *) malloc(quantidade_de_dispositivos * sizeof(cl_device_id));
        status = clGetDeviceIDs(plataformas[i], 
                                CL_DEVICE_TYPE_ALL, 
                                quantidade_de_dispositivos, 
                                dispositivos, 
                                NULL);
        error(status, "Erro ao recuperar os IDs dos dispositivos da plataforma.");

        char buffer[1000];
        size_t buf_sizet = 1000;
        cl_uint buf_uint;
        printf("=== Dispositivos da Plataforma %s: ===\n", nome_plataforma);
        for (int i = 0; i < quantidade_de_dispositivos; i++)  {
            printf(" -- Dispositivo com id %d --\n", i);

            clGetDeviceInfo(dispositivos[i],
                            CL_DEVICE_NAME,
                            sizeof(buffer),
                            buffer,
                            NULL);
            printf(" DEVICE_NAME = %s\n", buffer);
            
            clGetDeviceInfo(dispositivos[i],
                            CL_DEVICE_VENDOR,
                            sizeof(buffer),
                            buffer,
                            NULL);
            printf(" DEVICE_VENDOR = %s\n", buffer);
            
            clGetDeviceInfo(dispositivos[i],
                            CL_DEVICE_MAX_COMPUTE_UNITS,
                            sizeof(buf_uint),
                            &buf_uint,
                            NULL);
            printf(" DEVICE_MAX_COMPUTE_UNITS = %u\n", 
                   (unsigned int)buf_uint);
            
            clGetDeviceInfo(dispositivos[i],
                            CL_DEVICE_MAX_WORK_GROUP_SIZE,
                            sizeof(buf_sizet),
                            &buf_sizet,
                            NULL);
            printf(" CL_DEVICE_MAX_WORK_GROUP_SIZE = %u\n",
                   (unsigned int)buf_sizet);

            clGetDeviceInfo(dispositivos[i],
                            CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
                            sizeof(buf_uint),
                            &buf_uint,
                            NULL);
            printf(" CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS = %u\n",
                   (unsigned int)buf_uint);

            size_t workitem_size[3];
            clGetDeviceInfo(dispositivos[i],
                            CL_DEVICE_MAX_WORK_ITEM_SIZES,
                            sizeof(workitem_size),
                            &workitem_size,
                            NULL);
            printf(" CL_DEVICE_MAX_WORK_ITEM_SIZES = %u, %u, %u \n",
                   (unsigned int)workitem_size[0],
                   (unsigned int)workitem_size[1],
                   (unsigned int)workitem_size[2]);

            printf("\n");
        }

        free(dispositivos);
        free(nome_plataforma);
        printf("\n");
    }

    free(plataformas);   
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int func(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return func(m - 1, 1);
    } else {
        return func(m - 1, func(m, n - 1));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <tipo_scheduling (1: estático, 2: dinámico)> <numero_hilos>\n", argv[0]);
        return -1;
    }

    int tipo_scheduling = atoi(argv[1]);
    int num_hilos = atoi(argv[2]);

    // Creamos el vector V, así como el vector resultante, VR
    int V[] = {10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
    int len = sizeof(V) / sizeof(V[0]);
    int *VR = (int *)malloc(len * sizeof(int));

    // Verificamos que la asignación de memoria haya salido bien
    if (VR == NULL) {
        printf("Error de asignación de memoria.\n");
        return -1;
    }

    clock_t inicio, fin;
    double tiempo_ejecucion;

    // Comenzamos a contar el tiempo
    inicio = clock();

    // Paralelización del bucle for utilizando OpenMP
    if(tipo_scheduling == 1){
        #pragma omp parallel for num_threads(num_hilos) schedule(static)
        for (int i = 0; i < len; i++) {
            VR[i] = func(3, V[i]);
        }
    } else {
        #pragma omp parallel for num_threads(num_hilos) schedule(dynamic)
        for (int i = 0; i < len; i++) {
            VR[i] = func(3, V[i]);
        }
    }

    // Terminamos de contar el tiempo
    fin = clock();
    tiempo_ejecucion = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("El tiempo de ejecución fue: %f segundos.\n", tiempo_ejecucion);

    // Imprimimos el vector en una forma 'legible'
    printf("VR: [ ");
    for (int i = 0; i < len; i++) {
        printf("%d", VR[i]);
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");

    // Liberamos la memoria utilizada por VR
    free(VR);

    return 0;
}
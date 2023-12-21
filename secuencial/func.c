#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int func(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return func(m - 1, 1);
    } else {
        return func(m - 1, func(m, n - 1));
    }
}

int main() {
    clock_t inicio, fin;
    double tiempo_ejecucion;

    // Creamos el vector V, así como el vector resultante, VR
    int V[] = {10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
    int len = sizeof(V) / sizeof(V[0]);
    int *VR = (int *)malloc(len * sizeof(int));

    // Verificamos que la asignación de memoria haya salido bien
    assert(VR != NULL && "Error de asignación de memoria.");

    // Comenzamos a contar el tiempo
    inicio = clock();

    // Iteramos sobre el vector
    for (int i = 0; i < len; i++) {
        VR[i] = func(3, V[i]);
    }

    // Termina de contar el tiempo
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

    // Liberamos la memoria que usó VR
    free(VR);

    return 0;
}
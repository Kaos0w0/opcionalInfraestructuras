#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
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

// Permitimos que el hilo tenga informacion especifica por medio de un struct
typedef struct {
    int num_hilos;
    int hilo_actual;
} ThreadInfo;

// Creamos el vector V, así como el vector resultante, VR
int V[] = {10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
int V_len = sizeof(V) / sizeof(V[0]);
int Vr[16];

// Generamos la función que ejecutará cada hilo
void* thread_func(void* arg) {
    // Definimos el tamaño de segmento sobre el cual un hilo trabajara
    ThreadInfo* info = (ThreadInfo*)arg;
    int num_hilos = info->num_hilos;
    int hilo_actual = info->hilo_actual;
    int tam_segmento = V_len / num_hilos;

    // Calculamos el inicio y el final del segmento del vector para cada hilo
    int inicio = hilo_actual * tam_segmento;
    int fin = (hilo_actual == num_hilos - 1) ? V_len : (hilo_actual + 1) * tam_segmento;

    for (int i = inicio; i < fin; i++) {
        Vr[i] = func(3, V[i]);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    // Nos aseguramos que se haya recibido un numero de hilos como parametro
    if (argc != 2) {
        printf("Uso: %s <numero_hilos>\n", argv[0]);
        return -1;
    }

    clock_t inicio, fin;
    double tiempo_ejecucion;

    // Se convierte a entero el parámetro y se crean dicho número de hilos
    int num_hilos = atoi(argv[1]);
    pthread_t threads[num_hilos];
    ThreadInfo thread_info[num_hilos];


    // Comenzamos a contar el tiempo
    inicio = clock();

    // Ejecutamos la función thread_func en dicho numero de hilos
    for (int i = 0; i < num_hilos; i++) {
        thread_info[i].num_hilos = num_hilos;
        thread_info[i].hilo_actual = i;
        pthread_create(&threads[i], NULL, thread_func, (void*)&thread_info[i]);
    }

    // Esperamos a que los hilos terminen su trabajo
    for (int i = 0; i < num_hilos; i++) {
        pthread_join(threads[i], NULL);
    }

    // Termina de contar el tiempo
    fin = clock();
    tiempo_ejecucion = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("El tiempo de ejecución fue: %f segundos.\n", tiempo_ejecucion);

    // Imprimimos el vector en una forma 'legible'
    printf("Vr: [ ");
    for (int i = 0; i < V_len; i++) {
        printf("%d ", Vr[i]);
    }
    printf("]\n");

    return 0;
}

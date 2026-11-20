
/*4. Escribir un programa que solicite al usuario una cantidad N de números enteros
y reserve dinámicamente la memoria necesaria para almacenarlos.
Una vez cargados, calcular e imprimir la suma y el promedio de los números pares.
 Finalmente, liberar correctamente toda la memoria utilizada. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    printf("Ingrese la cantidad de numeros N: ");
    scanf("%d", &N);

    int *vec = malloc(N * sizeof(int));

    if (vec == NULL) {
        printf("Error al asignar memoria.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < N; i++) {
        printf("Ingrese el numero #%d: ", i + 1);
        scanf("%d", &vec[i]);
    }

    int sumaTotal = 0;
    int sumaPares = 0;
    int cantPares = 0;

    for(int j = 0; j < N; j++) {
        sumaTotal = sumaTotal + vec[j];

        if(vec[j] % 2 == 0) {
            sumaPares = sumaPares + vec[j];
            cantPares++;
        }
    }

    float promedioPares = 0.0;
    if (cantPares > 0) {
        promedioPares = (float)sumaPares / cantPares;
    }

    printf("Suma total: %d \nPromedio de pares: %.2f\n", sumaTotal, promedioPares);

    free(vec);
    vec = NULL;
}

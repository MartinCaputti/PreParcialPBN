/*5. Implementar un programa que permita ingresar n�meros enteros hasta que el usuario
introduzca el valor -1. El programa debe almacenar los n�meros en un array din�mico. Al
finalizar, mostrar todos los n�meros ingresados en orden inverso y liberar la memoria
reservada. No almacenar el -1.*/


#include <stdio.h>
#include <stdlib.h>

int main(void){

    int valor = 0;
    int *arrayDin;
    int contador = 0;
    int *tmp ;
    arrayDin = malloc(1 * sizeof (int));

    if(arrayDin == NULL ){
        printf("error al reservar memoria inicial");
        return EXIT_FAILURE;
    }

    printf("Ingrese un numero entero (-1 para terminar): ");
    scanf("%d", &valor);

    while (valor != -1) {
        tmp = realloc(arrayDin, (contador + 1) * sizeof(int));
        if (tmp == NULL) {
            printf("Error al reservar memoria dinamica\n");
            free(arrayDin);
            return EXIT_FAILURE;
        }
        arrayDin = tmp;

        arrayDin[contador] = valor;
        contador++;

        printf("Ingrese otro numero (-1 para terminar): ");
        scanf("%d", &valor);
    }

    for (int i = contador - 1; i >= 0; i--) {
        printf("%d ", arrayDin[i]);
    }

    free(arrayDin);
    return EXIT_SUCCESS;


}

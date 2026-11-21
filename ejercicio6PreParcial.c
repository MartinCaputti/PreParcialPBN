/*6. Implementar una pila dinámica de números enteros.
 Luego debe apilar 5 números ingresados por el usuario y luego desapilarlos uno por uno*/

#include <stdio.h>
#include <stdlib.h>

// 1. Estructura del Nodo individual
typedef struct Nodo {
    int dato;
    struct Nodo *siguiente;
} Nodo;

// 2. Estructura de la Pila (mantiene la referencia al tope)
typedef struct {
    Nodo *tope;
} Pila;

// Prototipos de funciones
void inicializarPila(Pila *p);
int pilaVacia(const Pila *p);
int push(Pila *p, int valor);
int pop(Pila *p, int *valor);

int main(void) {
    Pila miPila;
    inicializarPila(&miPila); // El tope arranca en NULL

    int x;

    // A. Apilar 5 números ingresados por el usuario
    printf("--- APILANDO ELEMENTOS ---\n");
    for (int i = 1; i <= 5; i++) {
        printf("Ingrese el numero #%d a apilar: ", i);
        scanf("%d", &x);
        push(&miPila, x);
    }

    // B. Desapilar uno por uno y mostrarlos
    printf("\n--- DESAPILANDO ELEMENTOS (LIFO) ---\n");
    while (pop(&miPila, &x)) {
        printf("Elemento desapilado: %d\n", x);
    }

    return EXIT_SUCCESS;
}

// Inicializa la pila poniendo el tope en NULL
void inicializarPila(Pila *p) {
    p->tope = NULL;
}

// Retorna 1 si está vacía, 0 si tiene elementos
int pilaVacia(const Pila *p) {
    return (p->tope == NULL);
}

// Agrega un elemento al tope de la pila
int push(Pila *p, int valor) {
    Nodo *nuevo = malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        return 0; // Error de memoria
    }
    nuevo->dato = valor;
    nuevo->siguiente = p->tope; // El nuevo nodo apunta al viejo tope
    p->tope = nuevo;             // El tope de la pila pasa a ser el nuevo nodo
    return 1;
}

// Saca el elemento del tope y guarda su valor en el parámetro por referencia '*valor'
int pop(Pila *p, int *valor) {
    if (pilaVacia(p)) {
        return 0; // Pila vacía, no se puede desapilar
    }
    Nodo *aux = p->tope;          // 1. Guardamos temporalmente el nodo actual
    *valor = aux->dato;            // 2. Rescatamos el dato antes de borrar el nodo
    p->tope = aux->siguiente;     // 3. El tope pasa a ser el siguiente nodo
    free(aux);                    // 4. Liberamos la memoria del nodo desapilado
    return 1;                     // Éxito
}

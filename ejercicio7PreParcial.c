/*7. Implementar una cola dinámica que simule la atención de clientes en un comercio. El
programa debe solicitar 5 números de turno, almacenarlos en la cola y atender (desencolar)
los primeros 2. Finalmente, mostrar los turnos que todavía se encuentran esperando,
respetando el orden de llegada.
*/
#include <stdio.h>
#include <stdlib.h>

// 1. Estructura del Nodo
typedef struct Nodo {
    int dato;
    struct Nodo *siguiente;
} Nodo;

// 2. Estructura de la Cola (con frente y final)
typedef struct {
    Nodo *frente;
    Nodo *final;
} Cola;

// Prototipos
void inicializarCola(Cola *c);
int colaVacia(const Cola *c);
int enqueue(Cola *c, int valor);
int dequeue(Cola *c, int *valor);

int main(void) {
    Cola miCola;
    inicializarCola(&miCola);

    int turno;

    // A. Solicitar 5 números de turno y almacenarlos en la cola (Enqueue)
    printf("--- CARGA DE TURNOS ---\n");
    for (int i = 1; i <= 5; i++) {
        printf("Ingrese el numero de turno #%d: ", i);
        scanf("%d", &turno);
        enqueue(&miCola, turno);
    }

    // B. Atender (desencolar) los primeros 2 clientes
    printf("\n--- ATENDIENDO A LOS PRIMEROS 2 CLIENTES ---\n");
    for (int i = 1; i <= 2; i++) {
        if (dequeue(&miCola, &turno)) {
            printf("Atendiendo al turno: %d\n", turno);
        }
    }

    // C. Mostrar los turnos que todavía se encuentran esperando (respetando orden de llegada)
    printf("\n--- TURNOS QUE CONTINUAN ESPERANDO ---\n");
    // Recorremos la cola sin perder el frente original mediante un puntero auxiliar temporal
    Nodo *actual = miCola.frente;
    if (actual == NULL) {
        printf("No quedan turnos esperando.\n");
    } else {
        while (actual != NULL) {
            printf("Turno en espera: %d\n", actual->dato);
            actual = actual->siguiente;
        }
    }

    // D. Liberar los nodos restantes de la memoria dinámica al finalizar
    while (dequeue(&miCola, &turno)); // Vaciamos y liberamos todo lo que quedaba

    return EXIT_SUCCESS;
}

// Inicializa la cola poniendo frente y final en NULL
void inicializarCola(Cola *c) {
    c->frente = NULL;
    c->final = NULL;
}

// Retorna 1 si está vacía, 0 si tiene elementos
int colaVacia(const Cola *c) {
    return (c->frente == NULL);
}

// Encolar: Agrega un elemento al FINAL de la cola
int enqueue(Cola *c, int valor) {
    Nodo *nuevo = malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        return 0; // Error de memoria
    }
    nuevo->dato = valor;
    nuevo->siguiente = NULL; // Como es el último, su siguiente apunta a NULL

    if (colaVacia(c)) {
        // Si la cola estaba vacía, el nuevo es tanto el frente como el final
        c->frente = nuevo;
        c->final = nuevo;
    } else {
        // Si ya tenía elementos, lo enganchamos al final y movemos el puntero 'final'
        c->final->siguiente = nuevo;
        c->final = nuevo;
    }
    return 1;
}

// Desencolar: Saca el elemento del FRENTE de la cola
int dequeue(Cola *c, int *valor) {
    if (colaVacia(c)) {
        return 0; // Cola vacía
    }
    Nodo *aux = c->frente;         // 1. Guardamos el frente actual
    *valor = aux->dato;           // 2. Rescatamos el dato
    c->frente = aux->siguiente;   // 3. El frente avanza al siguiente nodo

    // Si al avanzar el frente queda en NULL, significa que la cola se vació por completo
    if (c->frente == NULL) {
        c->final = NULL;
    }

    free(aux);                    // 4. Liberamos la memoria del nodo atendido
    return 1;
}

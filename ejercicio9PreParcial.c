
#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura solicitada
typedef struct {
    int legajo;
    float nota;
} Alumno;

int main(void) {
    // Declaración e inicialización de 4 alumnos en un array estático
    Alumno alumnos[4] = {
        {101, 8.0f},
        {102, 6.5f},
        {103, 9.0f},
        {104, 7.5f}
    };

    // ==========================================
    // PASO 1: Almacenar 4 alumnos usando fwrite()
    // ==========================================
    FILE *f = fopen("alumnos.dat", "wb");
    if (f == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return EXIT_FAILURE;
    }

    // Escribimos el array completo de 4 elementos de una sola vez
    if (fwrite(alumnos, sizeof(Alumno), 4, f) != 4) {
        printf("Error al escribir los registros en el archivo.\n");
    }

    fclose(f); // Cerramos el archivo de escritura

    // ==========================================
    // PASO 2: Abrir en lectura y mostrar todos con fread()
    // ==========================================
    f = fopen("alumnos.dat", "rb");
    if (f == NULL) {
        printf("Error al abrir el archivo para lectura.\n");
        return EXIT_FAILURE;
    }

    printf("--- TODOS LOS ALUMNOS REGISTRADOS ---\n");
    Alumno a;
    // Leemos de a 1 registro hasta que fread devuelva 0 (fin de archivo)
    while (fread(&a, sizeof(Alumno), 1, f) == 1) {
        printf("Legajo: %d | Nota: %.1f\n", a.legajo, a.nota);
    }

    // ==========================================
    // PASO 3: Usar fseek() para acceder al tercer alumno (índice 2)
    // ==========================================
    // Movemos el cursor 2 posiciones hacia adelante desde el inicio (SEEK_SET)
    // 2 * sizeof(Alumno) nos posiciona exactamente en el tercer registro
    if (fseek(f, 2L * sizeof(Alumno), SEEK_SET) == 0) {
        // Leemos ese único registro directo
        if (fread(&a, sizeof(Alumno), 1, f) == 1) {
            printf("\n--- ACCESO DIRECTO (Tercer Alumno) ---\n");
            printf("Legajo: %d | Nota: %.1f\n", a.legajo, a.nota);
        }
    } else {
        printf("Error al posicionarse con fseek.\n");
    }

    // Cerramos el archivo definitivamente
    fclose(f);

    return EXIT_SUCCESS;
}

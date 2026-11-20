
# Preguntas teóricas – Lenguaje C

## 1. Gestión dinámica de memoria

### Pregunta

Explique para qué se utilizan las funciones `malloc()`, `calloc()`, `realloc()` y `free()`, indicando las diferencias entre ellas.

¿Qué sucede cuando `realloc()` no puede reservar la memoria solicitada? Explique cómo debería manejarse esta situación para evitar perder la memoria reservada anteriormente.

### Respuesta

Las funciones de gestión dinámica de memoria permiten reservar, modificar y liberar memoria durante la ejecución del programa.

- **malloc():** Reserva una cantidad determinada de bytes en memoria, sin inicializar su contenido. Devuelve un puntero al espacio reservado o `NULL` si falla.

- **calloc():** Reserva memoria para una cantidad determinada de elementos e inicializa todos sus bytes en cero. Devuelve un puntero o `NULL` si falla.

- **realloc():** Permite modificar el tamaño de un bloque de memoria previamente reservado. Puede ampliar o reducir el espacio disponible y, si es necesario, mover los datos a otra dirección de memoria.

- **free():** Libera la memoria dinámica previamente reservada, permitiendo que vuelva a estar disponible.

### ¿Qué sucede si realloc() falla?

Cuando `realloc()` no puede reservar la memoria solicitada, devuelve `NULL`.

**Importante:** La memoria original no se pierde ni se libera automáticamente. El problema aparece si asignamos directamente el resultado al puntero original.

Ejemplo incorrecto:

```c
datos = realloc(datos, 10000 * sizeof(int));
```

Si `realloc()` falla, `datos` pasa a valer `NULL` y perdemos la referencia al bloque original, provocando una fuga de memoria (*memory leak*).

**Solución:** Utilizar un puntero auxiliar y verificar el resultado antes de actualizar el puntero original.

### Ejemplo correcto

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Reserva inicial de memoria para 5 enteros
    int *datos = malloc(5 * sizeof(int));

    if (datos == NULL) {
        printf("Error al reservar memoria\n");
        return -1;
    }

    // Intentamos ampliar la memoria
    int *temp = realloc(datos, 10000 * sizeof(int));

    if (temp == NULL) {
        printf("No se pudo ampliar la memoria\n");

        // La memoria original sigue reservada
        free(datos);
        return -1;
    }

    // Actualizamos el puntero solo si realloc tuvo éxito
    datos = temp;

    // Utilizamos la memoria reservada...

    // Liberamos la memoria antes de finalizar
    free(datos);

    // Buena práctica para evitar un puntero colgante
    datos = NULL;

    return 0;
}
```

### Conceptos importantes

- **Memory leak:** Ocurre cuando se pierde la referencia a memoria reservada dinámicamente sin haberla liberado.
- **Dangling pointer:** Es un puntero que sigue apuntando a una dirección de memoria que ya fue liberada.
- **NULL:** Representa un puntero que no apunta a ningún objeto válido.
- **Puntero auxiliar:** Permite verificar el resultado de `realloc()` sin perder la referencia original.

---

## 2. Archivos de texto y archivos binarios en C

### Pregunta

Explique las diferencias entre los archivos de texto y los archivos binarios en C, indicando al menos una ventaja de cada uno.

Explique qué sucede al abrir un archivo existente utilizando los modos `"r"`, `"w"` y `"a"`, y para qué se utilizan las funciones `fread()` y `fwrite()`.

### Respuesta

### Archivos de texto

Los archivos de texto almacenan información codificada como caracteres legibles, por ejemplo, ASCII o UTF-8.

Generalmente, están organizados en líneas y se utilizan en formatos como `.txt`, `.csv` o `.c`.

**Ventajas:**
- Son fáciles de leer, inspeccionar y editar.
- Pueden abrirse con cualquier editor de texto compatible.
- Facilitan el intercambio de información entre distintos sistemas cuando se utiliza una codificación común.

### Archivos binarios

Los archivos binarios almacenan datos como secuencias de bytes, sin necesidad de convertirlos a una representación textual.

Por ejemplo, pueden almacenar directamente valores de tipo `int`, `float`, arreglos o estructuras (`struct`).

**Ventajas:**
- Evitan conversiones entre números y texto.
- Suelen ocupar menos espacio para datos numéricos o estructurados.
- Permiten lecturas y escrituras rápidas de bloques de memoria.

**Importante:** La representación binaria de algunos tipos puede variar entre sistemas, por lo que no siempre es portable.

### Modos de apertura de archivos

Los archivos se abren utilizando la función `fopen()`.

| Modo | Descripción |
|------|-------------|
| `"r"` | Abre un archivo existente únicamente para lectura. Conserva su contenido y comienza desde el inicio. |
| `"w"` | Abre un archivo para escritura. Si existe, elimina todo su contenido anterior. Si no existe, lo crea. |
| `"a"` | Abre un archivo para agregar información al final. Conserva el contenido anterior. Si no existe, lo crea. |

**Consideraciones:**

- `"r"` falla si el archivo no existe.
- `"w"` trunca el archivo existente a tamaño cero.
- `"a"` permite agregar datos sin sobrescribir los anteriores.
- Para trabajar con archivos binarios se utilizan modos como `"rb"`, `"wb"` y `"ab"`.

### Funciones fread() y fwrite()

Ambas funciones se utilizan principalmente para trabajar con archivos binarios, permitiendo transferir bloques de datos entre la memoria y un archivo.

**fread():**

Lee una cantidad determinada de elementos desde un archivo y los almacena en una dirección de memoria.

```c
fread(&variable, sizeof(variable), 1, archivo);
```

- Lee datos desde el archivo.
- Los copia a la memoria indicada.
- Sobrescribe los bytes correspondientes de la variable utilizada para recibirlos.
- Devuelve la cantidad de elementos leídos correctamente.

**fwrite():**

Escribe una cantidad determinada de elementos desde la memoria hacia un archivo.

```c
fwrite(&variable, sizeof(variable), 1, archivo);
```

- Toma datos desde la memoria.
- Los escribe en el archivo.
- Devuelve la cantidad de elementos escritos correctamente.

### Ejemplo práctico

```c
#include <stdio.h>

int main(void) {
    int numero = 25;
    int numeroLeido = 0;

    // Escritura de un archivo binario
    FILE *archivo = fopen("datos.bin", "wb");

    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return -1;
    }

    if (fwrite(&numero, sizeof(int), 1, archivo) != 1) {
        printf("Error al escribir\n");
        fclose(archivo);
        return -1;
    }

    fclose(archivo);

    // Lectura del archivo binario
    archivo = fopen("datos.bin", "rb");

    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return -1;
    }

    if (fread(&numeroLeido, sizeof(int), 1, archivo) != 1) {
        printf("Error al leer\n");
        fclose(archivo);
        return -1;
    }

    printf("Numero leido: %d\n", numeroLeido);

    fclose(archivo);

    return 0;
}
```

**Salida esperada:**

```text
Numero leido: 25
```

### Conceptos importantes

- **FILE*:** Puntero utilizado para manejar archivos en C.
- **fopen():** Abre un archivo y devuelve un puntero `FILE*`.
- **fclose():** Cierra un archivo abierto.
- **fread():** Lee bloques de datos desde un archivo.
- **fwrite():** Escribe bloques de datos en un archivo.
- **sizeof():** Devuelve el tamaño en bytes de un tipo o variable.
- **NULL:** Puede indicar que `fopen()` no pudo abrir el archivo.

---

## Resumen para repasar

### Memoria dinámica

| Función | Utilidad |
|---------|----------|
| `malloc()` | Reserva memoria sin inicializar |
| `calloc()` | Reserva memoria inicializada en cero |
| `realloc()` | Modifica el tamaño de memoria reservada |
| `free()` | Libera memoria reservada |

**Recordar:** Nunca asignar directamente el resultado de `realloc()` al único puntero que referencia la memoria original sin controlar el posible fallo.

### Archivos

| Concepto | Utilidad |
|----------|----------|
| Texto | Almacena caracteres legibles |
| Binario | Almacena datos como bytes |
| `"r"` | Leer |
| `"w"` | Escribir, borrando el contenido anterior |
| `"a"` | Agregar al final |
| `fread()` | Leer bloques de datos |
| `fwrite()` | Escribir bloques de datos |
| `fclose()` | Cerrar el archivo |

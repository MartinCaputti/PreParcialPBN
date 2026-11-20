/*Desarrollar un programa que permita almacenar los datos de 5 productos utilizando un
array de estructuras. Cada producto debe contener un c�digo (int), nombre (m�ximo 40
caracteres), precio (float) y cantidad disponible (int). Implementar una funci�n que cargue
los productos, otra que los muestre y una tercera que reciba el array y retorne el c�digo del
producto de mayor precio.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int codigo;
    char nombre[40];
    float precio;
    int cantDisp;
} Producto;

void cargarProducto(Producto[], int);
void mostrarTodos(Producto[], int);
int mayorPrecio(Producto[], int);

int main(void)
{

    Producto productos[5];
    int codigoMax = 0;

    cargarProducto(productos, 5);
    mostrarTodos(productos, 5);
    printf("el codigo del producto mas grande es %d", mayorPrecio(productos, 5));

    return 0;
}

void cargarProducto(Producto productos[], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("ingrese el nombre del producto #%d ", i);
        scanf("%s", productos[i].nombre);
        printf("ingrese el codigo del producto #%d ", i);
        scanf("%d", &productos[i].codigo);
        printf("ingrese el precio del producto #%d ", i);
        scanf("%f", &productos[i].precio);
        printf("ingrese la cantidad del producto #%d ", i);
        scanf("%d", &productos[i].cantDisp);
    }
}

void mostrarTodos(Producto productos[], int tam)
{

    for (int i = 0; i < tam; i++)
    {
        printf("Producto: %s \nCodigo: %d \nPrecio: %.2f \nCantidad disponible: %d \n\n",
        productos[i].nombre,
        productos[i].codigo,
        productos[i].precio,
        productos[i].cantDisp);
    }
}

int mayorPrecio(Producto productos[], int tam)
{
    int codigoMayor = productos[0].codigo;
    float precioMayor = productos[0].precio;
    for (int i = 1; i < tam; i++)
    {
        if (precioMayor < productos[i].precio)
        {
            precioMayor = productos[i].precio;
            codigoMayor = productos[i].codigo;
        }
    }

    return codigoMayor;
}

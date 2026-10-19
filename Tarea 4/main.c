#include <stdio.h>
#include <stdlib.h>

/*Para guardar los productos usé una lista enlazada simple, cada producto es un nodo (struct Producto) que contiene sus datos
(código, nombre, precio y cantidad) y un puntero siguiente que apunta al nodo que le sigue; el último apunta a NULL. El programa
solo conserva un puntero inicio que señala el primer nodo, y a partir de él se llega a todos los demás.
Para agregar al inicio, creo el nodo con malloc, hago que apunte al antiguo primer nodo y inicio pasa a apuntar a él.
 Para agregar al final, recorro la lista hasta el último nodo y lo enlazo con el nuevo. Para mostrar, buscar y contar,
  recorro los nodos uno a uno siguiendo los punteros. Para eliminar, busco el nodo guardando el anterior, hago que este apunte
   al siguiente del nodo borrado y libero su memoria con free y así, el inventario crece o se reduce mientras el programa corre, reservando memoria
   solo cuando se agrega un producto.*/


struct Producto {
    int codigo;
    char nombre[50];
    float precio;
    int cantidad;
    struct Producto *siguiente;
};

struct Producto *inicio = NULL;

struct Producto *crearProducto() {
    struct Producto *nuevo = malloc(sizeof(struct Producto));
    printf("Codigo: ");
    scanf("%d", &nuevo->codigo);
    printf("Nombre: ");
    scanf(" %[^\n]", nuevo->nombre);
    printf("Precio: ");
    scanf("%f", &nuevo->precio);
    printf("Cantidad: ");
    scanf("%d", &nuevo->cantidad);
    nuevo->siguiente = NULL;
    return nuevo;
}

void agregarInicio() {
    struct Producto *nuevo = crearProducto();
    nuevo->siguiente = inicio;
    inicio = nuevo;
    printf("Producto agregado al inicio.\n");
}

void agregarFinal() {
    struct Producto *nuevo = crearProducto();
    if (inicio == NULL) {
        inicio = nuevo;
    } else {
        struct Producto *aux = inicio;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = nuevo;
    }
    printf("Producto agregado al final.\n");
}

void mostrar() {
    struct Producto *aux = inicio;
    if (aux == NULL) {
        printf("El inventario esta vacio.\n");
        return;
    }
    while (aux != NULL) {
        printf("Codigo: %d | Nombre: %s | Precio: %.2f | Cantidad: %d\n",
               aux->codigo, aux->nombre, aux->precio, aux->cantidad);
        aux = aux->siguiente;
    }
}

void buscar() {
    int codigo;
    printf("Codigo a buscar: ");
    scanf("%d", &codigo);
    struct Producto *aux = inicio;
    while (aux != NULL) {
        if (aux->codigo == codigo) {
            printf("Encontrado -> Nombre: %s | Precio: %.2f | Cantidad: %d\n",
                   aux->nombre, aux->precio, aux->cantidad);
            return;
        }
        aux = aux->siguiente;
    }
    printf("Producto no encontrado.\n");
}

void eliminar() {
    int codigo;
    printf("Codigo a eliminar: ");
    scanf("%d", &codigo);
    struct Producto *aux = inicio, *anterior = NULL;
    while (aux != NULL && aux->codigo != codigo) {
        anterior = aux;
        aux = aux->siguiente;
    }
    if (aux == NULL) {
        printf("Producto no encontrado.\n");
        return;
    }
    if (anterior == NULL)
        inicio = aux->siguiente;
    else
        anterior->siguiente = aux->siguiente;
    free(aux);
    printf("Producto eliminado.\n");
}

int contar() {
    int total = 0;
    struct Producto *aux = inicio;
    while (aux != NULL) {
        total++;
        aux = aux->siguiente;
    }
    return total;
}

int main() {
    int opcion;
    do {
        printf("\n--- INVENTARIO ---\n");
        printf("1. Agregar al inicio\n");
        printf("2. Agregar al final\n");
        printf("3. Mostrar productos\n");
        printf("4. Buscar producto\n");
        printf("5. Eliminar producto\n");
        printf("6. Contar productos\n");
        printf("7. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: agregarInicio(); break;
            case 2: agregarFinal(); break;
            case 3: mostrar(); break;
            case 4: buscar(); break;
            case 5: eliminar(); break;
            case 6: printf("Total de productos: %d\n", contar()); break;
            case 7: printf("Adios.\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 7);

    return 0;
}

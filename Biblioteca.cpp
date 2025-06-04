#include <iostream>         // Librería para entrada y salida estándar (cin, cout)
#include <string>           // Librería para manejo de cadenas de texto (string)
using namespace std;        // Usar el espacio de nombres estándar para no escribir std::

struct Libro {              // Estructura que representa un nodo de libro en la lista enlazada
    string titulo;          // Título del libro
    Libro* siguiente;       // Puntero al siguiente libro en la lista
};

struct NodoCola {           // Nodo para cola de reservas
    string estudiante;      // Nombre del estudiante
    string libro;           // Título del libro reservado
    NodoCola* sig;          // Puntero al siguiente nodo en la cola
};

struct NodoPila {           // Nodo para pila de devoluciones
    string libro;           // Título del libro devuelto
    NodoPila* sig;          // Puntero al siguiente nodo en la pila
};

// Función para agregar un libro al catálogo
void agregar(Libro*& cabeza, string t) {
    Libro* nuevo = new Libro{t, NULL};             // Crear un nuevo nodo libro con título t
    if (!cabeza)                                   // Si la lista está vacía
        cabeza = nuevo;                            // El nuevo nodo se convierte en la cabeza
    else {
        Libro* temp = cabeza;                      // Apuntar al primer nodo
        while (temp->siguiente)                    // Recorrer hasta el último nodo
            temp = temp->siguiente;
        temp->siguiente = nuevo;                   // Insertar el nuevo nodo al final
    }
}

// Función para mostrar todos los libros del catálogo
void mostrar(Libro* cabeza) {
    for (Libro* temp = cabeza; temp; temp = temp->siguiente)  // Recorrer la lista
        cout << "- " << temp->titulo << "\n";                 // Imprimir el título de cada libro
}

// Función para ordenar los libros por título (método burbuja)
void ordenar(Libro* cabeza) {
    if (!cabeza) return;                        // Si la lista está vacía, no hacer nada
    bool cambiado;
    do {
        cambiado = false;                       // Reiniciar indicador de cambio
        for (Libro* a = cabeza; a && a->siguiente; a = a->siguiente) {
            if (a->titulo > a->siguiente->titulo) {           // Comparar títulos adyacentes
                swap(a->titulo, a->siguiente->titulo);        // Intercambiar si están desordenados
                cambiado = true;
            }
        }
    } while (cambiado);                         // Repetir mientras haya cambios
}

// Función para buscar un libro por título
bool buscar(Libro* cabeza, string t) {
    for (Libro* temp = cabeza; temp; temp = temp->siguiente) {
        if (temp->titulo == t)                  // Si el título coinci


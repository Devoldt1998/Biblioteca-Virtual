#include <iostream>         // Librer�a para entrada y salida est�ndar (cin, cout)
#include <string>           // Librer�a para manejo de cadenas de texto (string)
using namespace std;        // Usar el espacio de nombres est�ndar para no escribir std::

struct Libro {              // Estructura que representa un nodo de libro en la lista enlazada
    string titulo;          // T�tulo del libro
    Libro* siguiente;       // Puntero al siguiente libro en la lista
};

struct NodoCola {           // Nodo para cola de reservas
    string estudiante;      // Nombre del estudiante
    string libro;           // T�tulo del libro reservado
    NodoCola* sig;          // Puntero al siguiente nodo en la cola
};

struct NodoPila {           // Nodo para pila de devoluciones
    string libro;           // T�tulo del libro devuelto
    NodoPila* sig;          // Puntero al siguiente nodo en la pila
};

// Funci�n para agregar un libro al cat�logo
void agregar(Libro*& cabeza, string t) {
    Libro* nuevo = new Libro{t, NULL};             // Crear un nuevo nodo libro con t�tulo t
    if (!cabeza)                                   // Si la lista est� vac�a
        cabeza = nuevo;                            // El nuevo nodo se convierte en la cabeza
    else {
        Libro* temp = cabeza;                      // Apuntar al primer nodo
        while (temp->siguiente)                    // Recorrer hasta el �ltimo nodo
            temp = temp->siguiente;
        temp->siguiente = nuevo;                   // Insertar el nuevo nodo al final
    }
}

// Funci�n para mostrar todos los libros del cat�logo
void mostrar(Libro* cabeza) {
    for (Libro* temp = cabeza; temp; temp = temp->siguiente)  // Recorrer la lista
        cout << "- " << temp->titulo << "\n";                 // Imprimir el t�tulo de cada libro
}

// Funci�n para ordenar los libros por t�tulo (m�todo burbuja)
void ordenar(Libro* cabeza) {
    if (!cabeza) return;                        // Si la lista est� vac�a, no hacer nada
    bool cambiado;
    do {
        cambiado = false;                       // Reiniciar indicador de cambio
        for (Libro* a = cabeza; a && a->siguiente; a = a->siguiente) {
            if (a->titulo > a->siguiente->titulo) {           // Comparar t�tulos adyacentes
                swap(a->titulo, a->siguiente->titulo);        // Intercambiar si est�n desordenados
                cambiado = true;
            }
        }
    } while (cambiado);                         // Repetir mientras haya cambios
}

// Funci�n para buscar un libro por t�tulo
bool buscar(Libro* cabeza, string t) {
    for (Libro* temp = cabeza; temp; temp = temp->siguiente) {
        if (temp->titulo == t)                  // Si el t�tulo coinci


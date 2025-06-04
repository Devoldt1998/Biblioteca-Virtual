#include <iostream>         // Librería para entrada y salida estándar (cin, cout)
#include <string>           // Librería para manejo de cadenas de texto (string)
using namespace std;        // Usar el espacio de nombres estándar para no escribir std::

struct Libro {               // Estructura que representa un nodo de libro en lista enlazada
    string titulo;           // Título del libro
    Libro* siguiente;        // Puntero al siguiente libro en la lista
};

class Catalogo {             // Clase para manejar el catálogo de libros usando lista enlazada
public:
    Libro* cabeza = NULL;    // Puntero al primer libro en la lista (cabeza)

    void agregar(string t) { // Método para agregar un libro al final de la lista
        Libro* nuevo = new Libro{t, NULL};   // Crear un nuevo nodo libro con título t
        if (!cabeza)                         // Si la lista está vacía
            cabeza = nuevo;                  // Nuevo nodo es la cabeza
        else {                              // Si la lista no está vacía
            Libro* temp = cabeza;           // Apuntar al primer nodo
            while (temp->siguiente)         // Recorrer hasta el último nodo
                temp = temp->siguiente;
            temp->siguiente = nuevo;        // Insertar el nuevo nodo al final
        }
    }

    void mostrar() {                      // Método para mostrar todos los libros
        for (Libro* temp = cabeza; temp; temp = temp->siguiente)  // Recorrer la lista
            cout << "- " << temp->titulo << "\n";  // Imprimir título de cada libro
    }

    void ordenar() {                      // Método para ordenar libros por título (burbuja)
        if (!cabeza) return;              // Si la lista está vacía, no hacer nada
        bool cambiado;                    // Variable para detectar intercambios
        do {
            cambiado = false;             // Reiniciar indicador de cambio
            for (Libro* a = cabeza; a && a->siguiente; a = a->siguiente) { // Recorrer nodos
                if (a->titulo > a->siguiente->titulo) {   // Comparar títulos adyacentes
                    swap(a->titulo, a->siguiente->titulo); // Intercambiar títulos si desordenados
                    cambiado = true;         // Marcar que hubo un cambio
                }
            }
        } while (cambiado);               // Repetir mientras haya cambios
    }

    bool buscar(string t) {               // Método para buscar libro por título
        for (Libro* temp = cabeza; temp; temp = temp->siguiente) // Recorrer lista
            if (temp->titulo == t)        // Si el título coincide
                return true;              // Retornar true (encontrado)
        return false;                     // No encontrado, retornar false
    }
};

struct NodoCola {                       // Nodo para cola de reservas
    string estudiante, libro;            // Nombre del estudiante y título del libro
    NodoCola* sig;                      // Puntero al siguiente nodo en la cola
};

class Cola {                           // Clase para manejar reservas usando cola simple
public:
    NodoCola* frente = NULL, *fin = NULL;   // Punteros al frente y fin de la cola

    void encolar(string e, string l) {        // Método para agregar reserva al final
        NodoCola* nuevo = new NodoCola{e, l, NULL}; // Crear nuevo nodo con datos
        if (fin)                              // Si la cola no está vacía
            fin->sig = nuevo;                 // Apuntar último nodo al nuevo
        else
            frente = nuevo;                   // Si está vacía, nuevo nodo es frente
        fin = nuevo;                          // Actualizar el fin al nuevo nodo
    }

    void mostrar() {                         // Método para mostrar todas las reservas
        for (NodoCola* t = frente; t; t = t->sig)    // Recorrer la cola
            cout << "- " << t->estudiante << " reservó: " << t->libro << "\n";  // Mostrar datos
    }
};

struct NodoPila {                       // Nodo para pila de devoluciones
    string libro;                       // Título del libro devuelto
    NodoPila* sig;                     // Puntero al siguiente nodo en la pila
};

class Pila {                          // Clase para manejar devoluciones usando pila
public:
    NodoPila* cima = NULL;             // Puntero a la cima de la pila

    void apilar(string l) {            // Método para apilar un libro devuelto
        cima = new NodoPila{l, cima};  // Crear nuevo nodo y apuntarlo como cima
    }

    void mostrar() {                   // Método para mostrar devoluciones (pila)
        for (NodoPila* t = cima; t; t = t->sig)    // Recorrer la pila
            cout << "- " << t->libro << "\n";      // Mostrar título de cada libro
    }
};

int main() {
    setlocale(LC_CTYPE,"spanish");    // Configurar localización para caracteres en español
    Catalogo catalogo;                 // Crear instancia de catálogo de libros
    Cola reservas;                    // Crear instancia de cola para reservas
    Pila devoluciones;                // Crear instancia de pila para devoluciones
    int op;                          // Variable para opción del menú
    string titulo, estudiante;       // Variables para datos ingresados

    do {
        cout << "\n--- Menú Biblioteca ---\n";   // Mostrar menú principal
        cout << "1. Agregar libro\n2. Mostrar catálogo\n3. Ordenar catálogo\n4. Buscar libro\n";
        cout << "5. Agregar reserva\n6. Mostrar reservas\n7. Agregar devolución\n8. Mostrar devoluciones\n9. Salir\nOpción: ";
        cin >> op;                      // Leer opción del usuario
        cin.ignore();                   // Limpiar buffer para entrada de strings

        switch (op) {
            case 1:                     // Agregar libro
                cout << "Título: ";    
                getline(cin, titulo);   // Leer título completo (con espacios)
                catalogo.agregar(titulo);  // Agregar libro al catálogo
                break;
            case 2:                     // Mostrar catálogo
                catalogo.mostrar();    // Mostrar todos los libros
                break;
            case 3:                     // Ordenar catálogo
                catalogo.ordenar();    // Ordenar libros por título
                cout << "Ordenado.\n"; 
                break;
            case 4:                     // Buscar libro
                cout << "Buscar: ";
                getline(cin, titulo);   // Leer título a buscar
                cout << (catalogo.buscar(titulo) ? "Encontrado\n" : "No encontrado\n"); // Mostrar resultado
                break;
            case 5:                     // Agregar reserva
                cout << "Estudiante: ";
                getline(cin, estudiante);   // Leer nombre estudiante
                cout << "Libro: ";
                getline(cin, titulo);       // Leer título libro reservado
                reservas.encolar(estudiante, titulo); // Agregar reserva a la cola
                break;
            case 6:                     // Mostrar reservas
                reservas.mostrar();     // Mostrar todas las reservas
                break;
            case 7:                     // Agregar devolución
                cout << "Libro devuelto: ";
                getline(cin, titulo);   // Leer título libro devuelto
                devoluciones.apilar(titulo);   // Apilar en pila de devoluciones
                break;
            case 8:                     // Mostrar devoluciones
                devoluciones.mostrar(); // Mostrar todos los libros devueltos
                break;
            case 9:                     // Salir
                cout << "Saliendo...\n"; // Mensaje de despedida
                break;
            default:                    // Opción inválida
                cout << "Opción inválida\n";
        }
    } while (op != 9);                 // Repetir hasta que el usuario seleccione salir

    return 0;                          // Terminar el programa exitosamente
}

#include <iostream>         // Librería para entrada y salida estándar (cin, cout)
#include <string>           // Librería para manejo de cadenas de texto (string)
using namespace std;        // Usar el espacio de nombres estándar para no escribir std::

struct Libro {               // Estructura que representa un nodo de libro en lista enlazada
    string titulo;           // Título del libro
    Libro* siguiente;        // Puntero al siguiente libro en la lista
};

struct NodoCola {                       						// Nodo para cola de reservas
    string estudiante, libro;          								  // Nombre del estudiante y título del libro
    NodoCola* sig;                      											// Puntero al siguiente nodo en la cola
};

struct NodoPila {                       // Nodo para pila de devoluciones
    string libro;                       // Título del libro devuelto
    NodoPila* sig;                     // Puntero al siguiente nodo en la pila
};

																	// Función para agregar un libro al catálogo
void agregar(Libro*& cabeza, string t) {
    Libro* nuevo = new Libro{t, NULL};   							// Crear un nuevo nodo libro con título t
    if (!cabeza)                        						 // Si la lista está vacía
        cabeza = nuevo;                 						 // Nuevo nodo es la cabeza
    else {                              									// Si la lista no está vacía
        Libro* temp = cabeza;           								// Apuntar al primer nodo
        while (temp->siguiente)         								// Recorrer hasta el último nodo
            temp = temp->siguiente;
        temp->siguiente = nuevo;        											// Insertar el nuevo nodo al final
    }
}

																										// Función para mostrar todos los libros
void mostrar(Libro* cabeza) {
    for (Libro* temp = cabeza; temp; temp = temp->siguiente)  										 // Recorrer la lista
        cout << "- " << temp->titulo << "\n";  															// Imprimir título de cada libro
}

																					// Función para ordenar libros por título (burbuja)
void ordenar(Libro* cabeza) {
    if (!cabeza) return;              												 // Si la lista está vacía, no hacer nada
    bool cambiado;                   													 // Variable para detectar intercambios
    do {
        cambiado = false;             																	 // Reiniciar indicador de cambio
        for (Libro* a = cabeza; a && a->siguiente; a = a->siguiente) {														  // Recorrer nodos
            if (a->titulo > a->siguiente->titulo) {  															 // Comparar títulos adyacentes
                swap(a->titulo, a->siguiente->titulo); 															// Intercambiar títulos si desordenados
                cambiado = true;        																	 // Marcar que hubo un cambio
            }
        }
    } while (cambiado);                // Repetir mientras haya cambios
}

																						// Función para buscar libro por título
bool buscar(Libro* cabeza, string t) {
    for (Libro* temp = cabeza; temp; temp = temp->siguiente)  									// Recorrer lista
        if (temp->titulo == t)       														// Si el título coincide
            return true;             									// Retornar true (encontrado)
    return false;                    														 // No encontrado, retornar false
}

																								// Función para agregar una reserva al final de la cola
void encolar(NodoCola*& frente, NodoCola*& fin, string e, string l) {
    NodoCola* nuevo = new NodoCola{e, l, NULL};  								// Crear nuevo nodo con datos
    if (fin)                              													 // Si la cola no está vacía
        fin->sig = nuevo;                  										// Apuntar último nodo al nuevo
    else
        frente = nuevo;                  											 // Si está vacía, nuevo nodo es frente
    fin = nuevo;                        																 // Actualizar el fin al nuevo nodo
}

																							// Función para mostrar todas las reservas
void mostrarReservas(NodoCola* frente) {
    for (NodoCola* t = frente; t; t = t->sig) 																					 // Recorrer la cola
        cout << "- " << t->estudiante << " reservó: " << t->libro << "\n"; 														 // Mostrar datos
}

																																			// Función para apilar un libro devuelto
void apilar(NodoPila*& cima, string l) {
    cima = new NodoPila{l, cima};  																	 // Crear nuevo nodo y apuntarlo como cima
}

																					// Función para mostrar todas las devoluciones
void mostrarDevoluciones(NodoPila* cima) {
    for (NodoPila* t = cima; t; t = t->sig) 											 // Recorrer la pila
        cout << "- " << t->libro << "\n";  															// Mostrar título de cada libro
}

int main() {
    setlocale(LC_CTYPE,"spanish");    // Configurar localización para caracteres en español
    Libro* catalogo = NULL;           // Puntero al catálogo de libros
    NodoCola* reservasFrente = NULL, *reservasFin = NULL;  // Punteros para la cola de reservas
    NodoPila* devolucionesCima = NULL;  // Puntero a la cima de la pila de devoluciones
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
                agregar(catalogo, titulo);  // Agregar libro al catálogo
                break;
            case 2:                     // Mostrar catálogo
                mostrar(catalogo);    // Mostrar todos los libros
                break;
            case 3:                     // Ordenar catálogo
                ordenar(catalogo);    // Ordenar libros por título
                cout << "Ordenado.\n"; 
                break;
            case 4:                     // Buscar libro
                cout << "Buscar: ";
                getline(cin, titulo);   // Leer título a buscar
                cout << (buscar(catalogo, titulo) ? "Encontrado\n" : "No encontrado\n"); // Mostrar resultado
                break;
            case 5:                     // Agregar reserva
                cout << "Estudiante: ";
                getline(cin, estudiante);   // Leer nombre estudiante
                cout << "Libro: ";
                getline(cin, titulo);       // Leer título libro reservado
                encolar(reservasFrente, reservasFin, estudiante, titulo); // Agregar reserva a la cola
                break;
            case 6:                     // Mostrar reservas
                mostrarReservas(reservasFrente);     // Mostrar todas las reservas
                break;
            case 7:                     // Agregar devolución
                cout << "Libro devuelto: ";
                getline(cin, titulo);   // Leer título libro devuelto
                apilar(devolucionesCima, titulo);   // Apilar en pila de devoluciones
                break;
            case 8:                     // Mostrar devoluciones
                mostrarDevoluciones(devolucionesCima); // Mostrar todos los libros devueltos
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




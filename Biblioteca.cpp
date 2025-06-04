#include <iostream>         // Librer�a para entrada y salida est�ndar (cin, cout)
#include <string>           // Librer�a para manejo de cadenas de texto (string)
using namespace std;        // Usar el espacio de nombres est�ndar para no escribir std::

struct Libro {               // Estructura que representa un nodo de libro en lista enlazada
    string titulo;           // T�tulo del libro
    Libro* siguiente;        // Puntero al siguiente libro en la lista
};

struct NodoCola {                       						// Nodo para cola de reservas
    string estudiante, libro;          								  // Nombre del estudiante y t�tulo del libro
    NodoCola* sig;                      											// Puntero al siguiente nodo en la cola
};

struct NodoPila {                       // Nodo para pila de devoluciones
    string libro;                       // T�tulo del libro devuelto
    NodoPila* sig;                     // Puntero al siguiente nodo en la pila
};

																	// Funci�n para agregar un libro al cat�logo
void agregar(Libro*& cabeza, string t) {
    Libro* nuevo = new Libro{t, NULL};   							// Crear un nuevo nodo libro con t�tulo t
    if (!cabeza)                        						 // Si la lista est� vac�a
        cabeza = nuevo;                 						 // Nuevo nodo es la cabeza
    else {                              									// Si la lista no est� vac�a
        Libro* temp = cabeza;           								// Apuntar al primer nodo
        while (temp->siguiente)         								// Recorrer hasta el �ltimo nodo
            temp = temp->siguiente;
        temp->siguiente = nuevo;        											// Insertar el nuevo nodo al final
    }
}

																										// Funci�n para mostrar todos los libros
void mostrar(Libro* cabeza) {
    for (Libro* temp = cabeza; temp; temp = temp->siguiente)  										 // Recorrer la lista
        cout << "- " << temp->titulo << "\n";  															// Imprimir t�tulo de cada libro
}

																					// Funci�n para ordenar libros por t�tulo (burbuja)
void ordenar(Libro* cabeza) {
    if (!cabeza) return;              												 // Si la lista est� vac�a, no hacer nada
    bool cambiado;                   													 // Variable para detectar intercambios
    do {
        cambiado = false;             																	 // Reiniciar indicador de cambio
        for (Libro* a = cabeza; a && a->siguiente; a = a->siguiente) {														  // Recorrer nodos
            if (a->titulo > a->siguiente->titulo) {  															 // Comparar t�tulos adyacentes
                swap(a->titulo, a->siguiente->titulo); 															// Intercambiar t�tulos si desordenados
                cambiado = true;        																	 // Marcar que hubo un cambio
            }
        }
    } while (cambiado);                // Repetir mientras haya cambios
}

																						// Funci�n para buscar libro por t�tulo
bool buscar(Libro* cabeza, string t) {
    for (Libro* temp = cabeza; temp; temp = temp->siguiente)  									// Recorrer lista
        if (temp->titulo == t)       														// Si el t�tulo coincide
            return true;             									// Retornar true (encontrado)
    return false;                    														 // No encontrado, retornar false
}

																								// Funci�n para agregar una reserva al final de la cola
void encolar(NodoCola*& frente, NodoCola*& fin, string e, string l) {
    NodoCola* nuevo = new NodoCola{e, l, NULL};  								// Crear nuevo nodo con datos
    if (fin)                              													 // Si la cola no est� vac�a
        fin->sig = nuevo;                  										// Apuntar �ltimo nodo al nuevo
    else
        frente = nuevo;                  											 // Si est� vac�a, nuevo nodo es frente
    fin = nuevo;                        																 // Actualizar el fin al nuevo nodo
}

																							// Funci�n para mostrar todas las reservas
void mostrarReservas(NodoCola* frente) {
    for (NodoCola* t = frente; t; t = t->sig) 																					 // Recorrer la cola
        cout << "- " << t->estudiante << " reserv�: " << t->libro << "\n"; 														 // Mostrar datos
}

																																			// Funci�n para apilar un libro devuelto
void apilar(NodoPila*& cima, string l) {
    cima = new NodoPila{l, cima};  																	 // Crear nuevo nodo y apuntarlo como cima
}

																					// Funci�n para mostrar todas las devoluciones
void mostrarDevoluciones(NodoPila* cima) {
    for (NodoPila* t = cima; t; t = t->sig) 											 // Recorrer la pila
        cout << "- " << t->libro << "\n";  															// Mostrar t�tulo de cada libro
}

int main() {
    setlocale(LC_CTYPE,"spanish");    // Configurar localizaci�n para caracteres en espa�ol
    Libro* catalogo = NULL;           // Puntero al cat�logo de libros
    NodoCola* reservasFrente = NULL, *reservasFin = NULL;  // Punteros para la cola de reservas
    NodoPila* devolucionesCima = NULL;  // Puntero a la cima de la pila de devoluciones
    int op;                          // Variable para opci�n del men�
    string titulo, estudiante;       // Variables para datos ingresados

    do {
        cout << "\n--- Men� Biblioteca ---\n";   // Mostrar men� principal
        cout << "1. Agregar libro\n2. Mostrar cat�logo\n3. Ordenar cat�logo\n4. Buscar libro\n";
        cout << "5. Agregar reserva\n6. Mostrar reservas\n7. Agregar devoluci�n\n8. Mostrar devoluciones\n9. Salir\nOpci�n: ";
        cin >> op;                      // Leer opci�n del usuario
        cin.ignore();                   // Limpiar buffer para entrada de strings

        switch (op) {
            case 1:                     // Agregar libro
                cout << "T�tulo: ";    
                getline(cin, titulo);   // Leer t�tulo completo (con espacios)
                agregar(catalogo, titulo);  // Agregar libro al cat�logo
                break;
            case 2:                     // Mostrar cat�logo
                mostrar(catalogo);    // Mostrar todos los libros
                break;
            case 3:                     // Ordenar cat�logo
                ordenar(catalogo);    // Ordenar libros por t�tulo
                cout << "Ordenado.\n"; 
                break;
            case 4:                     // Buscar libro
                cout << "Buscar: ";
                getline(cin, titulo);   // Leer t�tulo a buscar
                cout << (buscar(catalogo, titulo) ? "Encontrado\n" : "No encontrado\n"); // Mostrar resultado
                break;
            case 5:                     // Agregar reserva
                cout << "Estudiante: ";
                getline(cin, estudiante);   // Leer nombre estudiante
                cout << "Libro: ";
                getline(cin, titulo);       // Leer t�tulo libro reservado
                encolar(reservasFrente, reservasFin, estudiante, titulo); // Agregar reserva a la cola
                break;
            case 6:                     // Mostrar reservas
                mostrarReservas(reservasFrente);     // Mostrar todas las reservas
                break;
            case 7:                     // Agregar devoluci�n
                cout << "Libro devuelto: ";
                getline(cin, titulo);   // Leer t�tulo libro devuelto
                apilar(devolucionesCima, titulo);   // Apilar en pila de devoluciones
                break;
            case 8:                     // Mostrar devoluciones
                mostrarDevoluciones(devolucionesCima); // Mostrar todos los libros devueltos
                break;
            case 9:                     // Salir
                cout << "Saliendo...\n"; // Mensaje de despedida
                break;
            default:                    // Opci�n inv�lida
                cout << "Opci�n inv�lida\n";
        }
    } while (op != 9);                 // Repetir hasta que el usuario seleccione salir

    return 0;                          // Terminar el programa exitosamente
}




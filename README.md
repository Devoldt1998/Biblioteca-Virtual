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

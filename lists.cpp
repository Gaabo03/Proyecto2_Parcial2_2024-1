#include "lists.h"

lists::lists(){
}

void lists::newNodo(Nodo *&acceso, int _price, COORD _position, char* _name, bool _isHere, int _id)
{
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->price = _price;
    nuevo_nodo->position = _position;
    strncpy(nuevo_nodo->name, _name, sizeof(nuevo_nodo->name) - 1);
    nuevo_nodo->name[sizeof(nuevo_nodo->name) - 1] = '\0';
    nuevo_nodo->isHere = _isHere;
    nuevo_nodo->id = _id;
    

    if (acceso == NULL)
    {
        acceso = nuevo_nodo;
        acceso->sig = acceso;
        acceso->ant = acceso;
    }
    else
    {
        nuevo_nodo->sig = acceso;
        nuevo_nodo->ant = acceso->ant;
        nuevo_nodo->ant->sig = nuevo_nodo;
        acceso->ant = nuevo_nodo;
        acceso = nuevo_nodo;
    }
}

void lists::read(const char *nombreArchivo, int indice, Binario *datos)
{
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo)
    {
        std::cerr << "NO SE PUDO ABRIR EL ARCHIVO." << std::endl;
    }
	
    size_t posicion = indice * sizeof(Binario);
    archivo.seekg(posicion);
    if (!archivo.read(reinterpret_cast<char *>(datos), sizeof(Binario)))
    {
        std::cerr << "ERROR AL LEER DEL ARCHIVO." << std::endl;
    }
}

void lists::readLoop(Nodo *&acceso, const char *nombre_archivo)
{
    Binario auxiliar;
    int size = static_cast<int>(getSize(nombre_archivo));
    if (isEmpty(nombre_archivo))
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        read(nombre_archivo, i, &auxiliar);
        newNodo(acceso, auxiliar.price, auxiliar.position, auxiliar.name, false, 0);
    }
}

size_t lists::getSize(const char *nombreArchivo)
{
    std::ifstream archivo(nombreArchivo, std::ios::binary | std::ios::ate);
    if (!archivo)
    {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 0;
    }
    size_t tamanoDelArchivo = archivo.tellg();
    return tamanoDelArchivo / sizeof(Binario);
}

bool lists::isEmpty(const char* nombreArchivo)
{
    std::ifstream archivo(nombreArchivo, std::ios::binary | std::ios::ate);
    if (!archivo)
    {
        return true;
    }
    return archivo.tellg() == 0;
}

void lists::printAll(Nodo *acceso)
{
    Nodo *actual = acceso;
    do
    {
        std::cout << actual->name << "\n";
        std::cout << actual->position.X << "\n";
		std::cout << actual->position.Y << "\n";
        actual = actual->sig;
    } while (actual != acceso);
}

void lists::guardarTodo(){
	Binario *datos;
	char nombre[45];
	
	for(int i = 0; i<28; i++){
		std::ofstream archivo("tablero.txt", std::ios::binary | std::ios::app);
		std::cout << "NOMBRE: ";
		std::cin.getline(datos->name, 45);
		std::cout << "PRECIO: ";
		std::cin >> datos->price;
		std::cout << "X: ";
		std::cin >> datos->position.X;
		std::cout << "Y: ";
		std::cin >> datos->position.Y;
	    if (!archivo)
	    {
	        std::cout << "NO SE PUDO ABRIR EL ARCHIVO.";
	        return;
	    }
    	archivo.write(reinterpret_cast<const char *>(datos), sizeof(Binario));
    	archivo.close();
	}
}

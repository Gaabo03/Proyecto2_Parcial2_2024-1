#include "lists.h"

lists::lists(){
}

void lists::newNodo(Nodo *&acceso, int _price, COORD _position, char* _name)
{
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->price = _price;
    nuevo_nodo->position = _position;
    strncpy(nuevo_nodo->name, _name, sizeof(nuevo_nodo->name) - 1);
    nuevo_nodo->name[sizeof(nuevo_nodo->name) - 1] = '\0';
    for(int i = 0; i<4; i++){
    	nuevo_nodo->houseHere[i] = false;
    	nuevo_nodo->isHere[i] = false;
	}
    

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
        newNodo(acceso, auxiliar.price, auxiliar.position, auxiliar.name);
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
	int i = 0;
    Nodo *actual = acceso;
    do
    {
    	std::cout << i << "\n";
    	i++;
        std::cout << actual->name << "\n";
        std::cout << actual->position.X << "\n";
		std::cout << actual->position.Y << "\n\n";
        actual = actual->sig;
    } while (actual != acceso);
}

void lists::guardarTodo(){
	Binario *nuevo_nodo = new Binario();
	char nombre[45];
	
	for(int i = 0; i<28; i++){
		std::ofstream archivo("tablero.txt", std::ios::binary | std::ios::app);
		std::cout << "NOMBRE: ";
		std::cin.getline(nombre, 45);
		strncpy(nuevo_nodo->name, nombre, sizeof(nuevo_nodo->name) - 1);
   		nuevo_nodo->name[sizeof(nuevo_nodo->name) - 1] = '\0';
		std::cout << "PRECIO: ";
		std::cin >> nuevo_nodo->price;
		std::cout << "X: ";
		std::cin >> nuevo_nodo->position.X;
		std::cout << "Y: ";
		std::cin >> nuevo_nodo->position.Y;
		std::cout << "COLOR: ";
		std::cin >> nuevo_nodo->color;
		std::cin.ignore();
	    if (!archivo)
	    {
	        std::cout << "NO SE PUDO ABRIR EL ARCHIVO.";
	        return;
	    }
    	archivo.write(reinterpret_cast<const char *>(nuevo_nodo), sizeof(Binario));
    	archivo.close();
	}
}

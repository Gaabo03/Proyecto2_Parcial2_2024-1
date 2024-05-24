#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include "lists.h"

class Interface {
public:
	void menu();
	std::vector<std::string> pedirDatos();
	void imprimirTablero(lists::Nodo *acceso, std::vector<std::string> nombres);
	void imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const std::string texto);
	void actualizarTablero(lists::Nodo *acceso);
};

#endif

#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <windows.h>
#include "lists.h"

class Interface {
public:
	void menu();
	void imprimirTablero(lists::Nodo *acceso);
	void imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const char *texto);
};

#endif

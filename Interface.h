#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "lists.h"

class Interface {
public:
	int nJugadores;
	
	bool menu();
	std::vector<std::string> pedirDatos();
	void imprimirTablero(lists::Nodo* acceso, std::vector<std::string> nombres, int* pagoMovil);
	void imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const std::string texto);
	void imprimirEnPosicion(int x, int y, int textColor, int backgroundColor, const std::string texto);
	void actualizarTablero(int dado, std::string jugador);
	void actualizarTablero(lists::Nodo *acceso, int* pagoMovil);
	char* preguntarJugador(const std::string& pregunta);
};

#endif

#include <iostream>
#include <windows.h>
#include "lists.h"
#include "Interface.h"

void imprimirEnPosicion(COORD posicion, const char *texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    std::cout << texto;
}

int main(int argc, char** argv) {
	lists lista;
	lists::Nodo *puntoAcceso = NULL;
	lista.readLoop(*&puntoAcceso, "tablero.txt");
	Interface interfaz;
	interfaz.imprimirTablero(puntoAcceso);
}

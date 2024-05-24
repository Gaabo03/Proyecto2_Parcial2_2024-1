#include "interface.h"

using namespace std;

void Interface::menu(){
}

void Interface::imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const string texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCursorPosition(hConsole, posicion);
    int colorAttribute = (backgroundColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
    std::cout << texto << endl;;
}

void Interface::imprimirTablero(lists::Nodo *acceso){
	COORD casilla;
	
	//Imprimiento lineas verticales
	casilla.X = 4;
	casilla.Y = 3;
	for (int i = 0; i < 3; ++i) {
	    imprimirEnPosicion(casilla, 15, 0, "|      |      |      |      |      |      |      |      |");
	    casilla.Y++;
	}
	for (int i = 0; i < 25; ++i) {
	    imprimirEnPosicion(casilla, 15, 0, "|      |                                         |      |");
	    casilla.Y++;
	}
	for (int i = 0; i < 3; ++i) {
	    imprimirEnPosicion(casilla, 15, 0, "|      |      |      |      |      |      |      |      |");
	    casilla.Y++;
	}
	
	//Imprimiendo lineas horizontales
	casilla.X = 4;
	casilla.Y = 2;
	for (int i = 0; i < 2; ++i) {
	    imprimirEnPosicion(casilla, 15, 0, "---------------------------------------------------------");
	    casilla.Y += 4;
	}
	
	for (int i = 0; i < 5; ++i) {
	    imprimirEnPosicion(casilla, 15, 0, "--------                                         --------");
	    casilla.Y += 4;
	}
	
	for (int i = 0; i < 2; ++i) {
	    imprimirEnPosicion(casilla, 15, 0, "---------------------------------------------------------");
	    casilla.Y += 4;
	}
	
	lists::Nodo *actual = acceso;
	for(int i = 0; i <28; i++){
		casilla.X = actual->position.X - 2;
		casilla.Y = actual->position.Y - 2;
		
		stringstream ss;
		if(i == 0){
			ss << " HOME ";
		} else if (i == 7 || i == 21){
			ss << "  ??  ";
		} else if (i == 14){
			ss << " JAIL ";
		} else{
			ss << " $" << actual->price << " ";
		}
		
		imprimirEnPosicion(casilla, 0, actual->color, ss.str());
		casilla.Y++;
		for (int j = casilla.Y+2; casilla.Y < j; casilla.Y++){
			imprimirEnPosicion(casilla, 0, 15, "      ");
		}
		
		actual = actual->ant;
	}
	
	casilla.X = 0;
	casilla.Y = 40;
	imprimirEnPosicion(casilla, 15, 0, "");
}

void Interface::actualizarTablero(lists::Nodo *acceso){
	
}



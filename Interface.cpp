#include "interface.h"

using namespace std;

void Interface::menu(){
}

void Interface::imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const string texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    int colorAttribute = (backgroundColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
    std::cout << texto << endl;;
}

void Interface::imprimirTablero(lists::Nodo *acceso){
	//Impresion de bordes
	cout << endl << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	
	// Impresion de casillas del tablero
	lists::Nodo *actual = acceso;
	for (int i = 0; i < 28; i++){
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
		imprimirEnPosicion(actual->position, 0, actual->color, ss.str());
		actual->position.Y++;
		imprimirEnPosicion(actual->position, 0, 15, "      ");
		actual = actual->ant;
	}
	
	
	COORD casilla;
	casilla.X = 0;
	casilla.Y = 28;
	imprimirEnPosicion(casilla, 15, 0, "");
	system("PAUSE");
}


void Interface::actualizarTablero(lists::Nodo *acceso){
	
}



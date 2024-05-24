#include "interface.h"

using namespace std;

void Interface::menu(){
}

void Interface::imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const char *texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    int colorAttribute = (backgroundColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
    std::cout << texto;
}

void Interface::imprimirTablero(lists::Nodo *acceso){
	cout << endl << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |  ??  | $    | $    | $    | $    | $    | $    | JAIL |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    | $    |                                         | $    |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    | $    |                                         | $    |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    | $    |                                         | $    |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    | $    |                                         | $    |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    | $    |                                         | $    |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    --------                                         --------" << endl;
	cout << "    | $    |                                         | $    |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    | HOME | $    | $    | $    | $    | $    | $    |  ??  |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	
	lists::Nodo *actual = acceso->ant;
	cout << actual->price;
	imprimirEnPosicion(actual->position, 0, actual->color, "  ");
}



#include "interface.h"

using namespace std;

void Interface::imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const string texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    int colorAttribute = (backgroundColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
    std::cout << texto << endl;;
}

void Interface::menu(){
	int resp;
	do{
		system("cls");
		cout << endl << endl;
		cout << "    =========================================================" << endl;
		cout << "    |              M  O  N  O  P  O  L  I  O                |" << endl;
		cout << "    =========================================================" << endl;
		cout << "    |------                                  ---------------|" << endl;
		cout << "    |-----------             1. JUGAR           ------------|" << endl;
		cout << "    |--------------                                     ----|" << endl;
		cout << "    |-----------             2. REGLAS          ------------|" << endl;
		cout << "    |------------                           ----------------|" << endl;
		cout << "    |-----------             3. SALIR           ------------|" << endl;
		cout << "    |-------                                          ------|" << endl;
		cout << "    =========================================================" << endl;
		cout << "    | Eleccion: ";
		cin >> resp;
	} while(resp <1 || resp > 3);
	
	switch(resp){
		case 1:
			return;
		case 2:
			break;
		case 3:
			break;
		default:
			cout << "Debe haber algún error" << endl;
	}
}

vector<string> Interface::pedirDatos(){
	vector<string> jugadores;
	string nombre;
	int nPlayers;
	
	system("cls");
	cout << endl << endl;
	cout << "    =========================================================" << endl;
	cout << "    | Ingrese numero de jugadores: ";
	cin >> nPlayers;
	cin.ignore();
	for (int i = 0; i < nPlayers; i++){
		cout << "    | Nombre del Jugador " << (i+1) << ": ";
		getline(cin, nombre);
		jugadores.push_back(nombre);
	}
	return jugadores;
}


void Interface::imprimirTablero(lists::Nodo* acceso, vector<string> nombres){
	system("cls");
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
	for (int i = 0; i < 28; i++){
		stringstream ss;
		if(i == 0){
			ss << " HOME ";
		} else if (i == 7 || i == 21){
			ss << "  ??  ";
		} else if (i == 14){
			ss << " JAIL ";
		} else{
			ss << " $" << acceso->price << " ";
		}
		imprimirEnPosicion(acceso->position, 0, acceso->color, ss.str());
		acceso->position.Y++;
		imprimirEnPosicion(acceso->position, 0, 15, "      ");
		acceso = acceso->ant;
	}
	
	// Impresion de nombre jugadores
	COORD pos;
	pos.X = 62; 
	pos.Y = 3;
	for (int i = 0; i < nombres.size(); i++){
		stringstream ss;
		ss << "'**' is " << nombres[i];
		imprimirEnPosicion(pos, i+3, 0, ss.str());
		pos.Y +=2;
	}
	
	actualizarTablero(acceso);
}


void Interface::actualizarTablero(lists::Nodo *acceso){
	for (int i =0; i < 28; i++){
		COORD casilla;
		casilla.Y = acceso->position.Y;
		for (int j = 0; j < 4; j++){
			casilla.X = acceso->position.X+1+j;
			if (acceso->isHere[j]){
				imprimirEnPosicion(casilla, j+3, 15, "*");
			} else {
				imprimirEnPosicion(casilla, j+3, 15, " ");
			}
		}
	}
}



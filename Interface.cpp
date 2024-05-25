#include "interface.h"

using namespace std;

void Interface::imprimirEnPosicion(COORD posicion, int textColor, int backgroundColor, const string texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    int colorAttribute = (backgroundColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
    std::cout << texto << endl;;
}

void Interface::imprimirEnPosicion(int x, int y, int textColor, int backgroundColor, const string texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posicion;
    posicion.X = x;
    posicion.Y = y;
    SetConsoleCursorPosition(hConsole, posicion);
    int colorAttribute = (backgroundColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
    std::cout << texto << endl;;
}

bool Interface::menu(){
	while(true){
		char tecla = '\0';
		cout << endl << endl;
		cout << "    =========================================================" << endl;
		cout << "    |                 M  O  N  O  P  O  L  Y                |" << endl;
		cout << "    =========================================================" << endl;
		cout << "    |------                                  ---------------|" << endl;
		cout << "    |-----------             1. JUGAR           ------------|" << endl;
		cout << "    |--------------                                     ----|" << endl;
		cout << "    |-----------             2. REGLAS          ------------|" << endl;
		cout << "    |------------                           ----------------|" << endl;
		cout << "    |-----------             3. SALIR           ------------|" << endl;
		cout << "    |-------                                          ------|" << endl;
		cout << "    |-------           Selecciona el numero           ------|" << endl;
		cout << "    =========================================================" << endl;
		
		do{
			tecla = _getch();
		} while(tecla != '1' && tecla != '2' && tecla != '3');
		
		switch(tecla){
			case '1':
				return true;
			case '2':
				//imprimirReglas();
				break;
			case '3':
				cout << "     Muchas gracias por jugar :)" << endl;
				return false;
			default:
				cout << "Debe haber algún error" << endl;
		}
	}
}

vector<string> Interface::pedirDatos(){
	vector<string> jugadores;
	string nombre;
	int nPlayers;
	
	system("cls");
	cout << endl << endl;
	cout << "    =========================================================" << endl;
	do{
	cout << "    | Digite numero de jugadores (MAX 4): ";
	cin >> nPlayers;
	}while(nPlayers<1 || nPlayers>4);
	nJugadores = nPlayers;
	cin.ignore();
	for (int i = 0; i < nPlayers; i++){
		cout << "    | Nombre del Jugador " << (i+1) << ": ";
		getline(cin, nombre);
		jugadores.push_back(nombre);
	}
	return jugadores;
}

void Interface::imprimirTablero(lists::Nodo* acceso, vector<string> nombres, int* pagoMovil){
	system("cls");
	//Impresion de bordes
	cout << endl << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    |      |      |      |      |      |      |      |      |" << endl;
	cout << "    ---------------------------------------------------------" << endl;
	cout << "    |      |                                         |      |" << endl;
	cout << "    |      |  Turno de:                              |      |" << endl;
	cout << "    --------  Dado:                                  --------" << endl;
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
	for (int i = 0; i < nombres.size(); i++){
		stringstream ss;
		ss << "'*' " << nombres[i];
		imprimirEnPosicion(67, 3+(2*i), i+3, 0, ss.str());
	}
	
	actualizarTablero(acceso, pagoMovil);
}

void Interface::actualizarTablero(int dado, string jugador){
	imprimirEnPosicion(24, 7, 15, 0, "                    ");
	imprimirEnPosicion(24, 7, 15, 0, jugador);
	stringstream ss;
	ss << dado;
	imprimirEnPosicion(20, 8, 15, 0, ss.str());
	cin.get();
}


void Interface::actualizarTablero(lists::Nodo *acceso, int* pagoMovil){
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
		acceso = acceso->ant;
	}
	
	for (int i = 0; i < nJugadores; i++){
		stringstream ss;
		if (pagoMovil[i] > 0){
			ss << "$" << pagoMovil[i];
			imprimirEnPosicion(62, 3+(2*i), i+3, 0, ss.str());
		}
	}
}

#include "interface.h"
#include <iostream>
#include <conio.h> // Para _getch()

using namespace std;

// Otras funciones ya definidas

char* Interface::preguntarJugador(const string& pregunta) {
    static char respuesta[2];
    char tecla = '\0';
    
    while (true) {
    	imprimirEnPosicion(15, 11, 15, 0, pregunta);
        tecla = _getch(); // Espera a que el usuario presione una tecla

        if (tecla == 'S' || tecla == 's') {
            respuesta[0] = 'S';
            break;
        } else if (tecla == 'N' || tecla == 'n') {
            respuesta[0] = 'N';
            break;
        }
    }
    imprimirEnPosicion(15, 11, 15, 0, "                                   ");
    return respuesta;
}




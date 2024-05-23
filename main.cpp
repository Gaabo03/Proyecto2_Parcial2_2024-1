#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include "lists.h"
#define MAXMONEY 500

lists lista;
lists::Nodo *acceso = NULL;
int pagoMovil[4];
bool gameOver = false;
void start(int _nPlayers);
void init(int _nPlayers);
std::vector<lists::Nodo*> accesoJugador;
int random();
const char* datos[] = {
        "GO TO JAIL",
        "GO TO THE START",
        "GO TO PAY THE ELECTRICITY BILL",
        "GO TO THE RAILWAY",
        "GO TO THE HARBOR",
        "GO TO THE AIRPORT"
};

void imprimirEnPosicion(COORD posicion, const char *texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    std::cout << texto;
}

int main(int argc, char** argv) {
	int nPlayers = 1;
	lista.readLoop(acceso, "tablero.txt");
	acceso = acceso->ant;
	init(nPlayers);
	
}

void init(int _nPlayers)
{
	// std::cout << acceso->name;
	accesoJugador.resize(_nPlayers);
	
	for(int i = 0; i < _nPlayers; i++)
	{
		acceso->isHere[i] = true;
		pagoMovil[i] = MAXMONEY;
		accesoJugador[i] = acceso;
	}
	
	start(_nPlayers);
	
}

void start(int _nPlayers)
{
	int dado, tarjeta, iterador = 0, retirados = 0;
	bool seVende = true, ubicacionEncontrada = false, rondaTerminada = false;
	char compra[2];
	// Do while que define las rondas
	do
	{
		// For para cada jugador en la ronda
		for(int i = 0; i < _nPlayers; i++)
		{
			seVende = true;
			rondaTerminada = false;
			// Primero tiramos el dado
			dado = random();
			// Quitamos al jugador de la casilla original
			accesoJugador[i]->isHere[i] = false;
			// Movemos al jugador tantas casillas lo indique el dado
			for(int a= 0; a<dado; a++){
				accesoJugador[i] = accesoJugador[i]->ant;
			}
			// Ubicamos al jugador en la nueva casilla
			accesoJugador[i]->isHere[i] = true;
			
			// If para verificar si caimos en una de las casillas principales
			if(strcmpi(accesoJugador[i]->name, "HOME") == 0){
				pagoMovil[i] += 200;
				rondaTerminada = true;
			}else if(strcmpi(accesoJugador[i]->name, "??") == 0){ // Si caemos aquí, moveremos al jugador
				tarjeta = random();
				// Con un do recorremos el tablero hasta encontrar la posición de la tarjeta que obtuvo el usuario en la ronda
				do
				{
					switch (tarjeta){
						case 1:
							if(strcmpi(acceso->name, "JAIL") == 0){
								// Movemos al jugador de la posición original
								accesoJugador[i]->isHere[i] = false;
								accesoJugador[i] = acceso;
								// Lo ubicamos en la nueva posición
								accesoJugador[i]->isHere[i] = true;
								ubicacionEncontrada = true;
							}
							break;
						case 2:
							if(strcmpi(acceso->name, "HOME") == 0){
								accesoJugador[i]->isHere[i] = false;
								accesoJugador[i] = acceso;
								accesoJugador[i]->isHere[i] = true;
								ubicacionEncontrada = true;
							}
							break;
						case 3:
							if(strcmpi(acceso->name, "ELECTRICITY") == 0){
								accesoJugador[i]->isHere[i] = false;
								accesoJugador[i] = acceso;
								accesoJugador[i]->isHere[i] = true;
								ubicacionEncontrada = true;
							}
							break;
						case 4:
							if(strcmpi(acceso->name, "RAILWAY") == 0){
								accesoJugador[i]->isHere[i] = false;
								accesoJugador[i] = acceso;
								accesoJugador[i]->isHere[i] = true;
								ubicacionEncontrada = true;
							}
							break;
						case 5:
							if(strcmpi(acceso->name, "HARBOR") == 0){
								accesoJugador[i]->isHere[i] = false;
								accesoJugador[i] = acceso;
								accesoJugador[i]->isHere[i] = true;
								ubicacionEncontrada = true;
							}
							break;
						case 6:
							if(strcmpi(acceso->name, "AIRPORT") == 0){
								accesoJugador[i]->isHere[i] = false;
								accesoJugador[i] = acceso;
								accesoJugador[i]->isHere[i] = true;
								ubicacionEncontrada = true;
							}
							break;
					}	
					// Si encontramos la ubicación de la tarjeta deja de repetirse el while
					iterador++;
					acceso = acceso->ant;
				}
				while(!ubicacionEncontrada && iterador < 28);
			}
			if(!rondaTerminada){
				// Revisamos si el jugador está en una de las casillas especiales para que pague
				if(strcmpi(accesoJugador[i]->name, "HARBOR") == 0){
					if(pagoMovil[i] >= accesoJugador[i]->price){
						pagoMovil[i] -= accesoJugador[i]->price;
					}else{
						retirados++;
					}
					rondaTerminada = true;
				}else if(strcmpi(accesoJugador[i]->name, "RAILWAY") == 0){
					if(pagoMovil[i] >= accesoJugador[i]->price){
						pagoMovil[i] -= accesoJugador[i]->price;
					}else{
						retirados++;
					}
					rondaTerminada = true;
				}else if(strcmpi(accesoJugador[i]->name, "AIRPORT") == 0){
					if(pagoMovil[i] >= accesoJugador[i]->price){
						pagoMovil[i] -= accesoJugador[i]->price;
					}else{
						retirados++;
					}
					rondaTerminada = true;
				}else if(strcmpi(accesoJugador[i]->name, "JAIL") == 0){
					if(pagoMovil[i] >= accesoJugador[i]->price){
						pagoMovil[i] -= accesoJugador[i]->price;
					}else{
						retirados++;
					}
					rondaTerminada = true;
				}else if(strcmpi(accesoJugador[i]->name, "ELECTRICITY") == 0){
					if(pagoMovil[i] >= accesoJugador[i]->price){
						pagoMovil[i] -= accesoJugador[i]->price;
					}else{
						retirados++;
					}
					rondaTerminada = true;
				}
			}
			
			if(!rondaTerminada){
				// For para ver si algún jugador s tiene una casa en la posición
				for(int s = 0; s < _nPlayers; s++){
					if(accesoJugador[i]->houseHere[s]){
						seVende = false;
						if(s == i){
							break;
						}else{
							if(pagoMovil[i] >= accesoJugador[i]->price){
								pagoMovil[i] -= accesoJugador[i]->price;
								pagoMovil[s] += accesoJugador[i]->price;
								break;
							}else{
								accesoJugador[i] = NULL;
							}
						}
					}
				}
				
				if(seVende){
					// Preguntamos si quiere comprar la propiedad
					if((strcmpi(compra, "S") == 0) && (pagoMovil[i] >= accesoJugador[i]->price)){
						// El jugador adquiere la casa
						pagoMovil[i] -= accesoJugador[i]->price;
						accesoJugador[i]->houseHere[i] = true;
					}
				}
			}
			if(_nPlayers - retirados == 1){
				gameOver = true;
				break;
			}
		} // Aquí termina el turno de un jugador
	}
	while(!gameOver);
	// Juego terminado
}

int random()
{
	std::srand(std::time(0));
	return std::rand()%6+1;
}



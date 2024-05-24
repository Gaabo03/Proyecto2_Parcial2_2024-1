#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include "lists.h"
#include "Interface.h"
#define MAXMONEY 500

lists lista;
lists::Nodo *acceso = NULL;
Interface interfaz;
int pagoMovil[4];
bool gameOver = false;
void start(int _nPlayers);
void init(int _nPlayers);
std::vector<std::string> nombres;
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

int main(int argc, char** argv) {
	interfaz.menu();
	nombres = interfaz.pedirDatos();
	int nPlayers = nombres.size();
	lista.readLoop(acceso, "tablero.txt");
	acceso = acceso->ant;
	init(nPlayers);
}

void init(int _nPlayers)
{
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
	int dado, tarjeta, iterador = 0, retirados = 0, diasCarcel[_nPlayers];
	bool seVende = true, ubicacionEncontrada = false, rondaTerminada = false;
	char compra[2], carcel[2];
	
	for (int i=0; i<_nPlayers; i++)
		diasCarcel[i] = 0;
		
	interfaz.imprimirTablero(acceso, nombres);
	std::cin.get();
	// Do while que define las rondas
	do
	{
		// For para cada jugador en la ronda
		for(int i = 0; i < _nPlayers; i++)
		{
			if(diasCarcel[i] == 0 || diasCarcel[i] == 4){
				// El jugador no estï¿½ en la cï¿½rcel o reciï¿½n saliï¿½ de la cï¿½rcel
				diasCarcel[i] = 0;
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
				
				
				interfaz.actualizarTablero(acceso); //ACA ESTOY INTENTANDO IMPRIMIR EL MOVIMIENTO (detecta que se movió pero no hacia donde)
				std::cin.get();
				
				
				// If para verificar si caimos en una de las casillas principales
				if(strcmpi(accesoJugador[i]->name, "HOME") == 0){
					pagoMovil[i] += 200;
					rondaTerminada = true;
				}else if(strcmpi(accesoJugador[i]->name, "??") == 0){ // Si caemos aquï¿½, moveremos al jugador
					tarjeta = random();
					// Con un do recorremos el tablero hasta encontrar la posiciï¿½n de la tarjeta que obtuvo el usuario en la ronda
					do
					{
						switch (tarjeta){
							case 1:
								if(strcmpi(acceso->name, "JAIL") == 0){
									// Movemos al jugador de la posiciï¿½n original
									accesoJugador[i]->isHere[i] = false;
									accesoJugador[i] = acceso;
									// Lo ubicamos en la nueva posiciï¿½n
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
						// Si encontramos la ubicaciï¿½n de la tarjeta deja de repetirse el while
						iterador++;
						acceso = acceso->ant;
					}
					while(!ubicacionEncontrada && iterador < 28);
				}
				if(!rondaTerminada){
					// Revisamos si el jugador estï¿½ en una de las casillas especiales para que pague
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
						// AQUï¿½ DEBEMOS PREGUNTAR AL JUGADOR SI DESEA PAGAR O PREFIERE PASAR TRES TURNOS EN LA Cï¿½RCEL
						if(strcmpi(compra, "S") == 0){
							// Si quiere pagar
							if(pagoMovil[i] >= accesoJugador[i]->price){
								pagoMovil[i] -= accesoJugador[i]->price;
							}
						}else{
							// El jugador pasa tres turnos en la clase
							diasCarcel[i] ++;
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
					// For para ver si algï¿½n jugador s tiene una casa en la posiciï¿½n
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
			}else{
				// El jugador estï¿½ en la cï¿½rcel
			}
			
			// AQUï¿½ SE DEBE REFRESCAR EL TABLERO
			
			if(_nPlayers - retirados == 1){
				gameOver = true;
				break;
			}
		} // Aquï¿½ termina el turno de un jugador
	}
	while(!gameOver);
	// Juego terminado
}

int random()
{
	std::srand(std::time(0));
	return std::rand()%6+1;
}



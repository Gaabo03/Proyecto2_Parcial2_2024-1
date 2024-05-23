#include <iostream>
#include <windows.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void imprimirEnPosicion(COORD posicion, const char *texto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    std::cout << texto;
}

int main(int argc, char** argv) {

}

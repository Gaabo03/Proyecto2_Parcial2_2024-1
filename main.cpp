void imprimirEnPosicion(COORD posicion, const char *texto)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    std::cout << texto;
}

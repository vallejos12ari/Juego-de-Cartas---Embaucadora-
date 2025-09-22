#include <iostream>
#include <ctime>
#include <locale.h>
#include "logicaJuego.h"
#include "menu_nombres_creditos.h"
#include "desarrolloJuego.h"
#include "rlutil.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "spanish_Argentina");
    int opcion;
    char respuestaAbandonar;
    bool abandonar = false;

    do
    {
        mostrarMenu();
        cin >> opcion;
        rlutil::cls();

        switch (opcion)
        {
        case 1:
            jugar();
            break;
        case 2:
            mostrarEstadisticas();
            break;
        case 3:

            mostrarCreditos();
            break;

        case 0:
            cout << "Abandonar juego. ¿Esta seguro? S/N " << endl;
            do
            {
                cin >> respuestaAbandonar;
                if(respuestaAbandonar == 's' || respuestaAbandonar == 'S')
                {
                    abandonar = true;
                    break;
                }
                else if(respuestaAbandonar == 'n' || respuestaAbandonar == 'N')
                {
                    rlutil::cls();
                    mostrarMenu();
                    break;
                }
                else
                {
                    cout << "Error. Intente nuevamente." << endl;
                    cout << "--------------------------------------------------" << endl;
                }
            }
            while(respuestaAbandonar != 's' || respuestaAbandonar != 'S' || respuestaAbandonar != 'n' || respuestaAbandonar != 'N' );
            rlutil::cls();
            break;

        default:
            if(opcion != 0)
            {
                cout << "Error. Ingrese un numero del 1 al 3 o 0 para salir." << endl;
                cout << "--------------------------------------------------" << endl;
            }

            break;
        }
    }
    while (!abandonar);

    return 0;
}


#include <iostream>
#include "menu_nombres_creditos.h"
#include <cstdlib>
#include <locale.h>
#include "rlutil.h"
#include <string>

using namespace std;

void mostrarMenu()
{
    cout<<" "<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"|                    EMBAUCADO                     |"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<" "<<endl;
    cout << "--------------------------------------------------" << std::endl;
    cout << "1 - JUGAR" << std::endl;
    cout << "2 - ESTADÍSTICAS" << std::endl;
    cout << "3 - CRÉDITOS" << std::endl;
    cout << "--------------------------------------------------" << std::endl;
    cout << "0 - SALIR" << std::endl;
}

void ingresarNombres(string& nombreJ1, string& nombreJ2)
{
    cout<<" "<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"|                    EMBAUCADO                     |"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<" "<<endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Antes de comenzar deben registrar sus nombres: " << endl;
    cout << "¿Nombre del Jugador 1? ";
    cin >> nombreJ1;
    cout << "¿Nombre del Jugador 2? ";
    cin >> nombreJ2;
    cout << endl;
}

void confirmarNombres(string& nombreJ1, string& nombreJ2)
{
    string strConfirmarNombres;
    char opcionCambiarNombre;


    do
    {
        cout << "Nombre del Jugador 1: " << nombreJ1 << endl;
        cout << "Nombre del Jugador 2: " << nombreJ2 << endl;
        cout << "¿Confirmar nombres? (S/N) " << endl;
        cout << "--------------------------------------------------" << endl;
        cin >> strConfirmarNombres;

        if (strConfirmarNombres == "s" || strConfirmarNombres == "S")
        {
            cout << "Nombres confirmados. ¡Bienvenidos "<<nombreJ1 << " y " << nombreJ2 << endl;
        }
        else if (strConfirmarNombres == "n" || strConfirmarNombres == "N")
        {
            cout << "Nombres no confirmados. Intente de nuevo" << endl;

            cout << "¿Que nombre desea modificar? " << endl;
            cout << "Jugador 1 = 1 " << endl;
            cout << "Jugador 2 = 2 " << endl;

            cin >> opcionCambiarNombre;


            if (opcionCambiarNombre == '1')
            {
                cout << "Ingrese el nombre del Jugador 1" << endl;
                cin >> nombreJ1;
            }
            else if (opcionCambiarNombre == '2')
            {
                cout << "Ingrese el nombre del Jugador 2" << endl;
                cin >> nombreJ2;
            }
            else if(opcionCambiarNombre != '1' || opcionCambiarNombre != '2')
            {
                 cout << "ERROR. Dato ingresado inválido. Intente de nuevo." << endl;
                 cout << "--------------------------------------------------" << endl;
            }

        }else{
                  cout << "ERROR.  Intente de nuevo." << endl;
                 cout << "--------------------------------------------------" << endl;
        }
    }
    while (strConfirmarNombres != "s" && strConfirmarNombres != "S");
}

void mostrarCreditos()
{
        cout<<" "<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"|                  CRÉDITOS                    |"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<" "<<endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    cout << "Juego inventado por Angel Simón." << endl;
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Inspirado levemente en un juego Push your luck de Bob Lancaster -" << endl;
    cout << "Nombre del juego basado en la serie Friends." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Alumnos desarrolladores:" << endl;
    cout << "Sanchez, Santiago Ezequiel - Legajo: 30679" << endl;
    cout << "Vallejos Ari, Carla - Legajo: 30637" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    cout << "Presione una tecla para volver al menú." << endl;
    rlutil::anykey();
    rlutil::cls();
}

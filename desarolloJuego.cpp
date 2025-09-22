#include <iostream>
#include <cstdlib>
#include <locale.h>
#include "desarrolloJuego.h"
#include "menu_nombres_creditos.h"
#include "rlutil.h"
#include "logicaJuego.h"

using namespace std;

string valores[] = {"10", "J", "Q", "K", "A"};
string palos[] = {"Corazon", "Diamante", "Pica", "Trebol"};
const int CANT_VALORES = 5;
const int CANT_PALOS = 4;
const int CANT_CARTAS = 20;

string barajaValores[CANT_CARTAS];
string barajaPalos[CANT_CARTAS];
string mazoValoresJ1[CANT_VALORES];
string mazoPalosJ1[CANT_VALORES];
string mazoValoresJ2[CANT_VALORES];
string mazoPalosJ2[CANT_VALORES];

int puntajeJ1 = 0, puntajeJ2 = 0;
int puntosRondaJ1, puntosRondaJ2;
int puntosRonda1Jugador1 = 0, puntosRonda2Jugador1 = 0, puntosRonda3Jugador1 = 0; // puntaje de cada ronda para el jugador 1 (para estadisticas)
int puntosRonda1Jugador2 = 0, puntosRonda2Jugador2 = 0, puntosRonda3Jugador2 = 0; // puntaje de cada ronda para el jugador 2 (para estadisticas)
int ronda; // entero para ir iterando sobre las rondas (se usa para el while)
int puntajeTotalJ1 = 0, puntajeTotalJ2 = 0; // puntaje total para cada jugador (para estadisticas)
string mismaEmbaucadora; // string para no repetir carta embaucadora
string nombreJ1, nombreJ2; // nombres jugadores
string cartaEmbaucadora; // string para guardar calculo de carta embaucadora
char respuesta; // char para respuesta sobre cambio de carta embaucadora

string nombreGanador;
string nombreGanadorHistorico;
int puntajeGanador = 0;
int puntajeGanadorHistorico = 0;
bool dosGanadores = false;

void mostrarPuntajesFinales(string& nombreJ1, string& nombreJ2)
{
    cout<<" "<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"|              Fin de la partida                   |"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<" "<<endl;

    cout << "RONDA        " << nombreJ1 << "        " << nombreJ2 << "\n";
    cout << "--------------------------------------\n";
    cout << "  1           " << puntosRonda1Jugador1 << "            " << puntosRonda1Jugador2 << "\n";
    cout << "  2           " << puntosRonda2Jugador1 << "            " << puntosRonda2Jugador2 << "\n";
    cout << "  3           " << puntosRonda3Jugador1 << "            " << puntosRonda3Jugador2 << "\n";
    cout << "--------------------------------------\n";
    cout << "TOTAL         " << puntajeTotalJ1 << "           " << puntajeTotalJ2 << "\n";
}

// Metodo burbuja para ordenar de mayor a menor las rondas de cada jugador
void ordenarMayorAMenor(int v[], int numeroRondas)
{
    int i, j, auxiliar;
    for (i = 0; i < numeroRondas; i++)
    {
        for (j = 0; j < numeroRondas - 1; j++)
        {
            if (v[j] < v[j + 1])
            {
                auxiliar = v[j + 1];
                v[j + 1] = v[j];
                v[j] = auxiliar;
            }
        }
    }
}

void mostrarEstadisticas()
{

    cout<<" "<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"|                  ESTADÍSTICAS                    |"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"+--------------------------------------------------+"<<endl;
    cout<<" "<<endl;
    if (puntajeGanador == 0)
    {
        cout << "Aún no hubo ganadores." << endl;
        cout << "Presione una tecla para volver al menú." << endl;
        rlutil::anykey();
        rlutil::cls();
    }
    else if (!dosGanadores)
    {
        cout << "El jugador con mayor cantidad de puntos es: " << nombreGanadorHistorico << ". Logró un total de " << puntajeGanadorHistorico << " puntos." << endl;
        cout << endl;
        cout << "Presione una tecla para volver al menú." << endl;
        rlutil::anykey();
        rlutil::cls();
    }
    else
    {
        cout << "Los jugadores con mayor cantidad de puntos son: " << nombreGanadorHistorico << ". Lograron un total de " << puntajeGanadorHistorico << " puntos en un empate." << endl;
        cout << endl;
        cout << "Presione una tecla para volver al menú." << endl;
        rlutil::anykey();
        rlutil::cls();
    }
}


void jugar()
{
    setlocale(LC_ALL, "spanish_Argentina");
    ronda = 1;
    puntajeJ1 = 0, puntajeJ2 = 0;
    puntajeGanador = 0;

    ingresarNombres(nombreJ1, nombreJ2);
    confirmarNombres(nombreJ1, nombreJ2);
    rlutil::anykey();
    rlutil::cls();

    while (ronda < 4)
    {
        {
            rlutil::cls();
            bool confirmacionCambio;

            // Mezclo - Reparto - Selecciono Carta Embaucadora
            mezclarCartas(valores, palos, barajaValores, barajaPalos, CANT_VALORES, CANT_PALOS, CANT_CARTAS);
            repartirCartas(barajaValores, barajaPalos, mazoValoresJ1, mazoPalosJ1, mazoValoresJ2, mazoPalosJ2, CANT_VALORES);
            cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);

            if(ronda == 1)
            {
                rlutil::cls();
                cout<<" "<<endl;
                cout<<"+--------------------------------------------------+"<<endl;
                cout<<"|                                                  |"<<endl;
                cout<<"|                    RONDA #"<<ronda<<"                      |"<<endl;
                cout<<"|                                                  |"<<endl;
                cout<<"+--------------------------------------------------+"<<endl;
                cout<<" "<<endl;

                // Le muestro las cartas a los jugadores
                cout << "RONDA #" << ronda << "\n" << nombreJ1 << " Vs " << nombreJ2 << "\n";
                cout << "+-------------------------+\n";
                cout << nombreJ1 << " (" << puntajeJ1 << " puntos)\n";
                mostrarCartas(mazoValoresJ1, mazoPalosJ1, CANT_VALORES);
                cout << endl;
                cout << nombreJ2 << " (" << puntajeJ2 << " puntos)\n";
                mostrarCartas(mazoValoresJ2, mazoPalosJ2, CANT_VALORES);
                cout << endl;
                cout << "Embaucadora: " << cartaEmbaucadora << "\n";
                cout << "+-------------------------+\n";

                // Calculo puntajes de la ronda
                puntosRondaJ1 = calcularPuntaje(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                puntosRondaJ2 = calcularPuntaje(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);

                puntosRonda1Jugador1 = puntosRondaJ1;
                puntosRonda1Jugador2 = puntosRondaJ2;

                puntajeJ1 += puntosRondaJ1;
                puntajeJ2 += puntosRondaJ2;

                puntajeTotalJ1 = puntosRonda1Jugador1;
                puntajeTotalJ2 = puntosRonda1Jugador2;

                // Imprimo los puntajes de la ronda
                cout << "Puntajes obtenidos: " << endl;
                cout << nombreJ1 << ": ";
                imprimirPuntajes(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                cout << " = " << puntosRondaJ1;

                cout << endl;

                cout << nombreJ2 << ": ";
                imprimirPuntajes(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);
                cout << " = " << puntosRondaJ2;


                cout << endl;
                cout << "Presione un boton para continuar a la siguiente ronda." << endl;
                ronda++;
                rlutil::anykey();
                rlutil::cls();
            }
            else if(ronda == 2)
            {
                rlutil::cls();
                cout<<" "<<endl;
                cout<<"+--------------------------------------------------+"<<endl;
                cout<<"|                                                  |"<<endl;
                cout<<"|                    RONDA #"<<ronda<<"                      |"<<endl;
                cout<<"|                                                  |"<<endl;
                cout<<"+--------------------------------------------------+"<<endl;
                cout<<" "<<endl;
                confirmacionCambio = false;

                // Mezclo - Reparto - Selecciono Carta Embaucadora
                mezclarCartas(valores, palos, barajaValores, barajaPalos, CANT_VALORES, CANT_PALOS, CANT_CARTAS);
                repartirCartas(barajaValores, barajaPalos, mazoValoresJ1, mazoPalosJ1, mazoValoresJ2, mazoPalosJ2, CANT_VALORES);
                cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);
                // Guardo variable por si se decide cambiar embaucadora y no toque la misma
                mismaEmbaucadora = cartaEmbaucadora;

                // Le muestro las cartas a los jugadores
                cout << "RONDA #" << ronda << "\n" << nombreJ1 << " Vs " << nombreJ2 << "\n";
                cout << "+-------------------------+\n";
                cout << nombreJ1 << " (" << puntajeTotalJ1 << " puntos)\n"; /// PUNTAJE RONDA ANTERIOR (1)
                mostrarCartas(mazoValoresJ1, mazoPalosJ1, CANT_VALORES);
                cout << endl;
                cout << nombreJ2 << " (" << puntajeTotalJ2 << " puntos)\n"; /// PUNTAJE RONDA ANTERIOR (1)
                mostrarCartas(mazoValoresJ2, mazoPalosJ2, CANT_VALORES);
                cout << endl;
                cout << "Embaucadora: " << cartaEmbaucadora << "\n";
                cout << "+-------------------------+\n";

                // Consulta al jugador 1 para cambiar carta embaucadora
                cout << nombreJ1 << ": ¿Desea cambiar la carta embaucadora actual? (" << cartaEmbaucadora << ") (S/N)" << endl;
                cin >> respuesta;

                /// ANALISIS JUGADOR 1 CON PRIORIDAD
                while (respuesta != 'S' && respuesta != 's' && respuesta != 'N' && respuesta != 'n')
                {
                    cout << "+-------------------------+\n";
                    cout << "Error!" << endl;
                    cout << nombreJ1 << ": ¿Desea cambiar la carta embaucadora actual? (" << cartaEmbaucadora << ") (S/N)";
                    cin >> respuesta;
                    cout << "+-------------------------+\n";
                }
                if (puntajeJ1 < 20 && (respuesta == 'S' || respuesta == 's'))
                {
                    cout << "+-------------------------+\n";
                    cout << "Puntos insuficientes." << endl;
                    cout << "+-------------------------+\n";
                }
                if ((respuesta == 'S' || respuesta == 's') && puntajeJ1 >= 20)
                {
                    rlutil::cls();
                    confirmacionCambio = true;
                    // Calculo carta embaucadora nuevamente
                    do
                    {
                        cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);
                    }
                    while (mismaEmbaucadora == cartaEmbaucadora);

                    // Le muestro las cartas a los jugadores nuevamente
                    cout << "+------- Cambio de carta embaucada ---------+";
                    cout << endl;
                    cout << "RONDA #" << ronda << "\n" << nombreJ1 << " Vs " << nombreJ2 << "\n";
                    cout << "+-------------------------+\n";
                    cout << nombreJ1 << " (" << puntajeJ1 << " puntos)\n";
                    mostrarCartas(mazoValoresJ1, mazoPalosJ1, CANT_VALORES);
                    cout << endl;
                    cout << nombreJ2 << " (" << puntajeJ2 << " puntos)\n";
                    mostrarCartas(mazoValoresJ2, mazoPalosJ2, CANT_VALORES);
                    cout << endl;
                    cout << "Nueva Embaucadora: " << cartaEmbaucadora << "\n";
                    cout << "+-------------------------+\n";

                    // Calculo puntajes de la ronda
                    puntosRondaJ1 = calcularPuntaje(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                    puntosRondaJ2 = calcularPuntaje(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);

                    puntosRondaJ1 -= 20;

                    puntosRonda2Jugador1 = puntosRondaJ1;
                    puntosRonda2Jugador2 = puntosRondaJ2;

                    puntajeTotalJ1 = puntosRonda1Jugador1 + puntosRonda2Jugador1;
                    puntajeTotalJ2 = puntosRonda1Jugador2 + puntosRonda2Jugador2;

                    // Imprimo los puntajes de la ronda
                    cout << "Puntajes obtenidos: " << endl;
                    cout << nombreJ1 << ": ";
                    imprimirPuntajes(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                    cout << " = " << puntosRondaJ1;
                    cout << " (Se restaron 20 puntos de esta mano por cambiar carta embaucadora)." << endl;

                    cout << endl;

                    cout << nombreJ2 << ": ";
                    imprimirPuntajes(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);
                    cout << " = " << puntosRondaJ2;
                    cout << endl;
                    cout << "+-------------------------+\n";
                    cout << "Presione un boton para continuar a la siguiente ronda." << endl;

                    cout << endl;
                }
                /// ANALISIS JUGADOR 2
                if (!confirmacionCambio) // CONSULTA al jugador 2, siempre y cuando el jugador 1 no haya decidido cambiar
                {
                    char respuesta2;
                    cout << nombreJ2 << ": ¿Desea cambiar la carta embaucadora actual? (" << cartaEmbaucadora << ") (S/N)" << endl;  /// pasar todo a minuscula o mayuscula para el while de validacion
                    cin >> respuesta2;

                    while (respuesta2 != 'S' && respuesta2 != 's' && respuesta2 != 'N' && respuesta2 != 'n')
                    {
                        cout << "+-------------------------+\n";
                        cout << "Error!" << endl;
                        cout << nombreJ2 << ": ¿Desea cambiar la carta embaucadora actual " << cartaEmbaucadora << "? (S/N)";
                        cin >> respuesta2;
                        cout << "+-------------------------+\n";
                    }
                    if ((respuesta2 == 'S' || respuesta2 == 's') && puntajeJ2 < 20)
                    {
                        cout << "+-------------------------+\n";
                        cout << "Puntos insuficientes." << endl;
                        cout << "+-------------------------+\n";
                    }

                    if ((respuesta2 == 'S' || respuesta2 == 's') && puntajeJ2 >= 20)
                    {
                        rlutil::cls();
                        confirmacionCambio = true;
                        // Calculo carta embaucadora nuevamente
                        cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);
                        do
                        {
                            cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);
                        }
                        while (mismaEmbaucadora == cartaEmbaucadora);

                        // Le muestro las cartas a los jugadores
                        cout << "+------- Cambio de carta embaucada ---------+";
                        cout << endl;
                        cout << "RONDA #" << ronda << "\n" << nombreJ1 << " vs " << nombreJ2 << "\n";
                        cout << "+-------------------------+\n";
                        cout << nombreJ1 << " (" << puntajeTotalJ1 << " puntos)\n";
                        mostrarCartas(mazoValoresJ1, mazoPalosJ1, CANT_VALORES);
                        cout << endl;
                        cout << nombreJ2 << " (" << puntajeTotalJ2 << " puntos)\n";
                        mostrarCartas(mazoValoresJ2, mazoPalosJ2, CANT_VALORES);
                        cout << endl;
                        cout << "Nueva Embaucadora: " << cartaEmbaucadora << "\n";
                        cout << "+-------------------------+\n";

                        // Calculo puntajes de la ronda
                        puntosRondaJ1 = calcularPuntaje(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                        puntosRondaJ2 = calcularPuntaje(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);


                        puntosRondaJ2 -= 20;

                        puntosRonda2Jugador1 = puntosRondaJ1;
                        puntosRonda2Jugador2 = puntosRondaJ2;

                        puntajeTotalJ1 = puntosRonda1Jugador1 + puntosRonda2Jugador1;
                        puntajeTotalJ2 = puntosRonda1Jugador2 + puntosRonda2Jugador2;

                        // Imprimo los puntajes de la ronda
                        cout << "Puntajes obtenidos: " << endl;
                        cout << nombreJ1 << ": ";
                        imprimirPuntajes(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                        cout << " = " << puntosRondaJ1;

                        cout << endl;

                        cout << nombreJ2 << ": ";
                        imprimirPuntajes(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);
                        cout << " = " << puntosRondaJ2;
                        cout << " (Se restaron 20 puntos de esta mano por cambiar carta embaucadora)." << endl;
                        cout << "+-------------------------+\n";
                        cout << endl;
                        cout << "Presione un boton para continuar a la siguiente ronda." << endl;

                    }
                }
                if (!confirmacionCambio)
                {
                    puntosRondaJ1 = calcularPuntaje(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                    puntosRondaJ2 = calcularPuntaje(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);

                    puntosRonda2Jugador1 = puntosRondaJ1;
                    puntosRonda2Jugador2 = puntosRondaJ2;

                    puntajeTotalJ1 = puntosRonda1Jugador1 + puntosRonda2Jugador1;
                    puntajeTotalJ2 = puntosRonda1Jugador2 + puntosRonda2Jugador2;

                    // Imprimo los puntajes de la ronda para el caso en que los dos jugadores decidan no cambiar embaucadora
                    cout << "+-------------------------+\n";
                    cout << "Puntajes obtenidos: " << endl;
                    cout << nombreJ1 << ": ";
                    imprimirPuntajes(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                    cout << " = " << puntosRondaJ1;

                    cout << endl;

                    cout << nombreJ2 << ": ";
                    imprimirPuntajes(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);
                    cout << " = " << puntosRondaJ2;
                    cout << endl;
                    cout << "No se solicitaron cambios de carta embaucadora." << endl;
                    cout << "+-------------------------+\n";
                    cout << endl;
                    cout << "Presione un boton para continuar a la siguiente ronda." << endl;
                }
                ronda++;
                //system("pause");
                rlutil::anykey();
                rlutil::cls();
            }
            else // RONDA 3
            {
                rlutil::cls();
                cout<<" "<<endl;
                cout<<"+--------------------------------------------------+"<<endl;
                cout<<"|                                                  |"<<endl;
                cout<<"|                    RONDA #"<<ronda<<"                      |"<<endl;
                cout<<"|                                                  |"<<endl;
                cout<<"+--------------------------------------------------+"<<endl;
                cout<<" "<<endl;
                confirmacionCambio = false;
                // Mezclo y reparto cartas
                mezclarCartas(valores, palos, barajaValores, barajaPalos, CANT_VALORES, CANT_PALOS, CANT_CARTAS);
                repartirCartas(barajaValores, barajaPalos, mazoValoresJ1, mazoPalosJ1, mazoValoresJ2, mazoPalosJ2, CANT_VALORES);

                // Selecciono carta embaucadora
                cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);
                mismaEmbaucadora = cartaEmbaucadora;

                // Le muestro las cartas a los jugadores
                cout << "RONDA #" << ronda << "\n" << nombreJ1 << " vs " << nombreJ2 << "\n";
                cout << "+-------------------------+\n";
                cout << nombreJ1 << " (" << puntajeTotalJ1 << " puntos)\n";
                mostrarCartas(mazoValoresJ1, mazoPalosJ1, CANT_VALORES);
                cout << endl;
                cout << nombreJ2 << " (" << puntajeTotalJ2 << " puntos)\n";
                mostrarCartas(mazoValoresJ2, mazoPalosJ2, CANT_VALORES);
                cout << endl;
                cout << "Embaucadora: " << cartaEmbaucadora << "\n";
                cout << "+-------------------------+\n";

                // Consulta al jugador 2 para cambiar carta embaucadora
                cout << nombreJ2 << ": ¿Desea cambiar la carta embaucadora actual " << cartaEmbaucadora << "? (S/N)" << endl;
                cin >> respuesta;

                while (respuesta != 'S' && respuesta != 's' && respuesta != 'N' && respuesta != 'n')
                {
                    cout << "+-------------------------+\n";
                    cout << "Error!" << endl;
                    cout << nombreJ2 << ": ¿Desea cambiar la carta embaucadora actual " << cartaEmbaucadora << "? (S/N)";
                    cin >> respuesta;
                    rlutil::cls();
                    cout << "+-------------------------+\n";
                }

                if ((puntajeJ2 < 20) && (respuesta == 'S' || respuesta == 's'))
                {
                    cout << "+-------------------------+\n";
                    cout << "Puntos insuficientes." << endl;
                    cout << "+-------------------------+\n";
                }
                if ((respuesta == 'S' || respuesta == 's') && puntajeJ2 >= 20)
                {
                    rlutil::cls();
                    confirmacionCambio = true;
                    // Calculo carta embaucadora nuevamente
                    cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);
                    do
                    {
                        cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);
                    }
                    while (mismaEmbaucadora == cartaEmbaucadora);

                    // Le muestro las cartas a los jugadores
                    cout << "+------- Cambio de carta embaucada ---------+";
                    cout << endl;
                    cout << "RONDA #" << ronda << "\n" << nombreJ1 << " vs " << nombreJ2 << "\n";
                    cout << "+-------------------------+\n";
                    cout << nombreJ1 << " (" << puntajeTotalJ1 << " puntos)\n";
                    mostrarCartas(mazoValoresJ1, mazoPalosJ1, CANT_VALORES);
                    cout << endl;
                    cout << nombreJ2 << " (" << puntajeTotalJ2 << " puntos)\n";
                    mostrarCartas(mazoValoresJ2, mazoPalosJ2, CANT_VALORES);
                    cout << endl;
                    cout << "Embaucadora: " << cartaEmbaucadora << "\n";
                    cout << "+-------------------------+\n";

                    // Calculo puntajes de la ronda
                    puntosRondaJ1 = calcularPuntaje(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                    puntosRondaJ2 = calcularPuntaje(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);

                    puntosRondaJ2 -= 20;

                    puntosRonda3Jugador1 = puntosRondaJ1;
                    puntosRonda3Jugador2 = puntosRondaJ2;

                    puntajeTotalJ1 = puntosRonda1Jugador1 + puntosRonda2Jugador1 + puntosRonda3Jugador1;
                    puntajeTotalJ2 = puntosRonda1Jugador2 + puntosRonda2Jugador2 + puntosRonda3Jugador2;

                    // Imprimo los puntajes de la ronda
                    cout << "Puntajes obtenidos: " << endl;
                    cout << nombreJ1 << ": ";
                    imprimirPuntajes(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                    cout << " = " << puntosRondaJ1;

                    cout << endl;

                    cout << nombreJ2 << ": ";
                    imprimirPuntajes(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);
                    cout << " = " << puntosRondaJ2;
                    cout << " (Se restaron 20 puntos de esta mano por cambiar carta embaucadora)." << endl;
                    cout << "+-------------------------+\n";
                    cout << endl;
                    cout << "Presione un boton para ver el puntaje final." << endl;

                    cout << endl;
                }

                if (!confirmacionCambio) // CONSULTA al jugador 1, siempre y cuando el jugador 2 no haya decidido cambiar
                {
                    char respuesta2;
                    cout << nombreJ1 << ": ¿Desea cambiar la carta embaucadora actual" << cartaEmbaucadora << "? (S/N)" << endl;
                    cin >> respuesta2;

                    while (respuesta2 != 'S' && respuesta2 != 's' && respuesta2 != 'N' && respuesta2 != 'n')
                    {
                        cout << "+-------------------------+\n";
                        cout << "Error!" << endl;
                        cout << nombreJ1 << ": ¿Desea cambiar la carta embaucadora actual " << cartaEmbaucadora << "? (S/N)";
                        cin >> respuesta2;
                        cout << "+-------------------------+\n";
                    }

                    if ((puntajeJ2 < 20) && (respuesta2 == 'S' || respuesta2 == 's'))
                    {
                        cout << "+-------------------------+\n";
                        cout << "Puntos insuficientes." << endl;
                        cout << "+-------------------------+\n";
                    }

                    if ((respuesta2 == 'S' || respuesta2 == 's') && puntajeJ2 >= 20)
                    {
                        rlutil::cls();
                        confirmacionCambio = true;
                        // Calculo carta embaucadora nuevamente
                        cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);
                        do
                        {
                            cartaEmbaucadora = CartaEmbaucadora(palos, CANT_PALOS);
                        }
                        while (mismaEmbaucadora == cartaEmbaucadora);

                        // Le muestro las cartas a los jugadores
                        cout << "RONDA #" << ronda << "\n" << nombreJ1 << " Vs " << nombreJ2 << "\n";
                        cout << "+-------------------------+\n";
                        cout << nombreJ1 << " (" << puntajeTotalJ1 << " puntos)\n";
                        mostrarCartas(mazoValoresJ1, mazoPalosJ1, CANT_VALORES);
                        cout << endl;
                        cout << nombreJ2 << " (" << puntajeTotalJ2 << " puntos)\n";
                        mostrarCartas(mazoValoresJ2, mazoPalosJ2, CANT_VALORES);
                        cout << endl;
                        cout << "Embaucadora: " << cartaEmbaucadora << "\n";
                        cout << "+-------------------------+\n";

                        // Calculo puntajes de la ronda
                        puntosRondaJ1 = calcularPuntaje(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                        puntosRondaJ2 = calcularPuntaje(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);

                        puntosRondaJ1 -= 20;

                        puntosRonda3Jugador1 = puntosRondaJ1;
                        puntosRonda3Jugador2 = puntosRondaJ2;

                        puntajeTotalJ1 = puntosRonda1Jugador1 + puntosRonda2Jugador1 + puntosRonda3Jugador1;
                        puntajeTotalJ2 = puntosRonda1Jugador2 + puntosRonda2Jugador2 + puntosRonda3Jugador2;

                        // Imprimo los puntajes de la ronda
                        cout << "Puntajes obtenidos: " << endl;
                        cout << nombreJ1 << ": ";
                        imprimirPuntajes(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                        cout << " = " << puntosRondaJ1;
                        cout << " (Se restaron 20 puntos de esta mano por cambiar carta embaucadora)." << endl;

                        cout << endl;

                        cout << nombreJ2 << ": ";
                        imprimirPuntajes(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);
                        cout << " = " << puntosRondaJ2;
                        cout << endl;
                        cout << "+-------------------------+\n";
                        cout << endl;
                        cout << "Presione un boton para ver el puntaje final." << endl;

                        cout << endl;

                    }
                }
                if (!confirmacionCambio)
                {
                    // Calculo puntajes de la ronda
                    puntosRondaJ1 = calcularPuntaje(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                    puntosRondaJ2 = calcularPuntaje(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);


                    puntosRonda3Jugador1 = puntosRondaJ1;
                    puntosRonda3Jugador2 = puntosRondaJ2;

                    puntajeTotalJ1 = puntosRonda1Jugador1 + puntosRonda2Jugador1 + puntosRonda3Jugador1;
                    puntajeTotalJ2 = puntosRonda1Jugador2 + puntosRonda2Jugador2 + puntosRonda3Jugador2;

                    // Imprimo los puntajes de la ronda para el caso en que los dos jugadores decidan no cambiar embaucadora
                    cout << "+-------------------------+\n";
                    cout << "Puntajes obtenidos: " << endl;
                    cout << nombreJ1 << ": ";
                    imprimirPuntajes(mazoValoresJ1, mazoPalosJ1, cartaEmbaucadora, CANT_VALORES);
                    cout << " = " << puntosRondaJ1;

                    cout << endl;

                    cout << nombreJ2 << ": ";
                    imprimirPuntajes(mazoValoresJ2, mazoPalosJ2, cartaEmbaucadora, CANT_VALORES);
                    cout << " = " << puntosRondaJ2;
                    cout << endl;
                    cout << "No se solicitaron cambios de carta embaucadora." << endl;
                    cout << "+-------------------------+\n";
                    cout << endl;
                    cout << "Presione un boton para ver el puntaje final." << endl;
                }
                ronda++;
                rlutil::anykey();
                rlutil::cls();
            }
        }
    }

    ronda = 1; // vuelvo a inicializar la ronda en 1 para que si vuelven a jugar entre en el bucle while anterior

    /// Corta la ronda 3.
    /// Muestro puntajes finales

    mostrarPuntajesFinales(nombreJ1, nombreJ2);

    if (puntajeTotalJ1 > puntajeTotalJ2)
    {
        cout << "GANADOR: " << nombreJ1 << " con " << puntajeTotalJ1 << " puntos de victoria." << endl;
        nombreGanador = nombreJ1;
        puntajeGanador = puntajeTotalJ1;
        if (puntajeGanador > puntajeGanadorHistorico)
        {
            puntajeGanadorHistorico = puntajeGanador;
            nombreGanadorHistorico = nombreGanador;
        }

    }
    else if (puntajeTotalJ2 > puntajeTotalJ1)
    {
        cout << "GANADOR: " << nombreJ2 << " con " << puntajeTotalJ2 << " puntos de victoria." << endl;
        nombreGanador = nombreJ2;
        puntajeGanador = puntajeTotalJ2;
        if (puntajeGanador > puntajeGanadorHistorico)
        {
            puntajeGanadorHistorico = puntajeGanador;
            nombreGanadorHistorico = nombreGanador;
        }
    }
    else
    {
        int vectorPuntosJ1[] = {puntosRonda1Jugador1, puntosRonda2Jugador1, puntosRonda3Jugador1};
        int vectorPuntosJ2[] = {puntosRonda1Jugador2, puntosRonda2Jugador2, puntosRonda3Jugador2};
        int numeroRondas = 3;
        bool ganaJ1 = false;
        bool ganaJ2 = false;
        int maxJ1, maxJ2;
        int i = 0;

        // Ordeno los vectores de puntos de cada jugador de mayor a menor para poder analizarlos por su indice
        ordenarMayorAMenor(vectorPuntosJ1, numeroRondas);
        ordenarMayorAMenor(vectorPuntosJ2, numeroRondas);

        while((!ganaJ1 && !ganaJ2) && i < numeroRondas)
        {
            if (vectorPuntosJ1[i] > vectorPuntosJ2[i])
            {
                maxJ1 = vectorPuntosJ1[i];
                ganaJ1 = true;
            }
            else if (vectorPuntosJ2[i] > vectorPuntosJ1[i])
            {
                maxJ2 = vectorPuntosJ2[i];
                ganaJ2 = true;
            }
            i++;
        }

        if(ganaJ1)
        {
            cout << "El ganador es " << nombreJ1 << " por obtener " << maxJ1 << " puntos en una de las rondas." << endl;
            nombreGanador = nombreJ1;
            puntajeGanador = puntajeTotalJ1;
            if (puntajeGanador > puntajeGanadorHistorico)
            {
                puntajeGanadorHistorico = puntajeGanador;
                nombreGanadorHistorico = nombreGanador;
            }
        }
        else if (ganaJ2)
        {
            cout << "El ganador es: " << nombreJ2 << " por obtener " << maxJ2 << " puntos en una de las rondas." << endl;
            nombreGanador = nombreJ2;
            puntajeGanador = puntajeTotalJ2;
            if (puntajeGanador > puntajeGanadorHistorico)
            {
                puntajeGanadorHistorico = puntajeGanador;
                nombreGanadorHistorico = nombreGanador;
            }
        }

        else
        {
            cout << "Empate TOTAL. Ambos jugadores tienen los mismos puntos en cada ronda." << endl;
            nombreGanador = nombreJ1 + " y " + nombreJ2;
            dosGanadores = true;
            puntajeGanador = puntajeTotalJ1; // es lo mismo poner puntaje del J1 o J2
            if (puntajeGanador > puntajeGanadorHistorico)
            {
                puntajeGanadorHistorico = puntajeGanador;
                nombreGanadorHistorico = nombreGanador;
            }
        }

    }

    system("pause");
    std::cout << "\033[2J\033[1;1H";
}
